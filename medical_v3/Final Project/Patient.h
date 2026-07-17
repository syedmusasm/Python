#pragma once
#include"IDManager.h";
class Patient
{
public:
	int id;
	string name;
	int age;
	int severity; // Used for Max-Heap prioritization
	int* symptoms; // Array of 15 binary symptoms
	string diagnosedDisease;
	double predictionConfidence; // Added to store AI probability percentage

	Patient() {
		id = 0;
		name = "Unknown";
		age = 0;
		severity = 0;

		symptoms = new int[NUM_SYMPTOMS];
		for (int i = 0; i < NUM_SYMPTOMS; i++)
			symptoms[i] = 0;

		diagnosedDisease = "Pending Prediction";
		predictionConfidence = 0.0;
	}
	Patient(string n, int a, int sev)
	{
		id = 0;
		name = n;
		age = a;
		severity = sev;

		symptoms = new int[NUM_SYMPTOMS];
		for (int i = 0; i < NUM_SYMPTOMS; i++)
			symptoms[i] = 0;

		diagnosedDisease = "Pending Prediction";
		predictionConfidence = 0.0;
	}
	Patient(const Patient& p)
	{
		id = p.id;
		name = p.name;
		age = p.age;
		severity = p.severity;
		diagnosedDisease = p.diagnosedDisease;
		predictionConfidence = p.predictionConfidence;

		symptoms = new int[NUM_SYMPTOMS];
		for (int i = 0; i < NUM_SYMPTOMS; i++)
			symptoms[i] = p.symptoms[i];
	}

	~Patient()
	{
		delete[] symptoms;
	}
	void assignID() {
		id = IDManager::getNextID();
	}
};