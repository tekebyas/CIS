/*
	File: Database.cpp
	Author: Teke Byas
	Email: tekeb6687@student.vvc.edu
	Description: This object will store, sort, search, and print the data it holds
		formatted to look like a table
*/

#include <fstream>

#include "Database.h"

Database::Database() {
	// with the read function implemented,
	// blank Database objects can be created and used
	// unlike with the other project done for class
}

Database::Database(std::string **new_data) {
	data = new_data;
}

//void Database::read(const char *file) {
void Database::read(const std::string &file) {
	std::ifstream input( file );

	std::string buffer;
	std::string* data;

	while (input >> buffer) {
		data = split(buffer, ',');
		// TODO figure out what to do with 'data' at this point

		//   this is where the dynamically sized array would come in handy
		//   just using an array of size 1001 would work for now because we know
		//   how many lines there are, but then this wouldn't work for other files
	}
}

std::ostream& Database::write(std::ostream &out) {
	for (int i = 0; data[i]; i++) {
		out << "Name: " << data[i][LAST_NAME_POS] << ", " << data[i][FIRST_NAME_POS]
			<< "\nPhone Number: " << data[i][NUMBER_POS] << "\n\n";
	}
	return out;
}

void Database::sort(char field) {
	int pos;

	if (field == 'n')
		pos = NUMBER_POS;
	else if (field == 'f')
		pos = FIRST_NAME_POS;
	else
		pos = LAST_NAME_POS;

	for (int i = 0; data[i]; i++) {
		if ( data[i][pos] > data[i + 1][pos] ) {
			swap( data[i], data[i + 1] );
		}
	}
}

std::string* Database::search(const std::string &find) {
	int c = find[0];
	int pos;

	// if this were made into a double pointer, a table could be formed to return
	//   all people found
	//   i.e. std::string **person = new std::string* [FIELDS];

	//std::string *person;

	std::string person[] = {"Fred", "Bear", "555-5555"};

	if (c > 47 && c < 58) {
		sort('n');
		pos = NUMBER_POS;
	}
	else {
		sort('f');
		pos = FIRST_NAME_POS;
		// search for the person by first name
		pos = LAST_NAME_POS;
		// search for the person by last name
	}

	// TODO add three (3) for loops to search for the person by position
	//   one under each time pos is set
	//   use a function call to reduce copied code

	return person;
}

std::string* Database::split(const std::string &line, char delim) {
	std::string* data = new std::string[FIELDS];

	int count = 0;
	std::string temp = "";

	for (int i = 0; i < line.size(); i++) {
		if (line[i] == delim) {
			data[count] = temp;
			temp = "";
		}
		else
			temp += line[i];
	}

	return data;
}

void Database::swap(std::string *first, std::string *second) {
	std::string *temp = first;
	first = second;
	second = temp;
}
