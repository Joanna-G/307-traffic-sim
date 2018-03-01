
	/*******************************************************************
	*   CS 307 Programming Assignment 3 - Traffic Simulation
	*   File: VehicleMovement.cpp
	*   Author: Joanna Pease
	*	Prog Desc: This program simulates traffic on a grid of roads.
	*		Vehicles travel on the roads while obeying the road's speed
	*		limit and the status of the traffic light at the upcoming
	*		intersection.
	*   File Desc: This is a generic parent class for the VehicleMovement
			subclasses.
	*   Date: 4/9/17
	*
	*   I attest that this program is entirely my own work, unless
	*	noted otherwise.
	*******************************************************************/

#include "stdafx.h"
#include "VehicleMovement.h"

VehicleMovement::VehicleMovement()
{ 
}

VehicleMovement::~VehicleMovement()
{ 
}

void VehicleMovement::move()
{ 
	cout << "All subclasses must implement their own move." << endl;
}

void VehicleMovement::changeSpeed()
{ 
	cout << "All subclasses must implement their own changeSpeed." << endl;
}

void VehicleMovement::handleLocationException()
{ 	
	cout << "All subclasses must implement their own handleLocationException." << endl;
}

void VehicleMovement::decideTurn()
{ 
	cout << "All subclasses must implement their own decideTurn." << endl;
}

void VehicleMovement::printReport()
{ 
	cout << "All subclasses must implement their own printReport." << endl;
}