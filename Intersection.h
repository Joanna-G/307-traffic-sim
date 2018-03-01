	/*******************************************************************
	*   CS 307 Programming Assignment 3 - Traffic Simulation
	*   File: Intersection.h
	*   Author: Joanna Pease
	*	Prog Desc: This program simulates traffic on a grid of roads.
	*		Vehicles travel on the roads while obeying the road's speed
	*		limit and the status of the traffic light at the upcoming
	*		intersection.
	*   File Desc: This file is the header file that lists all member
	*		variables and function prototypes for the Intersection class.
	*   Date: 4/9/17
	*
	*   I attest that this program is entirely my own work, unless
	*	noted otherwise.
	*******************************************************************/

#pragma once

#include "Inclusions.h"
#include "Road.h"
#include "TrafficLightManager.h"

class Intersection {

private:
	int m_iIntersectID;
	int m_iNumLanesNS;
	int m_iNumLanesEW;
	double m_dIntersectMidPtX;
	double m_dIntersectMidPtY;
	double m_dUpLeftX;
	double m_dUpLeftY;
	double m_dLowRightX;
	double m_dLowRightY;
	Road *m_opEastRd;
	Road *m_opNorthRd;
	Road *m_opWestRd;
	Road *m_opSouthRd;
	TrafficLightManager *m_opLightManager;

public:
	Intersection(int ID, double midptX, double midptY, Road *rdE, Road *rdN, Road *rdW, Road *rdS);
	~Intersection();
	int getIntersectID();
	int getNumLanesNS();
	int getNumLanesEW();
	double getMidptX();
	double getMidptY();
	double getUpLeftX();
	double getUpLeftY();
	double getLowRightX();
	double getLowRightY();
	Road *getEastRoad();
	Road *getNorthRoad();
	Road *getWestRoad();
	Road *getSouthRoad();
	bool isPtInIntersect(double x, double y, eCompassDirection direction);
	eColor getLightColorNS();
	eColor getLightColorEW();

};