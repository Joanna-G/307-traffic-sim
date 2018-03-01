
	/*******************************************************************
	*   CS 307 Programming Assignment 3 - Traffic Simulation
	*   File: Map.cpp
	*   Author: Joanna Pease
	*	Prog Desc: This program simulates traffic on a grid of roads.
	*		Vehicles travel on the roads while obeying the road's speed
	*		limit and the status of the traffic light at the upcoming
	*		intersection.
	*   File Desc: This file is responsible for instantiating and collecting
	*		roads, intersections, and vehicles. It also contains utility
	*		functions for getting the current and next intersection, finding
	*		a road by name or location, and updating and reporting lights
	*		and vehicles.
	*   Date: 4/9/17
	*
	*   I attest that this program is entirely my own work, unless
	*	noted otherwise.
	*******************************************************************/

#include "stdafx.h"
#include "Map.h"

//Constructor
Map::Map() {
} // end map

// Clear vectors of vehicles, intersections, and roads
Map::~Map() {
//	m_oVehicles.clear();
//	m_oIntersections.clear();
//	m_oRoads.clear();
} // end ~Map

void Map::buildMap(TrafficSimDataParser *dp)
{
	//Local Variables for creating roads, intersection, and vehicles
	double startX, startY, endX, endY, spdLimit, midx, midy, startDir, acc;
	char name[64], rdE[64], rdN[64], rdW[64], rdS[64], type[64];
	int numLanes, ID, startInt, endInt;
	Road *roadE = NULL;
	Road *roadN = NULL;
	Road *roadW = NULL;
	Road *roadS = NULL;
	eCarType typeEnum;
	eCompassDirection direction;
	m_opLightManager = m_opLightManager->getInstance();
	m_oVFactory = m_oVFactory->getInstance();

	//Get and store all the roads
	for (int i = 0; i < dp->getRoadCount(); i++) {
		dp->getRoadData(name, &startX, &startY, &endX, &endY, &startInt, &endInt, &spdLimit, &numLanes);
		m_oRoads.push_back(new Road(name, startX, startY, endX, endY, startInt, endInt, spdLimit, numLanes));
	} // end for

	//Get and store all intersections
	for (int i = 0; i < dp->getIntersectionCount(); i++) {
		dp->getIntersectionData(&ID, &midx, &midy, rdN, rdE, rdS, rdW);

		// Get pointers to roads
		roadE = getRoad(rdE);
		roadN = getRoad(rdN);
		roadW = getRoad(rdW);
		roadS = getRoad(rdS);

		m_oIntersections.push_back(new Intersection(ID, midx, midy, roadE, roadN, roadW, roadS));
		roadE = roadN = roadW = roadS = NULL;
	} // end for adding Intersections

	//Loop through roads and intersections to set pointers to correct intersections
	for (vector<Road *>::iterator itrRoad = m_oRoads.begin(); itrRoad != m_oRoads.end(); itrRoad++) {
		for (vector<Intersection *>::iterator itrIntersect = m_oIntersections.begin(); itrIntersect != m_oIntersections.end(); itrIntersect++) {
			if ((*itrIntersect)->getIntersectID() == (*itrRoad)->getStartIntersectID())
				(*itrRoad)->setStartIntersect(*itrIntersect);
			else if((*itrIntersect)->getIntersectID() == (*itrRoad)->getEndIntersectID())
				(*itrRoad)->setEndIntersect(*itrIntersect);
		} // end for Intersections
	} // end for Roads
	
	//Add vehicle to vector of vehicles
	for (int i = 0; i < dp->getVehicleCount(); i++) {
		dp->getVehicleData(type, &ID, &startX, &startY, &startDir, &acc);
		
		//Translate double start direction into enumerated direction
		if(startDir == 0.0)
			direction = EAST;
		else if (startDir == 90.0)
			direction = NORTH;
		else if (startDir == 180.0)
			direction = WEST;
		else
			direction = SOUTH;

		//Translate char array type into enumerated type
		if (strcmp(type, "4-CYLINDER_CAR") == 0)
			typeEnum = CAR4;
		else if (strcmp(type, "6-CYLINDER_CAR") == 0)
			typeEnum = CAR6;
		else if (strcmp(type, "8-CYLINDER_CAR") == 0)
			typeEnum = CAR8;
		else if (strcmp(type, "LARGE_TRUCK") == 0)
			typeEnum = TRUCK;
		else
			typeEnum = SEMI;

		Vehicle *tempV = m_oVFactory->createVehicle(typeEnum, ID, startX, startY, direction, acc);
		m_oVehicles.push_back(tempV);
	}
}

// Update status of traffic light
void Map::updateLights() {
	m_opLightManager->changeColorEW();
	m_opLightManager->changeColorNS();
} // end updateLights

// Report the color of traffic light
void Map::reportLights() {
	
	//Color of EW lights
    switch (m_opLightManager->getColorEW()) {
        case RED:
            cout << "The lights facing East and West are red." << endl;
            break;
        case GREEN:
            cout << "The lights facing East and West are green." << endl;
            break;
        case AMBER:
            cout << "The lights facing East and West are amber." << endl;
            break;
    } // end switch

	// Color of NS lights
    switch (m_opLightManager->getColorNS()) {
        case RED:
            cout << "The lights facing North and South are red." << endl;
            break;
        case GREEN:
            cout << "The lights facing North and South are green." << endl;
            break;
        case AMBER:
            cout << "The lights facing North and South are amber." << endl;
            break;
    } // end switch
} // end reportLights

// Iterate through roads and return the road matching the name
Road* Map::getRoad(char* name) {
	for (vector<Road *>::iterator itr = m_oRoads.begin(); itr != m_oRoads.end(); itr++) {
		char itrName[64];
		(*itr)->getName(itrName);
		if (strcmp(itrName, name) == 0)
			return *itr;
	} // end for

	return NULL;

} // end getRoad by Name

/*
 /////////////////////////////////////////////////////////////////////////////////////
 * Iterate through roads to find the one matching the x, y point and direction	     *
 * traveling.																		 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * This algorithm was developed and is owned by Dr. Rick Coleman. It is used and     *
 * implemented here with permission.                                                 *
 /////////////////////////////////////////////////////////////////////////////////////
 */
Road* Map::getRoad(double x, double y, eCompassDirection direction) {
	bool isNS;
	double lowrighty, lowrightx, uplefty, upleftx;

	for (vector<Road *>::iterator itr = m_oRoads.begin(); itr != m_oRoads.end(); itr++) {
		upleftx = (*itr)->getUpLeftX();
		uplefty = (*itr)->getUpLeftY();
		lowrightx = (*itr)->getLowRightX();
		lowrighty = (*itr)->getLowRightY();
		
		if ((*itr)->getDirection() == NORTH)
			isNS = true;
		else
			isNS = false;

		if ((x >= upleftx) && (x <= lowrightx) && (y >= uplefty) && (y <= lowrighty)) {
				if ((isNS) && ((direction == NORTH) || (direction == SOUTH)))
					return *itr;
				else if ((!isNS) && ((direction == EAST) || (direction == WEST)))
					return *itr;
		} // end if
	} // end for road loop

	return NULL;
}// end getRoad by x, y and direction

//Iterate through intersections to find an intersection by ID
Intersection* Map::getIntersection(int ID) {
	for (vector<Intersection *>::iterator itr = m_oIntersections.begin(); itr != m_oIntersections.end(); itr++) {
		if ((*itr)->getIntersectID() == ID)
			return *itr;
	} // end for

	//Return NULL if not found
	return NULL;
} // end getIntersection by ID

/*
 /////////////////////////////////////////////////////////////////////////////////////
 * Iterate through intersections to find one by current position.					 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * This algorithm was developed and is owned by Dr. Rick Coleman. It is used and     *
 * implemented here with permission.                                                 *
 /////////////////////////////////////////////////////////////////////////////////////
 */
Intersection* Map::getIntersection(double x, double y) {
	for (vector<Intersection *>::iterator itr = m_oIntersections.begin(); itr != m_oIntersections.end(); itr++) {
		double upleftx = (*itr)->getUpLeftX();
		double uplefty = (*itr)->getUpLeftY();
		double lowrightx = (*itr)->getLowRightX();
		double lowrighty = (*itr)->getLowRightY();

		if ((x >= upleftx) && (x <= lowrightx) && (y >= uplefty) && (y <= lowrighty))
			return *itr;
	} // end for

	// Return NULL if not found
	return NULL;
} // end getIntersection by x, y

/*
 /////////////////////////////////////////////////////////////////////////////////////
 * Iterate through Intersections and find the one that is next up.					 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * This algorithm was developed and is owned by Dr. Rick Coleman. It is used and     *
 * implemented here with permission.                                                 *
 /////////////////////////////////////////////////////////////////////////////////////
 */
Intersection* Map::getNextIntersection(double x, double y, eCompassDirection direction, Road *currentRoad) {

	//Local variables
	double minDistance = 9558.25;
	double distance;
	Intersection *nextIntersection = NULL;
	bool checkIntersection = false;

	for (vector<Intersection *>::iterator itr = m_oIntersections.begin(); itr != m_oIntersections.end(); itr++) {
		checkIntersection = false;
		if ((direction == EAST) && ((*itr)->getWestRoad() == currentRoad) && (x < (*itr)->getMidptX()))
			checkIntersection = true;
		else if ((direction == NORTH) && ((*itr)->getSouthRoad() == currentRoad) && (y > (*itr)->getMidptY()))
			checkIntersection = true;
		else if ((direction == WEST) && ((*itr)->getEastRoad() == currentRoad) && (x > (*itr)->getMidptX()))		
			checkIntersection = true;
		else if ((direction == SOUTH) && ((*itr)->getNorthRoad() == currentRoad) && (y < (*itr)->getMidptY()))
			checkIntersection = true;

		if (checkIntersection == true) {
			double midptx = (*itr)->getMidptX();
			double midpty = (*itr)->getMidptY();
			distance = sqrt(pow((x - midptx), 2.0) + pow((y - midpty), 2.0));
			if (distance < minDistance) {
				minDistance = distance;
				nextIntersection = *itr;
			} // end if
		} // end if
	} // end for

	return nextIntersection;
}// end getNextIntersection

void Map::updateVehicles() {
	for(vector<Vehicle *>::iterator itr = m_oVehicles.begin(); itr < m_oVehicles.end(); itr++)
		(*itr)->move();
} // end updateVehicles

void Map::reportVehicles() {
	for(vector<Vehicle *>::iterator itr = m_oVehicles.begin(); itr < m_oVehicles.end(); itr++) {
		(*itr)->printReport();
	} // end for
} // end reportVehicles

Map *Map::getInstance()
{
	static Map *theInstance = NULL;
	if (theInstance == NULL)
		theInstance = new Map();
	return theInstance;
}

void Map::getDataFile(TrafficSimDataParser *dp)
{
	dataParser = dp;
}

void Map::update() {
	updateLights();
	updateVehicles();
}