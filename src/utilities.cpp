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
	ifstream inputFile;
	inputFile.open(*filename);
	if (!inputFile) {
		return COULD_NOT_OPEN_FILE;
	}
	while (!inputFile.eof()) {
		process_stats rowStats;
		istringstream row;
		getline(inputFile, row); // get row
		if (!getline(row, rowStats.process_number, ",")){
			continue;
		}
		if (!getline(row, rowStats.start_time, ",")){
			continue;
		}
		if (!getline(row, rowStats.cpu_time, ",")){
			continue;
		}
		if (!getline(row, rowStats.io_time)){
			continue;
		}
		myData.push_back(rowStats);
		if (!ignoreFirstRow){
			ignoreFirstRow = true;
		}
	}
	return SUCCESS;
}


//will sort according to user preference
void sortData(SORT_ORDER mySortOrder) {

}

process_stats getNext() {
	process_stats myFirst;

	return myFirst;
}

//returns number of process_stats structs in the vector holding them
int getNumbRows(){
	return 0;
}


