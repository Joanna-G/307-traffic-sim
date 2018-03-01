	/*******************************************************************
	*   CS 307 Programming Assignment 3 - Traffic Simulation
	*   File: Semi.h
	*   Author: Joanna Pease
	*	Prog Desc: This program simulates traffic on a grid of roads.
	*		Vehicles travel on the roads while obeying the road's speed
	*		limit and the status of the traffic light at the upcoming
	*		intersection.
	*   File Desc: This file is the header file that lists all member
	*		variables and function prototypes for the Semi subclass
	*		of the VehicleMovement class.
	*   Date: 4/9/17
	*
	*   I attest that this program is entirely my own work, unless
	*	noted otherwise.
	*******************************************************************/

#pragma once

#include "Inclusions.h"
#include "Map.h"
#include "Road.h"
#include "Intersection.h"
#include "VehicleMovement.h"

class Semi : public VehicleMovement
{

private:
	int m_iVehicleID;
	double m_dXPos;
	double m_dYPos;
	double m_dAcceleration;
	eCompassDirection m_dDirection;
	double m_dSpeedMPH;
	double m_dSpeedMPS;
	bool m_bTurnDecided;
	eTurnDirection turnDirection;
	Map *m_opMap;

public:
	Semi(eCarType typeEnum, int ID, double startX, double startY, eCompassDirection direction, double acc);
	~Semi();
	void move();
	void changeSpeed(Road *currentRoad, Intersection *nextIntersection);
	void handleLocationException(eTurnDirection *turnDirection, double *nextX, double *nextY);
	eTurnDirection decideTurn(Road *currentRoad, Intersection *nextIntersection, eCompassDirection currentDirection);
	double getXPos();
	double getYPos();
	eCompassDirection getDirection();
	double getSpeedMPH();
	double getSpeedMPS();
	eCarType  getType();
	double getAcceleration();
	eTurnDirection getTurnDirection();
	void printReport();

};