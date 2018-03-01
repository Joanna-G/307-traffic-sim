	/*******************************************************************
	*   CS 307 Programming Assignment 3 - Traffic Simulation
	*   File: Vehicle.cpp
	*   Author: Joanna Pease
	*	Prog Desc: This program simulates traffic on a grid of roads.
	*		Vehicles travel on the roads while obeying the road's speed
	*		limit and the status of the traffic light at the upcoming
	*		intersection.
	*   File Desc: This file simply sets a pointer to a VehicleMovement
	*		subclass based on the type passed in. The move and print report
	*		functions call the appropriate functions in the VehicleMovement
	*		subclass pointer.
	*   Date: 4/9/17
	*
	*   I attest that this program is entirely my own work, unless
	*	noted otherwise.
	*******************************************************************/

#include "stdafx.h"
#include "Vehicle.h"
#include "VehicleMovement.h"
#include "Car4Cyl.h"
#include "Car6Cyl.h"
#include "Car8Cyl.h"
#include "Truck.h"
#include "Semi.h"

Vehicle::Vehicle() 
{ } // end default constructor

Vehicle::~Vehicle() 
{ }

void Vehicle::setVehicleMovement(eCarType typeEnum, int ID, double startX, double startY, 
		eCompassDirection direction, double acc)
{
	switch (typeEnum) {
	case CAR4:
		m_opVMovement = new Car4Cyl(typeEnum, ID, startX, startY, direction, acc);
		break;
	case CAR6:
		m_opVMovement = new Car6Cyl(typeEnum, ID, startX, startY, direction, acc);
		break;
	case CAR8:
		m_opVMovement = new Car8Cyl(typeEnum, ID, startX, startY, direction, acc);
		break;
	case TRUCK:
		m_opVMovement = new Truck(typeEnum, ID, startX, startY, direction, acc);
		break;
	case SEMI:
		m_opVMovement = new Semi(typeEnum, ID, startX, startY, direction, acc);
		break;
	}
}

void Vehicle::move()
{
	m_opVMovement->move();
}

void Vehicle::printReport()
{
	m_opVMovement->printReport();
}