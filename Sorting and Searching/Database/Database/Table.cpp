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
        found[i] = nullptr;
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
        found[i] = nullptr;
        delete[] found[i];
    }
    delete[] found;
    prep_found();
}

void Table::read(const string &file) {
	ifstream input( file );

    assert( input.is_open() );

	string buffer;

    int line_count = 0;

    // reads the length of the file to determine how much space will be needed
    while ( !input.eof() ) {
        getline( input, buffer );
        line_count++;
    }

    // resets the state of 'input' to be read again
    // after the line count of the file is determined
    input.close();
    input.open(file);
    assert( input.is_open() );

    // updates the usable size of 'data'
    size = line_count;
    data = new string*[size];

    // creates an empty slot for each needed line, then fills it
    for ( int i = 0; i < size; i++ ) {
        data[i] = new string[FIELDS];

        getline( input, buffer );
        data[i] = split( buffer, ',' );
    }

}

ostream& Table::write( ostream &out ) {
    for ( int i = 0; found[i][ID_POS] != ""; i++ ) {
		out << "Name: " << found[i][LAST_NAME_POS] << ", " << found[i][FIRST_NAME_POS]
			<< "\nPhone Number: " << found[i][NUMBER_POS] << "\n\n";
	}
    return out;
}

void Table::sort( char field ) {
    int pos;

    if ( field == 'n' )
        pos = NUMBER_POS;
    else if ( field == 'f' )
        pos = FIRST_NAME_POS;
    else
        pos = LAST_NAME_POS;

    string **work = new string*[size];
    for ( int i = 0; i < size; i++ )
        work[i] = new string[FIELDS];

    copy_array( data, 0, size - 1, work );

    merge_sort( work, 0, size - 1, pos, data );

    for ( int i = 0; i < size; i++ ) {
        work[i] = nullptr;
        delete[] work[i];
    }
    delete[] work;
}

void Table::merge_sort( string **data, int low, int high, int pos, string **work ) {
    if ( high - low < 2 )
        return;
    else {
        int mid = ( high + low ) / 2;
        merge_sort( work, low, mid, pos, data );
        merge_sort( work, mid, high, pos, data );
        merge( data, low, high, pos, work );
    }
}

void Table::merge( string **work, int low, int high, int pos, string **data ) {
    int mid = ( high + low ) / 2;
    int i = low;
    int j = mid;

    for ( int k = low; k < high; k++ ) {
        if ( i < mid && ( work[i][pos] < work[j][pos] || j >= high ) ) {
            data[k] = work[i];
            i++;
        }
        else {
            data[k] = work[j];
            j++;
        }
    }
}

void Table::copy_array( string **from, int low, int high, string ** to ) {
    for ( int i = low; i < high; i++ )
        to[i] = from[i];
}

void Table::search(const string &find) {
    if ( found[0][0] != "" )
        reset_found();

	int c = find[0];

	if (c > 47 && c < 58) {
		Table::sort('n');
		bsearch(find, 0, size - 1, NUMBER_POS);
	}
	else {
		Table::sort('f');
		bsearch(find, 0, size - 1, FIRST_NAME_POS);
		Table::sort('l');
		bsearch(find, 0, size - 1, LAST_NAME_POS);
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
//      found[amount_found] = data[mid];
//      amount_found++;
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