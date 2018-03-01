	/*******************************************************************
	*   CS 307 Programming Assignment 3 - Traffic Simulation
	*   File: Simulation.h
	*   Author: Joanna Pease
	*	Prog Desc: This program simulates traffic on a grid of roads.
	*		Vehicles travel on the roads while obeying the road's speed
	*		limit and the status of the traffic light at the upcoming
	*		intersection.
	*   File Desc: This file is the header file that lists all member
	*		variables and function prototypes for the Simulation class.
	*   Date: 4/9/17
	*
	*   I attest that this program is entirely my own work, unless
	*	noted otherwise.
	*******************************************************************/

#pragma once

#include "Inclusions.h"
#include "Map.h"
#include "TrafficSimDataParser.h"

class Simulation {

private:
	Simulation();
	Map *m_oMap;
	TrafficSimDataParser *dataParser;

public:
	~Simulation();
	//void run();
	void update(double time);
	void build(TrafficSimDataParser *dataParser);
	static Simulation *getInstance();

};