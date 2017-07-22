#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "Doctor.h"
#include "Nurse.h"
#include "Patient.h"
#include "Hospital.h"
#include "Staff.h"
#include "WaitingQueue.h"

#include <iostream>
#include <stdexcept>
#include <limits>
#include <ios>
#include <string>
#include <map>


class Simulator {
private:
	int clock;
	//Simulator has doctor objects and nurse objects
	Hospital * hospital = new Hospital();
	Doctor * doctor;
	Nurse * nurse;
	Patient * patient;
	Staff * staff;


	//catch any exceptions inputted by the user when asking for data in the simulation
	int read_int(const std::string &prompt, int low, int high)
	{
		if (low >= high) // invalid range
			throw std::invalid_argument("invalid range specified");

		std::cin.exceptions(std::ios_base::failbit);
		int num = 0;
		while (true) {
			try {
				while (true) {
					std::cout << prompt;
					std::cin >> num;
					if (num >= low && num <= high) { // within the specified range
						std::cout << std::endl;
						return num;
					}
				}
			}
			catch (std::ios_base::failure) {
				std::cout << "Bad numeric string -- try again\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			}
		}
	}



public:
	//first step -  ask the user for the data
	void enter_data() {
		std::cout << "Welcome to 273ville (lame name Pete) with population 2000." << std::endl;
		std::cout << "You are chosen to run the local hospital!" << std::endl;

		//ask the user how many patients will come in to the hospital per hour
		int rate = read_int("What will be the average hourly patient arrival rate at this hospital?: ", 1, 59);
		double arrival_rate = rate / 60.0;
		//set the patient arrival rate for the priority waiting_queue
		hospital->get_waiting_queue()->set_arrival_rate(arrival_rate);

		//ask the user how many doctors will be on staff
		int num_doctors = read_int("How many doctors will be on staff?: ", 1, 200);

		//create new Doctor objects to match num_doctors
		//then push these doctors into a vector of doctors
		for (int i = 0; i < num_doctors; i++) {
			doctor = new Doctor();
			hospital->get_doctor_vector().push_back(doctor);
		}

		//ask the user how many nurses will be on staff
		int num_nurses = read_int("How many nurses will be on staff? : ", 0, 300);

		//create new Nurse objects to match num_nurses
		//then push these nurses into a vector of nurses
		for (int i = 0; i < num_nurses; i++) {
			nurse = new Nurse();
			hospital->get_nurse_vector().push_back(nurse);
		}
	}

	//run the simulation
	void run_hospital() {
		int total_time = 10080;
		for (int clock = 0; clock < total_time; clock++) {
			hospital->update(clock);
			for (int i = 0; i < hospital->get_staff_vector().size(); i++) {
				hospital->get_staff_vector()[i]->update(clock);
			}
		}
	}

	//show data from running the simulation
	
	void give_data() {
		std::cout << "The simulation is done!" << std::endl;
		std::cout << "Total served " << hospital->get_num_served() << std::endl;

		/*
		std::cout << "Total time spent at the hospital " << staff->get_total_time() << std::endl;
		*/

		std::cout << "The average patient visit time is: " << std::endl;
		std::cout << "Would you like to: " << std::endl;

		int answer = read_int("(1) See a list of all the residents treated, or (2) Search for a resident by name?: ", 1, 2);

		if (answer == 1) {
			std::map<std::string, Patient *> m = hospital->get_directory();
			for (std::map<std::string, Patient *>::iterator i = m.begin(); i != m.end(); i++) {
				//if the value num_visits is more than 0, then they visited the hospital
				//output the name
				if (i->second->get_num_visits() > 0)
					std::cout << i->first << std::endl;
			}
		}


		else {
			std::string search_name;
			std::cout << "Whose record would you like to find?" << std::endl;
			std::cin >> search_name;

			//lets see their info!
			std::map<std::string, Patient *> d = hospital->get_directory();
			//iterate through the directory map
			for (std::map<std::string, Patient *>::iterator i = d.begin(); i != d.end(); i++) {
				//if the key at the iterator i matches the search_name, output their value info
				if (i->first == search_name) {
					std::cout << "This person visited the hospital: " << i->second->get_num_visits() << " times." << std::endl;
					std::cout << "Their priority number was: " << i->second->get_priority_num() << std::endl;
				}
			
			}
			/* the test should look something like this
			//this name is not in this city
			if (i->first != search_name) {
					std::cout << "Whoops! This person was not in 273ville." << std::endl;
				}
				*/


		}



	}

};

#endif 
