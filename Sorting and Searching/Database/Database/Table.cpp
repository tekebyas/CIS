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
    prep_found();
}

Table::Table( string **table ) {
	data = table;
    prep_found();
}

Table::Table( const string &file ) {
    read( file );
    prep_found();
}

Table::~Table() {
    for ( int i = 0; i < size; i++ ) {
        delete[] data[i];
    }
    delete[] data;

    for ( int i = 0; i < MAX_SPREAD; i++ ) {
        delete[] found[i];
    }
    delete[] found;
}

void Table::prep_found() {
    amount_found = 0;
    found = new string*[MAX_SPREAD];
    
    for ( int i = 0; i < MAX_SPREAD; i++ ) {
        found[i] = new string[FIELDS];
    }
}

void Table::reset_found() {
    for ( int i = 0; i < MAX_SPREAD; i++ ) {
        delete[] found[i];
    }
    delete[] found;
    prep_found();
}

void Table::read(const string &file) {
	ifstream input( file );

    assert( input.is_open() );

	string buffer;
    string *person;

    while ( !input.eof() ) {
        getline( input, buffer );
        person = split( buffer, ',' );
        //data.push_back( person );
        // TODO implement how the 'data' array will be sized and store its info
    }
}

ostream& Table::write( ostream &out ) {
    for ( int i = 0; found[i][ID_POS] != ""; i++ ) {
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

    for ( int i = 1; i < size; i++ )
        if ( data[i][pos] < data[i - 1][pos] )
            swap( data[i], data[i - 1] );
}

void Table::search(const string &find) {
    if ( found[0][0] != "" )
        reset_found();

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

    if ( !temp.empty() ) {
        person[count] = temp;
    }

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

    if ( partial_match_found( data[mid][pos], find ) ) {
        found[amount_found] = data[mid];
        amount_found++;
        scan_near( find, low, high, pos );
	}
	else if (data[mid][pos] > find) {
		bsearch(find, low, mid - 1, pos);
	}
	else if (data[mid][pos] < find) {
		bsearch(find, mid + 1, high, pos);
	}
}

bool Table::partial_match_found( const string &person, const string &find ) {
    for ( int i = 0; i < find.size(); i++ ) {
        if ( find[i] != person[i] ) {
            return false;
        }
    }
    return true;
}

void Table::scan_near( const string &find, int low, int high, int pos ) {
    if ( ( high - low ) > 20 ) {
        int mid = ( high + low ) / 2;
        for ( int i = mid - 10; i < mid + 10; i++ ) {
            if ( partial_match_found( data[i][pos], find ) ) {
                found[amount_found] = data[i];
                amount_found++;
            }
        }
    }
    else {
        for ( int i = low; i < high; i++ ) {
            if ( partial_match_found( data[i][pos], find ) ) {
                found[amount_found] = data[i];
                amount_found++;
            }
        }
    }
}
