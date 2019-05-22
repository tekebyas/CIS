#pragma once

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

#include <iostream>
#include <string>

const int FIELDS = 3;

const int FIRST_NAME_POS = 0;
const int LAST_NAME_POS = 1;
const int NUMBER_POS = 2;

int size = 1000;

class Table {
	//std::string** data = new std::string[size][FIELDS];
	std::string** data = new std::string*[FIELDS];
	std::string** found = new std::string*[FIELDS];

public:
	Table();
	Table(std::string**);

	~Table();

	void read(const std::string &);
	std::ostream& operator<<(std::ostream &);

	void sort(char);
	//std::string* search(const std::string &);

	void search(const std::string &);
private:

	std::string* split(const std::string &, char);
	void swap(std::string*, std::string*);

	void bsearch(const std::string &, int, int, int);
};