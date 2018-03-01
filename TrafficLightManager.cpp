	/*******************************************************************
	*   CS 307 Programming Assignment 3 - Traffic Simulation
	*   File: TrafficLightManager.cpp
	*   Author: Joanna Pease
	*	Prog Desc: This program simulates traffic on a grid of roads.
	*		Vehicles travel on the roads while obeying the road's speed
	*		limit and the status of the traffic light at the upcoming
	*		intersection.
	*   File Desc: This file is responsible for managing the traffic
	*		light. It is responsible for changing the color of the
	*		traffic light and reporting its status to other classes.
	*   Date: 4/9/17
	*
	*   I attest that this program is entirely my own work, unless
	*	noted otherwise.
	*******************************************************************/
#include "stdafx.h"
#include "TrafficLightManager.h"

TrafficLightManager::TrafficLightManager()
{
	m_opLight = m_opLight->getInstance();
}

TrafficLightManager::~TrafficLightManager()
{
}

 TrafficLightManager *TrafficLightManager::getInstance()
{
	static TrafficLightManager *theLMInstance = NULL;
	if (theLMInstance == NULL)
		theLMInstance = new TrafficLightManager();
	return theLMInstance;
}
eColor TrafficLightManager::getColorNS()
{
	return m_opLight->getColorNS();
}
void TrafficLightManager::changeColorNS()
{
	m_opLight->changeColorNS();
}
eColor TrafficLightManager::getColorEW()
{
	return m_opLight->getColorEW();
}
void TrafficLightManager::changeColorEW()
{
	m_opLight->changeColorEW();
}