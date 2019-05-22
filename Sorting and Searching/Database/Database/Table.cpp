/*
	File: Database.cpp
	Author: Teke Byas
	Email: tekeb6687@student.vvc.edu
	Description: This object will store, sort, search, and print the data it holds
		formatted to look like a table
*/

#include <fstream>
#include <cassert>

#include "Table.h"

using namespace std;

Table::Table() {
	// with the read function implemented,
	// blank Table objects can be created and used
	// unlike with the other project done for class
}

Table::Table(vector<string*> new_data) {
	data = new_data;
}

Table::~Table() {
//  for ( int i = data.size() - 1; i > 0; i-- ) {
//      delete data[i];
//      data.pop_back();
//  }
//  for ( int i = found.size() - 1; i > 0; i-- ) {
//      delete found[i];
//      found.pop_back();
//  }
}

void Table::read(const string &file) {
	ifstream input( file );

    assert( input.is_open() );

	string buffer;
    string *person;

    while ( !input.eof() ) {
        getline( input, buffer );
        person = split( buffer, ',' );
        data.push_back( person );
    }
}

ostream& Table::write( ostream &out ) {
    for ( int i = 0; i < found.size(); i++ ) {
		out << "Name: " << found[i][LAST_NAME_POS] << ", " << found[i][FIRST_NAME_POS]
			<< "\nPhone Number: " << found[i][NUMBER_POS] << "\n\n";
	}
	return out;
}

void Table::sort(char field) {
	int pos;

    if ( field == 'n' )
		pos = NUMBER_POS;
    else if ( field == 'f' )
		pos = FIRST_NAME_POS;
	else
		pos = LAST_NAME_POS;

    for ( int i = 1; i < data.size(); i++ )
        if ( data[i][pos] < data[i - 1][pos] )
            swap( data[i], data[i - 1] );
}

void Table::search(const string &find) {
	int c = find[0];

	if (c > 47 && c < 58) {
		sort('n');
		bsearch(find, 0, data.size() - 1, NUMBER_POS);
	}
	else {
		sort('f');
		bsearch(find, 0, data.size() - 1, FIRST_NAME_POS);
		sort('l');
		bsearch(find, 0, data.size() - 1, LAST_NAME_POS);
	}
}

string* Table::split(const string &line, char delim) {
    string *person = new string[FIELDS];

	int count = 0;
	string temp = "";

	for (int i = 0; i < line.size(); i++) {
		if (line[i] == delim) {
			person[count] = temp;
            count++;
			temp = "";
		}
		else
			temp += line[i];
	}

//  if ( !temp.empty() ) {
//      person[count] = temp;
//  }

	return person;
}

void Table::swap(string *first, string *second) {
	string *temp = first;
	first = second;
	second = temp;
}

void Table::bsearch( const string &find, int low, int high, int pos ) {
    int mid = ( high + low ) / 2;

    if ( mid > high || mid < low ) {
        return;
    }

    if ( match_found( data[mid][pos], find ) ) {
        found.push_back( data[mid] );
		// TODO scan nearby items for other matching searches ** new function **
	}
	else if (data[mid][pos] > find) {
		bsearch(find, low, mid - 1, pos);
	}
	else if (data[mid][pos] < find) {
		bsearch(find, mid + 1, high, pos);
	}
}

bool Table::match_found( const string &person, const string &find ) {
    for ( int i = 0; i < find.size(); i++ ) {
        if ( find[i] != person[i] ) {
            return false;
        }
    }
    return true;
}
