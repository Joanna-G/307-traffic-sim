	/*******************************************************************
	*   CS 307 Programming Assignment 3 - Traffic Simulation
	*   File: VehicleFactory.cpp
	*   Author: Joanna Pease
	*	Prog Desc: This program simulates traffic on a grid of roads.
	*		Vehicles travel on the roads while obeying the road's speed
	*		limit and the status of the traffic light at the upcoming
	*		intersection.
	*   File Desc: This file is responsible for creating each vehicle
	*		and setting its VehicleMovement subclass
	*   Date: 4/9/17
	*
	*   I attest that this program is entirely my own work, unless
	*	noted otherwise.
	*******************************************************************/
#include "stdafx.h"
#include "VehicleFactory.h"

VehicleFactory::VehicleFactory()
{ }

VehicleFactory::~VehicleFactory()
{ }

Vehicle* VehicleFactory::createVehicle(eCarType typeEnum, int ID, double startX, double startY, eCompassDirection direction, double acc)
{
	Vehicle *tempV = new Vehicle();
	tempV->setVehicleMovement(typeEnum, ID, startX, startY, direction, acc);
	return tempV;
}

VehicleFactory *VehicleFactory::getInstance()
{
	static VehicleFactory *theInstance = NULL;
	if (theInstance == NULL)
		theInstance = new VehicleFactory();
	return theInstance;
}