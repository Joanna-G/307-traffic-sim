/*******************************************************************
*   CS 307 Programming Assignment 3 - Traffic Simulation
*   File: Map.h
*   Author: Joanna Pease
*	Prog Desc: This program simulates traffic on a grid of roads.
*		Vehicles travel on the roads while obeying the road's speed
*		limit and the status of the traffic light at the upcoming
*		intersection.
*   File Desc: This file is the header file that lists all member
*		variables and function prototypes for the Map class.
*   Date: 4/9/17
*
*   I attest that this program is entirely my own work, unless
*	noted otherwise.
*******************************************************************/

#pragma once

#include "Inclusions.h"
#include "Road.h"
#include "Intersection.h"
#include "Vehicle.h"
#include "TrafficSimDataParser.h"
#include "TrafficLightManager.h"
#include "VehicleFactory.h"

class Map {

private:
	Map();
	TrafficSimDataParser *dataParser;
	VehicleFactory *m_oVFactory;
	TrafficLightManager *m_opLightManager;
	vector<Road *> m_oRoads;
	vector<Intersection *> m_oIntersections;
	vector<Vehicle *> m_oVehicles;

public:
	~Map();
	void updateLights();
	void reportLights();
	void updateVehicles();
	void reportVehicles();
	Road* getRoad(char* name);
	Road* getRoad(double x, double y, eCompassDirection direction);
	Intersection* getIntersection(int ID);
	Intersection* getIntersection(double x, double y);
	Intersection* getNextIntersection(double x, double y, eCompassDirection direction, Road *currentRoad);
	static Map *getInstance();
	void getDataFile(TrafficSimDataParser *dp);
	void buildMap(TrafficSimDataParser *dp);
	void update();
};