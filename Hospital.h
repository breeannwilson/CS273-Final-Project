#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "Patient.h"
#include "Simulator.h"
#include "Doctor.h"
#include "Nurse.h"
#include "WaitingQueue.h"

#include <string>
#include <vector> 
#include <map>
#include <fstream>
#include <iostream>

Random random_num;


class Hospital {
private:
	std::vector<std::string> patient_names;		//hospital has a vector of all the resident names
	std::vector<Nurse *> nurses;				//hospital has a vector of all the nurses
	std::vector<Doctor *> doctors;				//hospital has a vector of all the doctors
	std::vector<Staff *> staff;					//hospital has a vector of all the staff members
	int num_served;								//total patients served
	std::string name;							//the name of a patient
	std::map<std::string, Patient *> directory;	//a directory for the patients that visited the hospital
	WaitingQueue * waiting_queue = new WaitingQueue();				//pointer to the waiting queue


	//function to fill patient_names vector with all the residents from file
	void fill_vector() {
		//open the file
		std::ifstream file("C:\\Users\\breea\\Desktop\\residents_of_273ville.txt");		//the file with all the resident names in it

		//if the file can be opened
		if (file.is_open())
		{
			//while not at the end of the file
			while (!file.eof())
			{
				//read the names in the file
				getline(file, name);
				//push the names of residents into a vector
				patient_names.push_back(name);
			}
			//close the file
			file.close();
		}
		//if the file cannot be opened 
		else
			 std::cout << "Whoops-something went wrong with opening the file." << std::endl;
	}

	//create map for directory, key = name of patient, value = patient object (which will have priority_num and num_visits)
	void make_directory() {
		for (int i = 0; i < patient_names.size(); i++) {
			//create new Patient
			Patient * patient = new Patient();
			//set patient name to the name from vector of patient names
			patient->set_name(patient_names[i]);
			//insert this patient into the directory
			directory.insert(make_pair(patient->get_name(), patient));
		}
	}


public:

	Hospital() : num_served(0) {
		//make sure the hospital has the vector of patient names, and a map "directory"
		fill_vector();
		make_directory();
	}

	//get function for the vector of patient names
	std::vector<std::string> get_patient_names() {
		return patient_names;
	}
	//get map+		this	0x00000000 <NULL>	Hospital *

	std::map<std::string, Patient *> get_directory() {
		return directory;
	}
	//get function for vector of nurses
	std::vector<Nurse *> get_nurse_vector() {
		return nurses;
	}
	//get function for vector of doctors
	std::vector<Doctor *> get_doctor_vector() {
		return doctors;
	}
	std::vector<Staff *> get_staff_vector() {
		for (int i = 0; i < get_nurse_vector().size(); i++) {
			staff.push_back(get_nurse_vector()[i]);
		}
		for (int i = 0; i < get_doctor_vector().size(); i++) {
			staff.push_back(get_doctor_vector()[i]);
		}
		return staff;
	}
	//get total number of patients served
	int get_num_served() {
		return num_served;
	}
	void set_num_served(int num_served) {
		this->num_served = num_served;
	}

	WaitingQueue* get_waiting_queue() {
		return waiting_queue;
	}
	//this function picks a patient from the vector of names and pushes it onto the waiting queue priority queue
	void update(int clock) {
		if (my_random.next_double() < waiting_queue->get_arrival_rate()) {
			
			//find a random patient in the vector of patient names
			int random_index = rand() % patient_names.size();
			//key = the randomly picked name
			std::string key = patient_names[random_index];

			//match this name to its map in directory
			Patient* patient = directory.at(key);

			//set the arrival_time for Patient object
			patient->arrival_time = clock;
			//pick the priority_num
			patient->set_priority_num(random_num.next_int(20));
			//update the patient's num_vists
			int prev_num_visits = patient->get_num_visits();
			patient->set_num_visits(prev_num_visits+1);

			//update num_served
			num_served++;
			set_num_served(num_served);

			//push this patient onto the waiting_queue
			waiting_queue->get_waiting_queue().push(patient);


		}
		

	}


};

#endif
