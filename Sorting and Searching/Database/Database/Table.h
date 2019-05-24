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
#include <vector>

using namespace std;

const int FIELDS = 4;
const int MAX_SPREAD = 21;  // the max amount of values to return from search

const int ID_POS = 0;
const int FIRST_NAME_POS = 1;
const int LAST_NAME_POS = 2;
const int NUMBER_POS = 3;

class Table {
    string **data;
    int size = 0;

    string **found;
    int amount_found;

public:
    /*
        Constructor for a blank Table to be filled with the read function
    */
	Table();

    /*
        Constructor for creating a filled Table
        @param table = the matrix of data to use
    */
    Table( string **table );

    /*
        Constructor for creating a Table and filling it automatically with a file
        @param file = the file to read
    */
    Table( const string &file );

    /*
        Frees space used by 'data' and 'found'
    */
    ~Table();

    /*
        Reads a file for input
        @param file = the file to read
    */
    void read( const string &file );

    /*
        Writes to a stream or file
        @param out = where to write to
    */
    ostream& write( ostream &out );

    /*
        Sorts the contained data based on a switch
        @param field = the switch to sort by ('f' for first, 'l' for last
            'n' for number)
    */
    void sort( char field );

    /*
        Populates a vector with all related searches to the given string
        @param find = the string to find
        @return       void because the 'found' vector is self contained
    */
    void search( const string &find );
private:

    /*
        Prepares the object for use - abstracted into a function to reduce copied code
    */
    void prep_found();

    /*
        Resets 'found' for reuse
    */
    void reset_found();

    /*
        Splits a string based on a character to delimit with
        @param line  = the line to split
        @param delim = where to split the line
        @return        an array of the found data
    */
    string* split( const string &line, char delim );

    /*
        Swaps the position of two arrays in the internal vector
    */
    void swap( string* first, string* second );

    /*
        Does a binary search for a string in the contained 'data' vector
        @param find = the string to find
        @param low  = the lower limit of where to search
        @param high = the higher limit of where to search
        @param pos  = the position to check in each array
    */
    void bsearch( const string &find, int low, int high, int pos );

    /*
        If every character of the string to find has been checked, and 
        they have not been found to be different strings, the two strings will be considered
        a partial match
        @param person = the person to check against
        @param find   = the string to search for
        @return         true only if the two strings have the same starting characters
    */
    bool partial_match_found( const string &person, const string &find );

    /*
        Scans nearby positions to determine if any of them are related
        @param find = the string to find
        @param low  = the lower limit of where to search
        @param high = the upper limit of where to search
        @param pos  = the field to check
    */
    void scan_near( const string &find, int low, int high, int pos );
};
