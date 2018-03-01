	/*******************************************************************
	*   CS 307 Programming Assignment 3 - Traffic Simulation
	*   File: Vehicle.h
	*   Author: Joanna Pease
	*	Prog Desc: This program simulates traffic on a grid of roads.
	*		Vehicles travel on the roads while obeying the road's speed
	*		limit and the status of the traffic light at the upcoming
	*		intersection.
	*   File Desc: This file is the header file that lists all member
	*		variables and function prototypes for the Vehicle class.
	*   Date: 4/9/17
	*
	*   I attest that this program is entirely my own work, unless
	*	noted otherwise.
	*******************************************************************/

#pragma once

#include "Inclusions.h"
#include "VehicleMovement.h"

class Vehicle {

private:
	eCarType m_eCarType;
	VehicleMovement *m_opVMovement;

public:
	Vehicle();
	~Vehicle();
	void move();
	void setVehicleMovement(eCarType typeEnum, int ID, double startX, double startY, eCompassDirection direction, double acc);
	void printReport();
};