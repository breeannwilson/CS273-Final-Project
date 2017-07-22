#ifndef DOCTOR_H
#define DOCTOR_H

#include "Patient.h"
#include "Staff.h"

class Doctor : public Staff {
	int max_service_time = 20;
	int min_service_time = 1;
	int total_time;

	//Doctor HAS-A vector of Patients - the vector is of size 1
	std::vector<Patient *> patients;

	//implement pure virtual function from Staff class
	//this determines a patient's treatment_time
	int rand_treatment_time() {
		int treatment_time = my_random.next_int(max_service_time - min_service_time) + min_service_time;
		patients[0]->set_treatment_time(treatment_time);
		return treatment_time;
	}

	void update(int clock) {
		//if a doctor doesn't have a patient, take the patient from the waiting queue
		if (patients.empty()) {
			//take the patient at the top of the waiting_queue
			Patient * patient = get_waiting_queue()->get_waiting_queue().top();
			//put this Patient into the Doctor vector
			patients[0] = patient;
			//take this patient off of the waiting queue
			get_waiting_queue()->get_waiting_queue().pop();
		}
		if (!patients.empty()) {
			//if the service time is up
			if (clock >= (patients[0]->get_start_treatment_time() + patients[0]->get_treatment_time())) {
				Patient * patient = patients[0];
				//set the departure time for the patient
				patient->departure_time = clock;
				//set the visit time for how long patient was at the hospital
				int visit_time = patient->departure_time - patient->arrival_time;
				patient->set_visit_amount(visit_time);
				
				total_time += visit_time;
				
				//erase the only element in the vector
				patients.erase(patients.begin());

			}
		}
	}

};


#endif
