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

int main(int argc, char *argv[]) {
	Database data;
	//data.read( argv[1] );

	data.write(std::cout);

	return 0;
}