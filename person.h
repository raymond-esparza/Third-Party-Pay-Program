/*
Program: Third Party Pay Program
File: person.h
Author: Raymond Esparza

This file is inended to be included in an accompanying person.cpp. This
file contains a class declaration for Person in the inhereting files.
*/

#ifndef PERSON_H
#define PERSON_H

#include <string>

using namespace std;

class Person {
	public:
		Person(){};
		void setFirstName(string fName);
		void setLastName(string lName);
		void setEmployeeId(int id);
		void setCompanyName(string coName);
		void setHoursWorked(float hours);
		void setPayRate(float rate);

		string getFirstName();
		string getLastName();
		int getEmployeeId();
		string getCompanyName();
		float getHoursWorked();
		float getPayRate();

		float totalPay();
		string fullName();

	private:
		string firstName;
		string lastName;
		int employeeID;
		string companyName;
		float hoursWorked;
		float payRate;
};
#endif