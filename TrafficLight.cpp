
	/*******************************************************************
	*   CS 307 Programming Assignment 3 - Traffic Simulation
	*   File: TrafficLight.cpp
	*   Author: Joanna Pease
	*	Prog Desc: This program simulates traffic on a grid of roads.
	*		Vehicles travel on the roads while obeying the road's speed
	*		limit and the status of the traffic light at the upcoming
	*		intersection.
	*   File Desc: This file is responsible for creating a traffic light.
	*		It provides functions to get, set, or change the color of the
	*		traffic light.
	*   Date: 4/9/17
	*
	*   I attest that this program is entirely my own work, unless
	*	noted otherwise.
	*******************************************************************/

#include "stdafx.h"
#include "TrafficLight.h"

TrafficLight::TrafficLight() {
    m_eColorNS = GREEN;
    m_eColorEW = RED;
    m_iTimerNS = 1;
	m_iTimerEW = 1;
} // end TrafficLight

TrafficLight::~TrafficLight() {
} // end ~TrafficLight


eColor TrafficLight::getColorNS() {
    return m_eColorNS;
}

// Change the color of the NS light
void TrafficLight::changeColorNS() {
    switch (m_eColorNS) {
        case RED:
            if (m_iTimerNS == 50) {
                m_eColorNS = GREEN;
                m_iTimerNS = 1;
            } // end if
            else
                m_iTimerNS++;
            break;
        case GREEN:
            if (m_iTimerNS == 30) {
                m_eColorNS = AMBER;
                m_iTimerNS = 1;
            } // end if
            else
                m_iTimerNS++;
            break;
        case AMBER:
            if (m_iTimerNS == 20) {
                m_eColorNS = RED;
                m_iTimerNS = 1;
            } // end if
            else
                m_iTimerNS++;
            break;
    } // end switch
} //end changeColorNS

eColor TrafficLight::getColorEW() {
    return m_eColorEW;
}

// Change the color of the EW light
void TrafficLight::changeColorEW() {
    switch (m_eColorEW) {
        case RED:
            if (m_iTimerEW == 50) {
                m_eColorEW = GREEN;
                m_iTimerEW = 1;
            } // end if 
			else
                m_iTimerEW++;
            break;
        case GREEN:
            if (m_iTimerEW == 30) {
                m_eColorEW = AMBER;
                m_iTimerEW = 1;
            } // end if
			else
                m_iTimerEW++;
            break;
        case AMBER:
            if (m_iTimerEW == 20) {
                m_eColorEW = RED;
                m_iTimerEW = 1;
            } // end if
			else
                m_iTimerEW++;
            break;
    } // end switch
} // end changeColorEW

TrafficLight *TrafficLight::getInstance()
{
	static TrafficLight *theInstance = NULL;
	if (theInstance == NULL)
		theInstance = new TrafficLight();
	return theInstance;
}