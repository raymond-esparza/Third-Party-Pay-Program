/*
Program: Third Party Payroll Program
File: pay.cpp
Author: Raymond Esparza

This file is intended to work alongside accompanying files person.h and person.cpp. It also requires a
textfile called "input.txt" that has lines formatted as: 
"firstname lastname (int)employeeID companyname (float)hoursworked (float)payrate".
This main file reads data from the text file, creates a vector of employees, creates a vector of different
companies, finds the highest paid individual, and then creates individual textfiles for each company containing
that companies employees.
*/

#include "person.cpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

//function declarations
void readData(vector<Person>&);
void getCompanies(vector<Person>&, vector<string>&);
void printHighestPaid(vector<Person>&);
void separateAndSave(vector<Person>&, vector<string>&);


//main function
int main(){

	vector<Person> employees;
	vector<string> companyNames;

	readData(employees);
	getCompanies(employees, companyNames);
	printHighestPaid(employees);
	separateAndSave(employees, companyNames);

	return 0;
}





//This function reads in lines from a text file and assigns strings of each line to elements in a temporary
//object of type Person as long as there are more lines to follow in the file. It then fills a vector of
//type Person with the object created from each line.
void readData(vector<Person> &employees){
	ifstream datafile("input.txt");
	Person temp;
	string  firstN, lastN, cname = "";
	int id = 0;
	float hworked, rate = 0.0;

	if(datafile.is_open()){
		while( !datafile.eof() ){
			datafile >> firstN >> lastN >> id >> cname >> hworked >> rate;
			temp.setFirstName(firstN);
			temp.setLastName(lastN);
			temp.setEmployeeId(id);
			temp.setCompanyName(cname);
			temp.setHoursWorked(hworked);
			temp.setPayRate(rate);
			employees.push_back(temp);
		}
		datafile.close();
	}

	return;
}



//This function takes as input a reference to a vector of type Person and a reference to an empty vector of strings.
//It finds the name of the company and populates the string vector with the names. It then finds and removes
//duplicates of company names.
void getCompanies(vector<Person> &employees, vector<string> &companyNames){
	int numcompanies = employees.size();

	//this loop populates a vector of strings
	for (int i = 0; i != numcompanies; ++i){
		companyNames.push_back( employees.at(i).getCompanyName() );
	}

	// This loop finds and removes duplicate companies
	for(int i = 0; i != numcompanies; ++i){	
		for(int j = i + 1; j != numcompanies; ++j){
			if( companyNames.at(i) == companyNames.at(j) ){
				companyNames.erase( companyNames.begin() + i);
				--numcompanies;
				--i;
				break;
			}
		}
	}

	return;
}



//This function takes as input a vector of type Person. It simply finds the highest paid person in the vector and
//prints out the details of that person.
void printHighestPaid(vector<Person> &employees){
	int numemployees = employees.size();
	int highestindex = 0;
	float highestamount = 0.0;
	for(int i = 0; i != numemployees; ++i){
		if( highestamount <= employees.at(i).totalPay() ){
			highestamount = employees.at(i).totalPay();
			highestindex = i;
		}
	}
	cout << "Highest paid: " << employees.at(highestindex).fullName() << endl;
	cout << "Employee ID: " << employees.at(highestindex).getEmployeeId() << endl;
	cout << "Employer: " << employees.at(highestindex).getCompanyName() << endl;
	cout << "Total Pay: $" << setprecision(2) << fixed << employees.at(highestindex).totalPay() << endl;
			//"setprecision(2) << fixed" sets the float to display the value to the nearest two decimal places

	return;
}



//This function takes as input a vector of type Person and a vector of strings of company names. It then loops through
//each company name and keeps a running total of employee pay for that company by looping through and finding employees
//who work for that company. When matching employees are found, it creates a textfile for that company and writes to the
//file the employee information and pay. When all employees have been looked at, it writes to the file the total pay to
//all the employees of that company.
void separateAndSave(vector<Person> &employees, vector<string> &companyNames){
	int numemployees = employees.size();
	int numcompanies = companyNames.size();

	for(int i = 0; i != numcompanies; ++i){ //loop through the different companies
		float total = 0.0;
		int companynamelength = companyNames.at(i).size();
		string textfilename = companyNames.at(i) + ".txt";
		ofstream savetofile(textfilename, ios::app);	// "ios::app" is used to append to the end of a file
														//leaving it out causes the file to be overwritten everytime the ofstream is called
		if( savetofile.is_open() ){
			for(int j = 0; j != numemployees; ++j){		//loop through all employees searching for a match to current company
				if( companyNames.at(i) == employees.at(j).getCompanyName() ){
					total = total + employees.at(j).totalPay();
					savetofile << setw(10) << left << employees.at(j).getFirstName() << " "		//"set(10) << left" reserves 10 spaces and left aligns the following string
							   << setw(10) << left << employees.at(j).getLastName() << " "
							   << setw(3) << left << employees.at(j).getEmployeeId() << " " 
							   << setw(companynamelength) << employees.at(j).getCompanyName()<< " $"
							   << setprecision(2) << fixed << employees.at(j).totalPay() << endl;
				}
			}
			savetofile << "Total: $" << setprecision(2) << fixed << total;
			savetofile.close();
		}
	}
	return;
}

