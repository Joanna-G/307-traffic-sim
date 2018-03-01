	/*******************************************************************
	*   CS 307 Programming Assignment 3 - Traffic Simulation
	*   File: TrafficLight.h
	*   Author: Joanna Pease
	*	Prog Desc: This program simulates traffic on a grid of roads.
	*		Vehicles travel on the roads while obeying the road's speed
	*		limit and the status of the traffic light at the upcoming
	*		intersection.
	*   File Desc: This file is the header file that lists all member
	*		variables and function prototypes for the TrafficLight 
	*		class.
	*   Date: 4/9/17
	*
	*   I attest that this program is entirely my own work, unless
	*	noted otherwise.
	*******************************************************************/

#pragma once

#include "Inclusions.h"

class TrafficLight {

private:
	TrafficLight();
	eColor m_eColorNS;
	eColor m_eColorEW;
	int m_iTimerNS;
	int m_iTimerEW;

public:
	~TrafficLight();
	eColor getColorNS();
	void changeColorNS();
	eColor getColorEW();
	void changeColorEW();
	static TrafficLight *getInstance();
};