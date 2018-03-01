/*******************************************************************
	*   CS 307 Programming Assignment 3 - Traffic Simulation
	*   File: Simulation.cpp
	*   Author: Joanna Pease
	*	Prog Desc: This program simulates traffic on a grid of roads.
	*		Vehicles travel on the roads while obeying the road's speed
	*		limit and the status of the traffic light at the upcoming
	*		intersection.
	*   File Desc: This file is responsible for creating the Simulation.
	*		It controls the main user interface and timing loop of the  
	*		program. It instantiates the map and builds it, passing in the
	*		data parser. It calls the map to update and report vehicles and
	*		the traffic light.
	*   Date: 4/9/17
	*
	*   I attest that this program is entirely my own work, unless
	*	noted otherwise.
	*******************************************************************/

#include "stdafx.h"
#include "Simulation.h"

Simulation::Simulation() {
	
	//cout << "Welcome to Traffic Simulator 3.0." << endl;

	//Get data filename from the user
	char filename[64];

#ifdef DEBUG1
	strcpy(filename, "TrafficSim03.xml");
#endif

#ifndef DEBUG1
    //cout << "Please enter a filename." << endl;
	//cin.getline(filename, 63, '\n');
#endif // !DEBUG1

    dataParser = dataParser->getInstance();
	dataParser->setDataFileName(filename);
}

//Delete the map, data parser, and clear the vector of vehicles
Simulation::~Simulation() {
    delete m_oMap;
    delete dataParser;
}

void Simulation::update(double time) {
	m_oMap->update();
}

void Simulation::build(TrafficSimDataParser *dataParser) {
	    m_oMap = m_oMap->getInstance();
		m_oMap->buildMap(dataParser);

}

// Starts the Simulation
//void Simulation::run() {
//
///*
// /////////////////////////////////////////////////////////////////////////////////////
// * The main loop. Updates based on running time and outputs a report every 5 seconds *
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
// * The main algorithm and timing loop were developed and are owned by Dr. Rick       *
// * Coleman. They are used and implemented here with permission.                      *
// /////////////////////////////////////////////////////////////////////////////////////
// */    
//	struct _timeb   tStruct;
//    double          thisTime, outputTime, pastTime;
//	double			elapsedTime = 0;
//    bool            done = false;  // while loop flag
//	int				runningTime = 1;
//	int				userChoice = 1;
//	int				count = 0;
//
//    _ftime(&tStruct);	// Get start time
//    thisTime = tStruct.time + (((double)(tStruct.millitm)) / 1000); // Convert to double
//    outputTime = thisTime + 5.0; // Set next 5 second interval time
//	pastTime = thisTime;
//
//	//cout << "Please choose a running time." << endl;
//	//cout << "Press 1 for real time." << endl;
//	//cout << "Press 2 for 2x time." << endl;
//	//cout << "Press 5 for 5x time." << endl;
//	//cout << "Press 0 to quit the simulation." << endl;
//	//cin >> userChoice;
//
//	//switch (userChoice) {
//	//case 1:
//	//	runningTime = 1;
//	//	break;
//	//case 2:
//	//	runningTime = 2;
//	//	break;
//	//case 5:
//	//	runningTime = 5;
//	//	break;
//	//case 0:
//	//	cout << "Goodbye." << endl;
//	//	exit(0);
//	//default:
//	//	cout << "That selection is invalid. Proceeding at real time." << endl;
//	//} // end switch
//
//    while(!done)     // Start an eternal loop
//    {
//        _ftime(&tStruct);    // Get the current time
//        thisTime = tStruct.time + (((double)(tStruct.millitm)) / 1000); // Convert to double
//
//		elapsedTime = elapsedTime + (thisTime - pastTime);
//		pastTime = thisTime;
//
//  //      // Check for 5 second interval to print status to screen
//  //      if (thisTime >= outputTime)
//  //      {
//		//	switch (runningTime) {
//		//	case 1:
//		//		for (int i = 0; i < 5; i++) {
//		//			m_oMap->updateVehicles();
//		//			m_oMap->updateLights();
//		//			count++;
//		//		}
//		//		break;
//		//	case 2:
//		//		for (int i = 0; i < 10; i++) {
//		//			m_oMap->updateVehicles();
//		//			m_oMap->updateLights();
//		//			count++;
//		//		}
//		//		break;
//		//	case 5:
//		//		for (int i = 0; i < 25; i++) {
//		//			m_oMap->updateVehicles();
//		//			m_oMap->updateLights();
//		//			count++;
//		//		}
//		//		break;
//		//	} // end switch
//
//  //           //Call functions to perform actions at 5 second intervals
//		//	cout << fixed;
//		//	cout << setprecision(0);
//		//	cout << "Real time elapsed: " << elapsedTime << " seconds." << endl;
//		//	cout << "Sim time elapsed: " << count << " seconds." << endl;
//		//	cout << setprecision(2);
//		//	cout << endl;
//		//	m_oMap->reportLights();
//		//	cout << endl;
//		//	m_oMap->reportVehicles();
//		//	cout << endl;
//		//	outputTime += 5.0; // Set time for next 5 second interval
//
//		//} // end if
//	} // end 'eternal' loop
//} // end run

// Get an instance
Simulation *Simulation::getInstance()
{
	static Simulation *theInstance = NULL;
	if (theInstance == NULL)
		theInstance = new Simulation();
	return theInstance;
}