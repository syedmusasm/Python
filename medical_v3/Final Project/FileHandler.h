#pragma once
#include"MultiClassLR.h";
class FileHandler {
public:
	static void savePatient(Patient* p)
	{
		ofstream out("patient.txt", ios::app);
		if (!out)
		{
			cout << "Error opening patient.txt\n";
			return;
		}
		out << p->id << "," << p->name << "," << p->age << "," << p->severity << endl;
		out.close();
	}

	static void displayPatients()
	{
		ifstream in("patient.txt");
		if (!in)
		{
			cout << "patient.txt not found.\n";
			return;
		}
		int id;
		string name;
		int age;
		int severity;
		char comma;
		cout << "\n===== PATIENT RECORDS =====\n";
		while (in >> id >> comma)
		{
			getline(in, name, ',');
			in >> age >> comma;
			in >> severity;
			in.ignore(1000, '\n');
			cout << "ID       : " << id << endl;
			cout << "Name     : " << name << endl;
			cout << "Age      : " << age << endl;
			cout << "Severity : " << severity << endl;
			cout << "-------------------------\n";
		}
		in.close();
	}
	static void saveRecords(LinkedList& records)
	{
		ofstream outFile("diagnosis_records.txt", ios::app);
		if (!outFile)
		{
			cout << "Error: Cannot open file.\n";
			return;
		}
		ListNode* temp = records.getHead();
		while (temp != NULL)
		{
			outFile << temp->data->name << "," << temp->data->age << "," << temp->data->diagnosedDisease << "," << temp->data->predictionConfidence << "%\n";

			temp = temp->next;
		}

		outFile.close();
	}
};