/*
	File: Source.cpp (main.cpp)
	Author: Teke Byas
	Email: tekeb6687@student.vvc.edu
	Description: A tabular version of the sorting and searching project done in CIS 202
		This version will be done with one object containing a table rather than two objects
*/

#include <iostream>
#include <cassert>

#include "Database.h"

std::string prompt();

int main(int argc, char *argv[]) {
	Table data;
	//data.read( argv[1] );

	// TODO determine why this gives an error
	//std::cout << data.search( prompt() ) << std::endl;

	return 0;
}

std::string prompt() {
	std::cout << "Enter a search term: ";
	std::string find;
	std::cin >> find;
	return find;
}