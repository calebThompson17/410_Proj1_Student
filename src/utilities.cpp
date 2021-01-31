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
	myData.clear();
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
		if (ignoreFirstRow){
			ignoreFirstRow = false;
			continue;
		}
		if (!getline(rowStream, str, ',')){
			continue;
		}
		rowStats.process_number = stringToInt(str.c_str());
		if (!getline(rowStream, str, ',')){
			continue;
		}
		rowStats.start_time = stringToInt(str.c_str());
		if (!getline(rowStream, str, ',')){
			continue;
		}
		rowStats.cpu_time = stringToInt(str.c_str());
		if (!getline(rowStream, str)){
			continue;
		}
		rowStats.io_time = stringToInt(str.c_str());
		myData.push_back(rowStats);
	}
	return SUCCESS;
}

bool CPUTimeSort(process_stats stat1, process_stats stat2) {
	return stat1.cpu_time < stat2.cpu_time;
}

bool ProcessNumberSort(process_stats stat1, process_stats stat2) {
	return stat1.process_number < stat2.process_number;
}

bool StartTimeSort(process_stats stat1, process_stats stat2) {
	return stat1.start_time < stat2.start_time;
}

bool IOTimeSort(process_stats stat1, process_stats stat2) {
	return stat1.io_time < stat2.io_time;
}


//will sort according to user preference
void sortData(SORT_ORDER mySortOrder) {
	switch(mySortOrder){
	case CPU_TIME:
		sort(myData.begin(), myData.end(), CPUTimeSort);
		break;
	case PROCESS_NUMBER:
		sort(myData.begin(), myData.end(), ProcessNumberSort);
		break;
	case START_TIME:
		sort(myData.begin(), myData.end(), StartTimeSort);
		break;
	case IO_TIME:
		sort(myData.begin(), myData.end(), IOTimeSort);
		break;
	}
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


