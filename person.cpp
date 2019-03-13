/*
Program: Third Party Payroll Program
File: person.cpp
Author: Raymond Esparza

This file is intended to be included in pay.cpp main file and in conjunction with person.h header file.
This file contains member functions of the Person class declared in person.h.
*/
#include "person.h"

void Person::setFirstName(string fName){
	firstName = fName;
	return;
}

void Person::setLastName(string lName){
	lastName = lName;
	return;
}

void Person::setEmployeeId(int id){
	employeeID = id;
	return;
}

void Person::setCompanyName(string coName){
	companyName = coName;
	return;
}

void Person::setHoursWorked(float hours){
	hoursWorked = hours;
	return;
}

void Person::setPayRate(float rate){
	payRate = rate;
	return;
}

string Person::getFirstName(){
	return firstName;
}

string Person::getLastName(){
	return lastName;
}

int Person::getEmployeeId(){
	return employeeID;
}

string Person::getCompanyName(){
	return companyName;
}

float Person::getHoursWorked(){
	return hoursWorked;
}

float Person::getPayRate(){
	return payRate;
}

float Person::totalPay(){
	return payRate * hoursWorked;
}

string Person::fullName(){
	return firstName + " " + lastName;
}