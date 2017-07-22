#ifndef STAFF_H
#define STAFF_H

#include "Patient.h"
#include "WaitingQueue.h"

class Staff {
private:
	WaitingQueue * waiting_queue;		//pointer to the waiting priority_queue
	int treatment_time;					//how long it takes to treat a Patient by a Staff
	int total_time;						//how long all the patients have been at the hospital
	Patient * patient;					//staff works with a patient


public:
	//get waiting_queue
	WaitingQueue * get_waiting_queue() {
		return waiting_queue;
	}
	int get_total_time() {
		return total_time;
	}
	//pure virtual functions that Nurse and Doctor will implement
	virtual int rand_treatment_time() = 0;
	virtual void update(int clock) = 0; 
};



#endif
