/*
	File: Database.h
	Author: Teke Byas
	Email: tekeb6687@student.vvc.edu
	Description: contains a variable amount of people and their data, stored
		in a tabular model to reduce the number of objects needed, and
		shrink the total memory usage of the program while running

		Any speed gains would be negligible with a progrram this size,
		but it makes for good practice to know how to do this in the future

		In all, this object will store, sort, search, and print the data it holds
		formatted to look like a table
*/

#pragma once

#include <iostream>
#include <string>

const int FIELDS = 3;

const int FIRST_NAME_POS = 0;
const int LAST_NAME_POS = 1;
const int NUMBER_POS = 2;

class Database {
	std::string** data = new std::string*[FIELDS];

public:
	Database();
	Database(std::string**);

	//void read(const char *);
	void read(const std::string &);
	std::ostream& write(std::ostream &);

	void sort(char);
	std::string* search(const std::string &);
private:

	std::string* split(const std::string &, char);
	void swap(std::string*, std::string*);
};