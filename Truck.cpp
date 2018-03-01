
	/*******************************************************************
	*   CS 307 Programming Assignment 3 - Traffic Simulation
	*   File: Truck.cpp
	*   Author: Joanna Pease
	*	Prog Desc: This program simulates traffic on a grid of roads.
	*		Vehicles travel on the roads while obeying the road's speed
	*		limit and the status of the traffic light at the upcoming
	*		intersection.
	*   File Desc: This is the Truck subclass of VehicleMovement.
	*		It handles moving and printing a report for large trucks.
	*   Date: 4/9/17
	*
	*   I attest that this program is entirely my own work, unless
	*	noted otherwise.
	*******************************************************************/
#include "stdafx.h"
#include "Truck.h"

Truck::Truck(eCarType typeEnum, int ID, double startX, double startY, 
		eCompassDirection direction, double acc)
{
	m_iVehicleID = ID;
	m_dXPos = startX;
	m_dYPos = startY;
	m_dDirection = direction;
	m_dAcceleration = acc;
	m_dSpeedMPH = m_dSpeedMPS = 0;
	m_bTurnDecided = false;
	m_opMap = m_opMap->getInstance();
}

/*
 /////////////////////////////////////////////////////////////////////////////////////
 * This is the main move algorithm. It calls the changeSpeed method to determine the *
 * vehicle's speed, calculates the next x and y points taking into account turn		 *
 * direction at next intersection, and sets the next x and y position.				 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * This algorithm was developed and is owned by Dr. Rick Coleman. It is used and     *
 * implemented here with permission.                                                 *
 /////////////////////////////////////////////////////////////////////////////////////
 */
void Truck::move() {
	double  nextX, nextY, SLmph, SLmps, midptX, midptY, distTravPerSecAC, 
		distCentNextIntAD, distToNextLaneBD, distBeforeTurnBC;
	int newNumLanes;
	Road *tempRoad;
	Road *currentRoad;
	Road *prevRoad;
	Intersection *nextIntersection;
	eColor TLstat;
	currentRoad = m_opMap->getRoad(m_dXPos, m_dYPos, m_dDirection);

	if (currentRoad == NULL) {
		Intersection *inter = m_opMap->getNextIntersection(m_dXPos, m_dYPos, m_dDirection, NULL);
		int newNumLanesNS = inter->getNumLanesNS();
		int newNumLanesEW = inter->getNumLanesEW();

		if (m_dDirection == EAST)
			m_dXPos = m_dXPos + ((newNumLanesNS == 4) ? LANE_WIDTH * 4.0 : LANE_WIDTH * 2.0);
		else if (m_dDirection == NORTH)
			m_dYPos = m_dYPos - ((newNumLanesEW == 4) ? LANE_WIDTH * 4.0 : LANE_WIDTH * 2.0);
		else if (m_dDirection == WEST)
			m_dXPos = m_dXPos - ((newNumLanesNS == 4) ? LANE_WIDTH * 4.0 : LANE_WIDTH * 2.0);
		else 
			m_dYPos = m_dYPos + ((newNumLanesEW == 4) ? LANE_WIDTH * 4.0 : LANE_WIDTH * 2.0);

		currentRoad =  m_opMap->getRoad(m_dXPos, m_dYPos, m_dDirection);
		if (currentRoad == NULL)
			exit(99);
	}

		nextIntersection = m_opMap->getNextIntersection(m_dXPos, m_dYPos, m_dDirection, currentRoad); 

		if (nextIntersection == NULL) {
			handleLocationException(&turnDirection, &nextX, &nextY);
			m_dXPos = nextX;
			m_dYPos = nextY;
			m_bTurnDecided = false;
			nextIntersection = m_opMap->getNextIntersection(m_dXPos, m_dYPos, m_dDirection, currentRoad);
			currentRoad = m_opMap->getRoad(m_dXPos, m_dYPos, m_dDirection);
		} // end if

	midptX = nextIntersection->getMidptX();
	midptY = nextIntersection->getMidptY();

	SLmph = currentRoad->getSpeedLimit();
	SLmps = SLmph * 0.44704;

	if ((m_dDirection == EAST) || (m_dDirection == WEST))
		TLstat = nextIntersection->getLightColorEW();
	else
		TLstat = nextIntersection->getLightColorNS();

	changeSpeed(currentRoad, nextIntersection);

	if (m_bTurnDecided == false) {
		turnDirection = decideTurn(currentRoad, nextIntersection, m_dDirection);
		m_bTurnDecided = true;
	} // end if

	midptX = nextIntersection->getMidptX();
	midptY = nextIntersection->getMidptY();

	distTravPerSecAC = m_dSpeedMPS;
	if (m_dDirection == EAST) {
		nextX = m_dXPos + m_dSpeedMPS;
		nextY = m_dYPos;
		if (nextX > midptX) {
			if (turnDirection == LEFT) {
				newNumLanes = (nextIntersection->getNorthRoad()->getNumLanes());
				distToNextLaneBD = ((newNumLanes == 4) ? (LANE_WIDTH * 1.5) : (LANE_WIDTH * 0.5));
				distCentNextIntAD = midptX - m_dXPos;
				distBeforeTurnBC = distTravPerSecAC - distCentNextIntAD - distToNextLaneBD;
				nextX = midptX + distToNextLaneBD;
				nextY = m_dYPos - distBeforeTurnBC;
 
				if (nextIntersection->isPtInIntersect(nextX, nextY, m_dDirection))
					nextY = nextY - (currentRoad->getNumLanes() * LANE_WIDTH);

				m_dDirection = NORTH;
			} // end if turn left
			else if (turnDirection == RIGHT) {
				newNumLanes = (nextIntersection->getSouthRoad()->getNumLanes());
				distToNextLaneBD = ((newNumLanes == 4) ? (LANE_WIDTH * 1.5) : (LANE_WIDTH * 0.5));
				distCentNextIntAD = midptX - m_dXPos;
				distBeforeTurnBC = distTravPerSecAC - distCentNextIntAD + distToNextLaneBD;
				nextX = midptX - distToNextLaneBD;
				nextY = m_dYPos + distBeforeTurnBC;
				m_dDirection = SOUTH;
			} // end else if turn right
			m_bTurnDecided = false;
		} // end if turning
	} // end move East

	else if (m_dDirection == NORTH) {
		nextX = m_dXPos;
		nextY = m_dYPos - m_dSpeedMPS;
		if (nextY < midptY) {
			if (turnDirection == LEFT) {
				newNumLanes = (nextIntersection->getWestRoad()->getNumLanes());
				distToNextLaneBD = ((newNumLanes == 4) ? (LANE_WIDTH * 1.5) : (LANE_WIDTH * 0.5));
				distCentNextIntAD = m_dYPos - midptY;
				distBeforeTurnBC = distTravPerSecAC - distCentNextIntAD - distToNextLaneBD;
				nextX = m_dXPos - distBeforeTurnBC;
				nextY = midptY - distToNextLaneBD;
 
				if (nextIntersection->isPtInIntersect(nextX, nextY, m_dDirection))
					nextX = nextX  - (currentRoad->getNumLanes() * LANE_WIDTH);

				m_dDirection = WEST;
			} // end if turn Left
			else if (turnDirection == RIGHT) {
				tempRoad = nextIntersection->getEastRoad();
				newNumLanes = tempRoad->getNumLanes();
				distToNextLaneBD = ((newNumLanes == 4) ? (LANE_WIDTH * 1.5) : (LANE_WIDTH * 0.5));
				distCentNextIntAD = m_dYPos - midptY;
				distBeforeTurnBC = distTravPerSecAC - distCentNextIntAD + distToNextLaneBD;
				nextX = m_dXPos + distBeforeTurnBC;
				nextY = midptY + distToNextLaneBD;
				m_dDirection = EAST;
			} // end if turn right
			m_bTurnDecided = false;
		} // end if turning
	} // end else if direction north

	else if (m_dDirection == WEST) {
		nextX = m_dXPos - m_dSpeedMPS;
		nextY = m_dYPos;
		if (nextX < midptX) {
			if (turnDirection == LEFT) {
				newNumLanes = (nextIntersection->getSouthRoad()->getNumLanes());
				distToNextLaneBD = ((newNumLanes == 4) ? (LANE_WIDTH * 1.5) : (LANE_WIDTH * 0.5));
				distCentNextIntAD = m_dXPos - midptX;
				distBeforeTurnBC = distTravPerSecAC - distCentNextIntAD - distToNextLaneBD;
				nextX = midptX - distToNextLaneBD;
				nextY = m_dYPos + distBeforeTurnBC;
 
				if (nextIntersection->isPtInIntersect(nextX, nextY, m_dDirection))
					nextY = nextY  + (currentRoad->getNumLanes() * LANE_WIDTH);

				m_dDirection = SOUTH;
			} // end if turn left
			if (turnDirection == RIGHT) {
				newNumLanes = (nextIntersection->getNorthRoad()->getNumLanes());
				distToNextLaneBD = ((newNumLanes == 4) ? (LANE_WIDTH * 1.5) : (LANE_WIDTH * 0.5));
				distCentNextIntAD = m_dXPos - midptX;
				distBeforeTurnBC = distTravPerSecAC - distCentNextIntAD + distToNextLaneBD;
				nextX = midptX + distToNextLaneBD;
				nextY = m_dYPos - distBeforeTurnBC;
				m_dDirection = NORTH;
			} // end if turn right
			m_bTurnDecided = false;
		} // end if turning
	} // end if direction west

	else if (m_dDirection == SOUTH) {
		nextX = m_dXPos;
		nextY = m_dYPos + m_dSpeedMPS;
		if (nextY > midptY) {
			if (turnDirection == LEFT) {
				newNumLanes = (nextIntersection->getEastRoad()->getNumLanes());
				distToNextLaneBD = ((newNumLanes == 4) ? (LANE_WIDTH * 1.5) : (LANE_WIDTH * 0.5));
				distCentNextIntAD = midptY - m_dYPos;
				distBeforeTurnBC = distTravPerSecAC - distCentNextIntAD - distToNextLaneBD;
				nextX = m_dXPos + distBeforeTurnBC;
				nextY = midptY + distToNextLaneBD;
 
				if (nextIntersection->isPtInIntersect(nextX, nextY, m_dDirection))
					nextX = nextX  + (currentRoad->getNumLanes() * LANE_WIDTH);

				m_dDirection = EAST;
			} // end if turn left
			else if (turnDirection == RIGHT) {
				tempRoad = nextIntersection->getWestRoad();
				newNumLanes = tempRoad->getNumLanes();
				distToNextLaneBD = ((newNumLanes == 4) ? (LANE_WIDTH * 1.5) : (LANE_WIDTH * 0.5));
				distCentNextIntAD = midptY - m_dYPos;
				distBeforeTurnBC = distTravPerSecAC - distCentNextIntAD + distToNextLaneBD;
				nextX = m_dXPos - distBeforeTurnBC;
				nextY = midptY - distToNextLaneBD;
				m_dDirection = WEST;
			} // end if turn right
			m_bTurnDecided = false;
		} // end if turning
	} // end else if direction south

	m_dXPos = nextX;
	m_dYPos = nextY;
	prevRoad = currentRoad;

} // end move

/*
 /////////////////////////////////////////////////////////////////////////////////////
 * This method calculates the speed the vehicle should be traveling at. It takes     *
 * into account the vehicle's rate of acceleration, the speed limit of the current   *
 * road, and the color of the light at the next intersection.						 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * This algorithm was developed and is owned by Dr. Rick Coleman. It is used and     *
 * implemented here with permission.                                                 *
 /////////////////////////////////////////////////////////////////////////////////////
 */
void Truck::changeSpeed(Road *currentRoad, Intersection *nextIntersection) {
	double SLmph = currentRoad->getSpeedLimit();
	double SLmps = SLmph * 0.44704;
	double stopDistAtVSpeed_TSDVS = ((1.1 * m_dSpeedMPH) + (0.06 * pow(m_dSpeedMPH, 2.0)));
	stopDistAtVSpeed_TSDVS *= 0.3048;
	double stopAtSL_TSDSL = ((1.1 * SLmph) + (0.06 * pow(SLmph, 2.0)));
	stopAtSL_TSDSL *= 0.3048;
	double startToMidD_BCC, vToMidD_ACC, vToStartD_AB;
	eColor lightColor;

	if (m_dDirection == EAST) {
		lightColor = nextIntersection->getLightColorEW();
		startToMidD_BCC = ((nextIntersection->getNumLanesNS() == 4) ? LANE_WIDTH * 2.0 : LANE_WIDTH * 1.0);
		vToMidD_ACC = nextIntersection->getMidptX() - m_dXPos;
		vToStartD_AB = vToMidD_ACC - startToMidD_BCC; 
	} // end if direction east

	else if (m_dDirection == NORTH) {
		lightColor = nextIntersection->getLightColorNS();
		if (nextIntersection->getEastRoad() != NULL)
			startToMidD_BCC = (nextIntersection->getEastRoad()->getNumLanes() == 4) ? LANE_WIDTH * 2.0 : LANE_WIDTH * 1.0;
		else 			
			startToMidD_BCC = (nextIntersection->getWestRoad()->getNumLanes() == 4) ? LANE_WIDTH * 2.0 : LANE_WIDTH * 1.0;

		vToMidD_ACC = m_dYPos - nextIntersection->getMidptY();
		vToStartD_AB = vToMidD_ACC - startToMidD_BCC;
	} // end direction north

	else if (m_dDirection == WEST) {
		lightColor = nextIntersection->getLightColorEW();
		if (nextIntersection->getNorthRoad() != NULL)
			startToMidD_BCC = (nextIntersection->getNorthRoad()->getNumLanes() == 4) ? LANE_WIDTH * 2.0 : LANE_WIDTH * 1.0;
		else 			
			startToMidD_BCC = (nextIntersection->getSouthRoad()->getNumLanes() == 4) ? LANE_WIDTH * 2.0 : LANE_WIDTH * 1.0;

		vToMidD_ACC = m_dXPos - nextIntersection->getMidptX();
		vToStartD_AB = vToMidD_ACC - startToMidD_BCC;
	} // end direction west

	else if (m_dDirection == SOUTH) {
		lightColor = nextIntersection->getLightColorNS();
		if (nextIntersection->getEastRoad() != NULL)
			startToMidD_BCC = (nextIntersection->getEastRoad()->getNumLanes() == 4) ? LANE_WIDTH * 2.0 : LANE_WIDTH * 1.0;
		else 			
			startToMidD_BCC = (nextIntersection->getWestRoad()->getNumLanes() == 4) ? LANE_WIDTH * 2.0 : LANE_WIDTH * 1.0;

		vToMidD_ACC = nextIntersection->getMidptY() - m_dYPos;
		vToStartD_AB = vToMidD_ACC - startToMidD_BCC;
	} // end direction south

	if ((lightColor == RED) || (lightColor == AMBER)) {
		if (stopAtSL_TSDSL < vToStartD_AB) {
			if (m_dSpeedMPS < SLmps) {
				m_dSpeedMPS += m_dAcceleration;
				m_dSpeedMPH = m_dSpeedMPS / 0.44704;
				if (m_dSpeedMPS > SLmps) {
					m_dSpeedMPS = SLmps;
					m_dSpeedMPH = SLmph;
				} // end if speed > SL
			} // end if speed < SL
		} // end if stop at speed < distance to start
		else if ((stopDistAtVSpeed_TSDVS > vToStartD_AB) && (m_dSpeedMPS != 0)) {
			while ((stopDistAtVSpeed_TSDVS > vToStartD_AB) && (vToStartD_AB > LANE_WIDTH) && (m_dSpeedMPS > 0)) {
				m_dSpeedMPS -= m_dAcceleration;
				m_dSpeedMPH = m_dSpeedMPS / 0.44704;
				if (m_dSpeedMPS < 0)
					m_dSpeedMPS = m_dSpeedMPH = 0;
				stopDistAtVSpeed_TSDVS = (1.1 * m_dSpeedMPH + 0.06 * pow(m_dSpeedMPH, 2.0));
				stopDistAtVSpeed_TSDVS *= 0.3048;
				if (m_dSpeedMPS == 0) 
					break;
			} // end while
		} //end else if stop > start dist and speed not 0

		if (vToStartD_AB < LANE_WIDTH)
			m_dSpeedMPS = m_dSpeedMPH = 0;

	} // end if light Red or Amber

	else {
		if (m_dSpeedMPS < SLmps) {
			m_dSpeedMPS += m_dAcceleration;
			m_dSpeedMPH = m_dSpeedMPS / 0.44704;
			if (m_dSpeedMPS > SLmps) {
				m_dSpeedMPS = SLmps;
				m_dSpeedMPH = m_dSpeedMPS / 0.44704;
			} // end if speed > SL
		} // end if speed < SL
	} // end else light green
} // end changeSpeed

 /*
 /////////////////////////////////////////////////////////////////////////////////////
 * This algorithm handles the situation that occurs when a call to get the next		 *
 * intersection returns NULL. It happens when a vehicle has passed the midpoint of   *
 * an edge intersection but not yet turned.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * This algorithm was developed and is owned by Dr. Rick Coleman. It is used and     *
 * implemented here with permission.                                                 *
 /////////////////////////////////////////////////////////////////////////////////////
 */
void Truck::handleLocationException(eTurnDirection *turnDirection, double *nextX, double *nextY) {

	Road *aRoad = m_opMap->getRoad(m_dXPos, m_dYPos, m_dDirection);
	Intersection *thisIntersection = m_opMap->getNextIntersection(m_dXPos, m_dYPos, m_dDirection, aRoad);

	double midpointX = thisIntersection->getMidptX();
	double midpointY = thisIntersection->getMidptY();
	int numLanesNS, numLanesEW;

	numLanesEW = thisIntersection->getNumLanesEW();
	numLanesNS = thisIntersection->getNumLanesNS();

	if (m_dDirection == EAST) {
		if (*turnDirection == LEFT) {
			*nextX = midpointX  + ((numLanesNS == 2) ? 0.5 : 1.5) * LANE_WIDTH;
			*nextY = midpointY - ((numLanesEW/2) * LANE_WIDTH);
			m_dDirection = NORTH;
		} // end if turn left
		else if (*turnDirection == RIGHT) {
			*nextX = midpointX  - ((numLanesNS == 2) ? 0.5 : 1.5) * LANE_WIDTH;
			*nextY = midpointY + ((numLanesEW/2) * LANE_WIDTH);
			m_dDirection = SOUTH;
		} // end if turn right
	} // end if direction east

	else if (m_dDirection == NORTH) {
		if (*turnDirection == LEFT) {
			*nextX = midpointX - ((numLanesNS/2) * LANE_WIDTH);
			*nextY = midpointY - ((numLanesEW == 2) ? 0.5 : 1.5) * LANE_WIDTH;
			m_dDirection = WEST;
		} // end if turn left
		else if (*turnDirection == RIGHT) {
			*nextX = midpointX + ((numLanesNS/2) * LANE_WIDTH);
			*nextY = midpointY + ((numLanesEW == 2) ? 0.5 : 1.5) * LANE_WIDTH;
			m_dDirection = EAST;
		} // end if turn right
	} // end if direction north

	else if (m_dDirection == WEST) {
		if (*turnDirection == RIGHT) {
			*nextX = midpointX  + ((numLanesNS == 2) ? 0.5 : 1.5) * LANE_WIDTH;
			*nextY = midpointY - ((numLanesEW/2) * LANE_WIDTH);
			m_dDirection = NORTH;
		} // end if turn right
		else if (*turnDirection == LEFT) {
			*nextX = midpointX  - ((numLanesNS == 2) ? 0.5 : 1.5) * LANE_WIDTH;
			*nextY = midpointY + ((numLanesEW/2) * LANE_WIDTH);
			m_dDirection = SOUTH;
		} // end if turn left
	} // end if direction west

	else if (m_dDirection == SOUTH) {
		if (*turnDirection == LEFT) {
			*nextX = midpointX + ((numLanesNS/2) * LANE_WIDTH);
			*nextY = midpointY + ((numLanesEW == 2) ? 0.5 : 1.5) * LANE_WIDTH;
			m_dDirection = EAST;
		} // end if turn left
		else if (*turnDirection == RIGHT) {
			*nextX = midpointX - ((numLanesNS/2) * LANE_WIDTH);
			*nextY = midpointY - ((numLanesEW == 2) ? 0.5 : 1.5) * LANE_WIDTH;
			m_dDirection = WEST;
		} // end if turn right
	} // end direction south
} // end handleLocationException

 /*
 /////////////////////////////////////////////////////////////////////////////////////
 * This method determines which way the vehicle should turn. It uses a random number *
 * and returns the turn direction based on the roads available at the next			 *
 * intersection. If there are two options, the chance is 50/50 for turn direction.   *
 * If there are three options, the chances are 60% for straight, and 30% each for    *
 * left or right.																	 *
 /////////////////////////////////////////////////////////////////////////////////////
 */
eTurnDirection Truck::decideTurn(Road *currentRoad, Intersection *nextIntersection, eCompassDirection currentDirection) {
	int randNum = rand() % 10;
	bool N = false, S = false, E = false, W = false;
	int count = 0;
	eTurnDirection turnDirection;

	if ((nextIntersection->getEastRoad() != NULL) && (currentDirection != WEST)) {
		E = true;
		count++;
	} // end if east road
	if ((nextIntersection->getNorthRoad() != NULL) && (currentDirection != SOUTH)) {
		N = true;
		count++;
	} // end if north road
	if ((nextIntersection->getWestRoad() != NULL) && (currentDirection != EAST)) {
		W = true;
		count++;
	} // end if west road
	if ((nextIntersection->getSouthRoad() != NULL) && (currentDirection != NORTH)) {
		S = true;
		count++;
	} // end if south road

	if (count == 1) {
		if (E == true) {	
			if (m_dDirection == SOUTH)
				turnDirection = LEFT;
			if (m_dDirection == EAST)
				turnDirection = STRAIGHT;
			if (m_dDirection == NORTH)
				turnDirection = RIGHT;
		} // end if E true
		if (N == true) {
			if (m_dDirection == EAST)
				turnDirection = LEFT;
			if (m_dDirection == NORTH)
				turnDirection = STRAIGHT;
			if (m_dDirection == WEST)
				turnDirection = RIGHT;
		} // end if N true
		if (W == true) {
			if (m_dDirection == NORTH)
				turnDirection = LEFT;
			if (m_dDirection == WEST)
				turnDirection = STRAIGHT;
			if (m_dDirection == SOUTH)
				turnDirection = RIGHT;
		} // end if W true
		if (S == true) {
			if (m_dDirection == EAST)
				turnDirection = RIGHT;
			if (m_dDirection == SOUTH)
				turnDirection = STRAIGHT;
			if (m_dDirection == WEST)
				turnDirection = LEFT;
		} // end if S true
	} // end if count = 1

	else if (count == 2) {
		if (E == true) {
			if (randNum % 2 == 0) {
				if (m_dDirection == SOUTH)
					turnDirection = LEFT;
				if (m_dDirection == EAST)
					turnDirection = STRAIGHT;
				if (m_dDirection == NORTH)
					turnDirection = RIGHT;
			} //end if randNum even
			else if (N == true) {
				if (m_dDirection == EAST)
					turnDirection = LEFT;
				if (m_dDirection == NORTH)
					turnDirection = STRAIGHT;
				if (m_dDirection == WEST)
					turnDirection = RIGHT;
			} // end if N true
			else if (W == true) {
				if (m_dDirection == NORTH)
					turnDirection = LEFT;
				if (m_dDirection == WEST)
					turnDirection = STRAIGHT;
				if (m_dDirection == SOUTH)
					turnDirection = RIGHT;
			} // end if W true
			else { // S == true
				if (m_dDirection == WEST)
					turnDirection = LEFT;
				if (m_dDirection == SOUTH)
					turnDirection = STRAIGHT;
				if (m_dDirection == EAST)
					turnDirection = RIGHT;
			} // end else S true
		} //end if E true

		else if (N == true) {
			if (randNum % 2 == 0) {
				if (m_dDirection == EAST)
					turnDirection = LEFT;
				if (m_dDirection == NORTH)
					turnDirection = STRAIGHT;
				if (m_dDirection == WEST)
					turnDirection = RIGHT;
			} // end if randNum even
			else if (W == true) {
				if (m_dDirection == NORTH)
					turnDirection = LEFT;
				if (m_dDirection == WEST)
					turnDirection = STRAIGHT;
				if (m_dDirection == SOUTH)
					turnDirection = RIGHT;
			} // end if W true
			else if (S == true) {
				if (m_dDirection == EAST)
					turnDirection = RIGHT;
				if (m_dDirection == SOUTH)
					turnDirection = STRAIGHT;
				if (m_dDirection == WEST)
					turnDirection = LEFT;
			} // end if S true
		} // end if N true

		else if (W == true) {
			if (randNum % 2 == 0) {
				if (m_dDirection == NORTH)
					turnDirection = LEFT;
				if (m_dDirection == WEST)
					turnDirection = STRAIGHT;
				if (m_dDirection == SOUTH)
					turnDirection = RIGHT;
			} // end if randNum even
			else { //S == true
				if (m_dDirection == EAST)
					turnDirection = RIGHT;
				if (m_dDirection == SOUTH)
					turnDirection = STRAIGHT;
				if (m_dDirection == WEST)
					turnDirection = LEFT;
			} // end else S true
		} // end if W true
	} // end if count = 2

	else { //count == 3
		if (randNum % 3 == 0)
			turnDirection = STRAIGHT;
		else if ((randNum == 1) || (randNum == 4) || (randNum == 7))
			turnDirection = LEFT;
		else	
			turnDirection = RIGHT;
	} // end else count = 3

	//turnDirection is a member variable now. Change functions accordingly.
	return turnDirection;
} // end decideTurn

/*
 /////////////////////////////////////////////////////////////////////////////////////
 * This method prints out a report with the vehicle ID, it's current x and y         *
 * coordinates, the current road, the direction traveling, the current speed, the    *
 * ID of the next intersection, and the direction it will turn at that intersection. *
 /////////////////////////////////////////////////////////////////////////////////////
 */
void Truck::printReport() {
	string direction;
	string turnDir;
	Road *temproad = m_opMap->getRoad(m_dXPos, m_dYPos, m_dDirection);
	Intersection *tempint = m_opMap->getNextIntersection(m_dXPos, m_dYPos, m_dDirection, temproad);
	char name[64];
	static int count = 1;
	temproad->getName(name);

	switch (turnDirection) {
	case LEFT:
		turnDir = "left";
		break;
	case RIGHT:
		turnDir = "right";
		break;
	case STRAIGHT:
		turnDir = "straight";
		break;
	}

	switch (m_dDirection) {
		case EAST:
			direction = "East";
			break;
		case NORTH:
			direction = "North";
			break;
		case WEST:
			direction = "West";
			break;
		case SOUTH:
			direction = "South";
			break;
	} // end switch

	cout << fixed;
	cout << setprecision(1);
	cout << "Vehicle #" << m_iVehicleID << " is a large truck located at (" << m_dXPos << ", " << m_dYPos << ")." << endl;
	cout << "It is traveling " << direction << " on " << name << " at " << m_dSpeedMPH << "mph." << endl;
	cout << "It will go " << turnDir << " at Intersection #" << tempint->getIntersectID() << ".\n" << endl;
} // end printReport