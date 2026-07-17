#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;
const int NUM_DISEASES = 41;   // real dataset: 41 diseases
const int NUM_SYMPTOMS = 131;  // real dataset: 131 unique symptoms
const int MAX_ROWS = 5000; // max CSV rows to load

class IDManager {//used to  get retrive last id
public:
	static int getNextID() {
		ifstream in("last_id.txt");
		int lastID = 100;

		if (in) {
			in >> lastID;
			in.close();
		}

		lastID++;

		ofstream out("last_id.txt");
		out << lastID;
		out.close();

		return lastID;
	}
};