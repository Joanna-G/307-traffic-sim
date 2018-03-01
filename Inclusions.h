	/*******************************************************************
	*   CS 307 Programming Assignment 3 - Traffic Simulation
	*   File: Inclusions.h
	*   Author: Joanna Pease
	*	Prog Desc: This program simulates traffic on a grid of roads.
	*		Vehicles travel on the roads while obeying the road's speed
	*		limit and the status of the traffic light at the upcoming
	*		intersection.
	*	File Desc: This file lists all includes, forward declarations,
	*		constants, enumerated data types, and debug statements.
	*   Date: 4/9/17
	*
	*   I attest that this program is entirely my own work, unless
	*	noted otherwise.
	*******************************************************************/


#pragma once

#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <time.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

class Road;
class Vehicle;
class Intersection;

#define LANE_WIDTH 3.6

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_INSECURE_NO_DEPRECATE

//#define DEBUG1

enum eColor {RED, GREEN, AMBER};
enum eCompassDirection {EAST = 0, NORTH = 90, WEST = 180, SOUTH = 270};
enum eCarType {CAR4, CAR6, CAR8, TRUCK, SEMI};
enum eTurnDirection {STRAIGHT, LEFT, RIGHT};