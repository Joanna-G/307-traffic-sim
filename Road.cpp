	/*******************************************************************
	*   CS 307 Programming Assignment 3 - Traffic Simulation
	*   File: Road.cpp
	*   Author: Joanna Pease
	*	Prog Desc: This program simulates traffic on a grid of roads.
	*		Vehicles travel on the roads while obeying the road's speed
	*		limit and the status of the traffic light at the upcoming
	*		intersection.
	*   File Desc: This file is responsible for creating Roads.
	*		It defines the name, start and end points and intersections,
	*		speed limit, number of lanes, and bounding rectangle.
	*		It also provides a method of determining if a point is on
	*		this road.
	*   Date: 4/9/17
	*
	*   I attest that this program is entirely my own work, unless
	*	noted otherwise.
	*******************************************************************/

#include "stdafx.h"
#include "Road.h"

// Create a road and calculate bounding rectangle
Road::Road(char *name, double startX, double startY, double endX, double endY, int startInt, int endInt, double spdLimit, int numLanes) {
	strcpy(m_cName, name);
	m_dStartPointX = startX;
	m_dStartPointY = startY;
	m_dEndPointX = endX;
	m_dEndPointY = endY;
	m_iStartInt = startInt;
	m_iEndInt = endInt;
	m_dSpeedLimit = spdLimit;
	m_iNumLanes = numLanes;
	m_opStartIntersect = NULL;
	m_opEndIntersect = NULL;

	// Calculate bounding rectangle and direction for NS roads
	if (m_dStartPointX == m_dEndPointX) {
		m_eDirection = NORTH;
		m_dUpLeftX = m_dStartPointX - (m_iNumLanes/2 * LANE_WIDTH);
		m_dUpLeftY = m_dStartPointY;
		m_dLowRightX = m_dEndPointX + (m_iNumLanes/2 * LANE_WIDTH);
		m_dLowRightY = m_dEndPointY;
	} // end if

	// Calculate bounding rectangle and direction for EW roads
	else if (m_dStartPointY == m_dEndPointY) {
		m_eDirection = EAST;
		m_dUpLeftX = m_dStartPointX;
		m_dUpLeftY = m_dStartPointY - (m_iNumLanes/2 * LANE_WIDTH);
		m_dLowRightX = m_dEndPointX;
		m_dLowRightY = m_dEndPointY + (m_iNumLanes/2 * LANE_WIDTH);
	} // end else if
} // end Road

/*
 /////////////////////////////////////////////////////////////////////////////////////
 * Determine if a point is within the bounding rectangle of the road.				 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * This algorithm was developed and is owned by Dr. Rick Coleman. It is used and     *
 * implemented here with permission.                                                 *
 /////////////////////////////////////////////////////////////////////////////////////
 */
bool Road::isPointOnRoad(double x, double y, eCompassDirection direction) {
	if ((x >= m_dUpLeftX) && (x <= m_dLowRightX) && (y >= m_dUpLeftY) && (y <= m_dLowRightY)) {
		if ((m_eDirection == NORTH) && ((direction == NORTH) || (direction == SOUTH)))
			return true;
		else if ((m_eDirection == EAST) && ((direction == EAST) || (direction == WEST)))
			return true;
		else
			return false;
	} // end if
	return false;
} // end isPointOnRoad

void Road::getName(char *name) {
	 strcpy(name, m_cName);
} 

double Road::getUpLeftX() {
	return m_dUpLeftX;
} 

double Road::getUpLeftY() {
	return m_dUpLeftY;
} 

double Road::getLowRightX() {
	return m_dLowRightX;
}

double Road::getLowRightY() {
	return m_dLowRightY;
}

double Road::getSpeedLimit() {
	return m_dSpeedLimit;
}

int Road::getNumLanes() {
	return m_iNumLanes;
}

int Road::getStartIntersectID() {
	return m_iStartInt;
}

int Road::getEndIntersectID() {
	return m_iEndInt;
}

Intersection *Road::getStartIntersect() {
	return m_opStartIntersect;
}

void Road::setStartIntersect(Intersection *startIntersect) {
	m_opStartIntersect = startIntersect;
}

Intersection *Road::getEndIntersect() {
	return m_opEndIntersect;

}

void Road::setEndIntersect(Intersection *endIntersect) {
	m_opEndIntersect = endIntersect;
}

eCompassDirection Road::getDirection() {
	return m_eDirection;
}