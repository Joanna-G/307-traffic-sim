	/*******************************************************************
	*   CS 307 Programming Assignment 3 - Traffic Simulation
	*   File: VehicleMovement.h
	*   Author: Joanna Pease
	*	Prog Desc: This program simulates traffic on a grid of roads.
	*		Vehicles travel on the roads while obeying the road's speed
	*		limit and the status of the traffic light at the upcoming
	*		intersection.
	*   File Desc: This file is the header file that lists all member
	*		variables and function prototypes for the VehicleMovement
	*		class.
	*   Date: 4/9/17
	*
	*   I attest that this program is entirely my own work, unless
	*	noted otherwise.
	*******************************************************************/

#pragma once

#include "Inclusions.h"

class VehicleMovement 
{

public:
	VehicleMovement();
	~VehicleMovement();
	virtual void move();
	virtual void changeSpeed();
	virtual void handleLocationException();
	virtual void decideTurn();
	virtual void printReport();
};