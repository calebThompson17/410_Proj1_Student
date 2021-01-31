/***
 * KP Utils
 */
#include <numeric>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "utilities.h"
#include "stdlib.h"

using namespace std;

vector<process_stats> myData;

//********************** private to this compilation unit **********************

//if myString does not contain a string rep of number returns o
//if int not large enough has undefined behaviour, very fragile
int stringToInt(const char *myString) {
	return atoi(myString);
}

int loadData(const char* filename, bool ignoreFirstRow) {
	ifstream inputFile (filename);
	if (!inputFile.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}
	while (!inputFile.eof()) {
		process_stats rowStats;
		string rowString;
		getline(inputFile, rowString); // get row
		stringstream rowStream;
		rowStream.str(rowString);
		string str;
		if (!getline(rowStream, str, ',')){
			continue;
		}
		rowStats.process_number = stringToInt(str.c_str());
		if (!getline(rowStream, str, ',') || rowStats.process_number == 0){
			continue;
		}
		rowStats.start_time = stringToInt(str.c_str());
		if (!getline(rowStream, str, ',') || rowStats.start_time == 0){
			continue;
		}
		rowStats.cpu_time = stringToInt(str.c_str());
		if (!getline(rowStream, str) || rowStats.cpu_time == 0){
			continue;
		}
		rowStats.io_time = stringToInt(str.c_str());
		if (ignoreFirstRow || rowStats.io_time == 0){
			ignoreFirstRow = false;
			continue;
		}
		else {
			myData.push_back(rowStats);
		}
	}
	return SUCCESS;
}


//will sort according to user preference
void sortData(SORT_ORDER mySortOrder) {

}

process_stats getNext() {
	process_stats myFirst;
	myData.front() = myFirst;
	myData.erase(myData.begin());
	return myFirst;
}

//returns number of process_stats structs in the vector holding them
int getNumbRows(){
	return myData.size();
}


