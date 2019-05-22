/*
	File: Database.cpp
	Author: Teke Byas
	Email: tekeb6687@student.vvc.edu
	Description: This object will store, sort, search, and print the data it holds
		formatted to look like a table
*/

#include <fstream>

#include "Database.h"

Table::Table() {
	// with the read function implemented,
	// blank Database objects can be created and used
	// unlike with the other project done for class
	for (int i = 0; data[i]; i++) {
		data[i] = nullptr;
	}
}

Table::Table(std::string **new_data) {
	data = new_data;
}

Table::~Table() {
	delete[] data;
	delete[] found;
}

void Table::read(const std::string &file) {
	std::ifstream input( file );

	std::string buffer;
	std::string* person;

	while (input >> buffer) {
		person = split(buffer, ',');
		// TODO figure out what to do with 'person' at this point

		//   this is where the dynamically sized array would come in handy
		//   just using an array of size 1001 would work for now because we know
		//   how many lines there are, but then this wouldn't work for other files
	}
}

std::ostream& Table::operator<<(std::ostream &out) {
	for (int i = 0; found[i]; i++) {
		out << "Name: " << found[i][LAST_NAME_POS] << ", " << found[i][FIRST_NAME_POS]
			<< "\nPhone Number: " << found[i][NUMBER_POS] << "\n\n";
	}
	return out;
}

void Table::sort(char field) {
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

#if 0
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
#endif

void Table::search(const std::string &find) {
	int c = find[0];

	if (c > 47 && c < 58) {
		sort('n');
		bsearch(find, 0, size, NUMBER_POS);
	}
	else {
		sort('f');
		bsearch(find, 0, size, FIRST_NAME_POS);
		sort('l');
		bsearch(find, 0, size, LAST_NAME_POS);
	}
}

std::string* Table::split(const std::string &line, char delim) {
	std::string* person = new std::string[FIELDS];

	int count = 0;
	std::string temp = "";

	for (int i = 0; i < line.size(); i++) {
		if (line[i] == delim) {
			person[count] = temp;
			temp = "";
		}
		else
			temp += line[i];
	}

	return person;
}

void Table::swap(std::string *first, std::string *second) {
	std::string *temp = first;
	first = second;
	second = temp;
}

void Table::bsearch(const std::string &find, int low, int high, int pos) {
	int mid = (high + low) / 2;
	
	if (data[mid][pos] == find) { // TODO overload == operator to check for partial matches
		// found[ size? ] = data[mid];
		// scan nearby items for other matching searches ** new function **
	}
	else if (data[mid][pos] > find) {
		bsearch(find, mid + 1, high, pos);
	}
	else if (data[mid][pos] < find) {
		bsearch(find, low, mid - 1, pos);
	}
}
