#ifndef WAITINGQUEUE_H
#define WAITINGQUEUE_H

#include "Simulator.h"
#include "Patient.h"
#include "RandomNum.h"

#include <string>
#include <iostream>
#include <queue>

Random my_random;

class WaitingQueue {
private:
	double arrival_rate;			//rate at which Patients enter the waiting queue
	int arrival_time;				//the time the patient arrives at the hospital
	int start_treatment_time;		//the time the patient enters treatment room
	int priority_num;				//number from 1-20 that determines position in priority queue
	int num_visits;					//how many times patient has been to hospital
	std::string name;				//the name of the patient
	
	std::priority_queue<Patient *> waiting_queue;		//the priority queue of Patient objects waiting to be treated

public:
	//set the arrival rate for the waiting room priority queue
	void set_arrival_rate(double arrival_rate) {
		this->arrival_rate = arrival_rate;
	}

	double get_arrival_rate() {
		return arrival_rate;
	}

	std::priority_queue<Patient *> get_waiting_queue() {
		return waiting_queue;
	}

};

#endif
