	/*******************************************************************
	*   CS 307 Programming Assignment 3 - Traffic Simulation
	*   File: Road.h
	*   Author: Joanna Pease
	*	Prog Desc: This program simulates traffic on a grid of roads.
	*		Vehicles travel on the roads while obeying the road's speed
	*		limit and the status of the traffic light at the upcoming
	*		intersection.
	*   File Desc: This file is the header file that lists all member
	*		variables and function prototypes for the Road class.
	*   Date: 4/9/17
	*
	*   I attest that this program is entirely my own work, unless
	*	noted otherwise.
	*******************************************************************/

#pragma once

#include "Inclusions.h"
#include "Intersection.h"

class Road {

private:
	char m_cName[64];
	double m_dStartPointX;
	double m_dStartPointY;
	double m_dEndPointX;
	double m_dEndPointY;
	double m_dUpLeftX;
	double m_dUpLeftY;
	double m_dLowRightX;
	double m_dLowRightY;
	double m_dSpeedLimit;
	int m_iStartInt;
	int m_iEndInt;
	int m_iNumLanes;
	Intersection *m_opStartIntersect;
	Intersection *m_opEndIntersect;
	eCompassDirection m_eDirection;

public:
	Road(char *name, double startX, double startY, double endX, double endY, int startInt, int endInt, double spdLimit, int numLanes);
	bool isPointOnRoad(double x, double y, eCompassDirection direction);
	void getName(char *name);
	double getUpLeftX();
	double getUpLeftY();
	double getLowRightX();
	double getLowRightY();
	double getSpeedLimit();
	int getStartIntersectID();
	int getEndIntersectID();
	int getNumLanes();
	Intersection *getStartIntersect();
	void setStartIntersect(Intersection *startIntersect);
	Intersection *getEndIntersect();
	void setEndIntersect(Intersection *endIntersect);
	eCompassDirection getDirection();
};