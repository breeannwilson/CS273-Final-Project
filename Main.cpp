#include <iostream>

#include "Simulator.h"


//create an object of Simulator class
Simulator hospital;



int main() {

	hospital.enter_data();
	hospital.run_hospital();
	hospital.give_data();

	system("pause");
	return 0;
}