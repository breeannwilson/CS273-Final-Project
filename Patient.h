#ifndef PATIENT_H
#define PATIENT_H

#include <queue>
#include <string>
#include <iostream>

class Patient {
	int clock;
	std::string name;				//the name of the Patient
	int priority_num;				//the priority number of the patient
	int num_visits;					//number of times the patient has been to the hospital
	int treatment_time;				//the time it takes with Doctor/Nurse to get treated
	int start_treatment_time;		//clock time when patient meets with Doctor/Nurse
	int total_time;					//total time spent at the hospital = departure_time - arrival_time

public:
	int arrival_time;
	int departure_time;
	Patient() {
		priority_num = 0;
		num_visits = 0;
		treatment_time = 0;
		total_time = 0;
	}

	//default 
	Patient(int clock) : arrival_time(clock), start_treatment_time(-1), departure_time(-1) {
		priority_num;
		num_visits;
		treatment_time;
		arrival_time;
		start_treatment_time;
		departure_time;
	}

	//set the name of the patient
	void set_name(std::string name) {
		this->name = name;
	}
	//get the name of the patient
	std::string get_name() {
		return name;
	}

	//set the priority number for the patient
	void set_priority_num(int priority_num) {
		this->priority_num = priority_num;
	}
	//get the priority number for the patient
	int get_priority_num() {
		return priority_num;
	}
	//set the number of visits for the patient
	void set_num_visits(int num_visits) {
		this->num_visits = num_visits;
	}
	//get the number of visits for the patient
	int get_num_visits() {
		return num_visits;
	}
	//set how long patient spends with doctor/nurse
	void set_treatment_time(int treatment_time) {
		this->treatment_time = treatment_time;
	}
	//get how long patient spend with doctor/nurse
	int get_treatment_time() {
		return treatment_time;
	}
	//set the time when patient enters Doctor/Nurse treatment room
	void set_start_treatment_time(int start_treatment_time) {
		this->start_treatment_time = start_treatment_time;
	}
	//get the time when patient enters Doctor/Nurse treatment room
	int get_start_treatment_time() {
		return start_treatment_time;
	}
	
	//how long the patient's visit was at the hospital
	void set_visit_amount(int total_time) {
		this->total_time = total_time;
	}
	int get_visit_time() {
		total_time = departure_time - arrival_time;
		return total_time;
	}

	//overload the < operator to be able to compare Patient objects by their priority_num
	bool operator<(Patient& other) const {
		if (this->priority_num < other.get_priority_num())
			return true;
		else
			return false;
	}

};

std::ostream& operator<<(std::ostream& os, Patient pt) {
	os << "priority number: " << pt.get_priority_num() << ", number of visits: " << pt.get_num_visits();
	return os;
}

#endif 
