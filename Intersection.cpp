	/*******************************************************************
	*   CS 307 Programming Assignment 3 - Traffic Simulation
	*   File: Intersection.cpp
	*   Author: Joanna Pease
	*	Prog Desc: This program simulates traffic on a grid of roads.
	*		Vehicles travel on the roads while obeying the road's speed
	*		limit and the status of the traffic light at the upcoming
	*		intersection.
	*   File Desc: This file is responsible for creating Intersections.
	*		It defines the ID, mid-point, Roads, bounding rectangle,
	*		number of lanes of the North/South road, number of lanes
	*		of the East/West road, and the pointer to the traffic 
	*		light manager. It also provides a method of determining if 
	*		a point is in this intersection.
	*   Date: 4/9/17
	*
	*   I attest that this program is entirely my own work, unless
	*	noted otherwise.
	*******************************************************************/

#include "stdafx.h"
#include "Intersection.h"

Intersection::Intersection(int ID, double midptX, double midptY, Road *rdE, Road *rdN, Road *rdW, Road *rdS) {
	m_iIntersectID = ID;
	m_dIntersectMidPtX = midptX;
	m_dIntersectMidPtY = midptY;
	m_opEastRd = rdE;
	m_opNorthRd = rdN;
	m_opWestRd = rdW;
	m_opSouthRd = rdS;
	m_dUpLeftX = 0.0;
	m_dUpLeftY = 0.0;
	m_dLowRightX = 0.0;
	m_dLowRightY = 0.0;

	int numLanesNS, numLanesEW;

	if (m_opSouthRd != NULL)
		numLanesNS = m_opSouthRd->getNumLanes();
	else 
		numLanesNS = m_opNorthRd->getNumLanes();

	if (m_opEastRd != NULL)
		numLanesEW = m_opEastRd->getNumLanes();
	else
		numLanesEW = m_opWestRd->getNumLanes();

	m_dUpLeftX = m_dIntersectMidPtX - (numLanesNS/2 * LANE_WIDTH);
	m_dUpLeftY = m_dIntersectMidPtY - (numLanesEW/2 * LANE_WIDTH);
	m_dLowRightX = m_dIntersectMidPtX + (numLanesNS/2 * LANE_WIDTH);
	m_dLowRightY = m_dIntersectMidPtY + (numLanesEW/2 * LANE_WIDTH);

	m_iNumLanesNS = numLanesNS;
	m_iNumLanesEW = numLanesEW;

	m_opLightManager = m_opLightManager->getInstance();
} // end Intersection

Intersection::~Intersection() {
} // end ~Intersection

int Intersection::getIntersectID() {
	return m_iIntersectID;
}

int Intersection::getNumLanesNS() {
	return m_iNumLanesNS;
}

int Intersection::getNumLanesEW() {
	return m_iNumLanesEW;
}

double Intersection::getMidptX() {
	return m_dIntersectMidPtX;
}

double Intersection::getMidptY() {
	return m_dIntersectMidPtY;
}

double Intersection::getUpLeftX() {
	return m_dUpLeftX;
}

double Intersection::getUpLeftY() {
	return m_dUpLeftY;
}

double Intersection::getLowRightX() {
	return m_dLowRightX;
}

double Intersection::getLowRightY() {
	return m_dLowRightY;
}

Road *Intersection::getEastRoad() {
	return m_opEastRd;
}

Road *Intersection::getNorthRoad() {
	return m_opNorthRd;
}

Road *Intersection::getWestRoad() {
	return m_opWestRd;
}

Road *Intersection::getSouthRoad() {
	return m_opSouthRd;
}

/*
 /////////////////////////////////////////////////////////////////////////////////////
 * Determine if a point is in an intersection given x, y coordinates and direction   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * This algorithm was developed and is owned by Dr. Rick Coleman. It is used and     *
 * implemented here with permission.                                                 *
 /////////////////////////////////////////////////////////////////////////////////////
 */
bool Intersection::isPtInIntersect(double x, double y, eCompassDirection direction) {
	if ((x >= m_dUpLeftX) && (x <= m_dLowRightX) && (y >= m_dUpLeftY) && (y <= m_dLowRightY))
		return true;
	else
		return false;
} // end isPtInIntersect

eColor Intersection::getLightColorNS()
{
	return m_opLightManager->getColorNS();
}

eColor Intersection::getLightColorEW()
{
	return m_opLightManager->getColorEW();
}