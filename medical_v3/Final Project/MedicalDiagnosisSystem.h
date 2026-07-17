#pragma once
#include"FileHandler.h"
class MedicalDiagnosisSystem {
private:
	Queue      assessmentQueue;
	MaxHeap    H;
	LinkedList predictionHistory;
	Stack      undoStack;
	BST        diseaseDB;
	MultiClassLR* aiModel;

	// ── Real disease & symptom names from dataset ──────────────────────────
	string diseaseNames[NUM_DISEASES] = {
		"(vertigo) Paroymsal  Positional Vertigo",
		"AIDS",
		"Acne",
		"Alcoholic hepatitis",
		"Allergy",
		"Arthritis",
		"Bronchial Asthma",
		"Cervical spondylosis",
		"Chicken pox",
		"Chronic cholestasis",
		"Common Cold",
		"Dengue",
		"Diabetes",
		"Dimorphic hemmorhoids(piles)",
		"Drug Reaction",
		"Fungal infection",
		"GERD",
		"Gastroenteritis",
		"Heart attack",
		"Hepatitis B",
		"Hepatitis C",
		"Hepatitis D",
		"Hepatitis E",
		"Hypertension",
		"Hyperthyroidism",
		"Hypoglycemia",
		"Hypothyroidism",
		"Impetigo",
		"Jaundice",
		"Malaria",
		"Migraine",
		"Osteoarthristis",
		"Paralysis (brain hemorrhage)",
		"Peptic ulcer diseae",
		"Pneumonia",
		"Psoriasis",
		"Tuberculosis",
		"Typhoid",
		"Urinary tract infection",
		"Varicose veins",
		"hepatitis A"
	};

	string symptomNames[NUM_SYMPTOMS] = {
		"abdominal_pain","abnormal_menstruation","acidity","acute_liver_failure",
		"altered_sensorium","anxiety","back_pain","belly_pain","blackheads",
		"bladder_discomfort","blister","blood_in_sputum","bloody_stool",
		"blurred_and_distorted_vision","breathlessness","brittle_nails","bruising",
		"burning_micturition","chest_pain","chills","cold_hands_and_feets","coma",
		"congestion","constipation","continuous_feel_of_urine","continuous_sneezing",
		"cough","cramps","dark_urine","dehydration","depression","diarrhoea",
		"dischromic _patches","distention_of_abdomen","dizziness",
		"drying_and_tingling_lips","enlarged_thyroid","excessive_hunger",
		"extra_marital_contacts","family_history","fast_heart_rate","fatigue",
		"fluid_overload","foul_smell_of urine","headache","high_fever",
		"hip_joint_pain","history_of_alcohol_consumption","increased_appetite",
		"indigestion","inflammatory_nails","internal_itching","irregular_sugar_level",
		"irritability","irritation_in_anus","itching","joint_pain","knee_pain",
		"lack_of_concentration","lethargy","loss_of_appetite","loss_of_balance",
		"loss_of_smell","malaise","mild_fever","mood_swings","movement_stiffness",
		"mucoid_sputum","muscle_pain","muscle_wasting","muscle_weakness","nausea",
		"neck_pain","nodal_skin_eruptions","obesity","pain_behind_the_eyes",
		"pain_during_bowel_movements","pain_in_anal_region","painful_walking",
		"palpitations","passage_of_gases","patches_in_throat","phlegm","polyuria",
		"prominent_veins_on_calf","puffy_face_and_eyes","pus_filled_pimples",
		"receiving_blood_transfusion","receiving_unsterile_injections",
		"red_sore_around_nose","red_spots_over_body","redness_of_eyes","restlessness",
		"runny_nose","rusty_sputum","scurring","shivering","silver_like_dusting",
		"sinus_pressure","skin_peeling","skin_rash","slurred_speech",
		"small_dents_in_nails","spinning_movements","spotting_ urination","stiff_neck",
		"stomach_bleeding","stomach_pain","sunken_eyes","sweating","swelled_lymph_nodes",
		"swelling_joints","swelling_of_stomach","swollen_blood_vessels",
		"swollen_extremeties","swollen_legs","throat_irritation","toxic_look_(typhos)",
		"ulcers_on_tongue","unsteadiness","visual_disturbances","vomiting",
		"watering_from_eyes","weakness_in_limbs","weakness_of_one_body_side",
		"weight_gain","weight_loss","yellow_crust_ooze","yellow_urine",
		"yellowing_of_eyes","yellowish_skin"
	};

public:
	MedicalDiagnosisSystem() : H(100) {
		// Populate BST disease dictionary
		for (int i = 0; i < NUM_DISEASES; i++) {
			DiseaseData d(diseaseNames[i], "Medical condition from symptoms dataset.");
			diseaseDB.insert(&d);
		}

		// Build & train the ML model from the real CSV
		aiModel = new MultiClassLR(NUM_DISEASES, NUM_SYMPTOMS, diseaseNames);
		aiModel->trainFromCSV("Symptomsdata.csv", symptomNames);
	}

	~MedicalDiagnosisSystem() { delete aiModel; }
	void displaySymptomsList() {
		cout << "\n========== SYMPTOM LIST ==========\n";
		for (int i = 0; i < NUM_SYMPTOMS; i++) {
			cout << (i + 1) << ". " << symptomNames[i] << endl;
		}
		cout << "==================================\n";
	}
	bool safeIntInput(int& value) {
		cin >> value;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
			return false;
		}
		return true;
	}
	void queuePatient() {
		string name;
		int age, severity;
		cout << "\n--- Enter Patient for Assessment ---\n";
		cout << "Enter Name: ";
		cin >> ws; // Clear buffer
		getline(cin, name);
		while (true) {
			cout << "Enter age (1-100): ";

			if (!safeIntInput(age)) {
				cout << "Invalid input! Enter a number.\n";
				continue;
			}

			if (age < 1 || age > 100) {
				cout << "Age must be between 1 and 100.\n";
				continue;
			}

			break;
		}
		while (true) {
			cout << "Enter Current Distress Level (1-10): ";

			if (!safeIntInput(severity)) {
				cout << "Invalid input! Enter a number.\n";
				continue;
			}

			if (severity < 1 || severity > 10) {
				cout << "Severity must be between 1 and 10.\n";
				continue;
			}

			break;
		}
		Patient* p = new Patient(name, age, severity);
		p->assignID();
		FileHandler::savePatient(p);

		if (severity > 6)
		{
			H.insert(p);
			cout << "Critical Patient " << name
				<< " automatically added to Max Heap (Priority Queue).\n";
		}
		else
		{
			assessmentQueue.enqueue(p);
			cout << "Patient " << name
				<< " added to the assessment queue.\n";
		}
	}

	void prioritizePatients() {
		cout << "\n--- Prioritizing Assessment Waitlist ---\n";
		if (assessmentQueue.isEmpty()) {
			cout << "No patients in the queue to prioritize.\n";
			return;
		}
		while (!assessmentQueue.isEmpty()) {
			Patient* p = assessmentQueue.dequeue();
			H.insert(p);
			cout << "Moved " << p->name << " to Prediction Priority Queue based on distress level.\n";
		}
	}

	void predictNextPatient() {
		//cout << "\n--- AI System Prediction --- \n";
		if (H.isEmpty()) {
			cout << "No patients ready for prediction. Please queue and prioritize first.\n";
			return;
		}

		Patient* p = H.extractMax();




		// STEP 1: reset all symptoms to 0
		for (int i = 0; i < NUM_SYMPTOMS; i++)
			p->symptoms[i] = 0;


		displaySymptomsList();

		cout << "\nEnter symptom numbers (1 to 131).\n";
		cout << "Enter 0 to finish input.\n";

		while (true) {
			int symID;

			cout << "Symptom: ";

			if (!(cin >> symID)) {
				cout << "Invalid input! Enter a number.\n";
				cin.clear();
				cin.ignore(1000, '\n');
				continue;
			}

			if (symID == 0) {
				break; // exit input loop
			}

			if (symID < 1 || symID > NUM_SYMPTOMS) {
				cout << "Invalid range! Enter 1 to 131 (or 0 to finish).\n";
				continue;
			}

			p->symptoms[symID - 1] = 1;
		}

		// Update the patient object using pass-by-reference for the probability
		string topDiseases[5];
		double topConf[5];

		aiModel->predictTopK(p->symptoms, topDiseases, topConf, 5);

		cout << "\n====================================\n";
		cout << "AI DIAGNOSIS (TOP 5 RESULTS)\n";
		cout << "====================================\n";

		for (int i = 0; i < 5; i++) {
			cout << i + 1 << ". " << topDiseases[i]
				<< " -> " << topConf[i] << "%\n";
		}

		p->diagnosedDisease = topDiseases[0];
		p->predictionConfidence = topConf[0];
		if (p->diagnosedDisease == "Heart attack" ||p->diagnosedDisease == "Tuberculosis")
		{
			cout << "\n⚠ EMERGENCY ALERT: Immediate hospital referral recommended!\n";
		}

	
		// Save to History (LinkedList) and Stack (Undo)
		predictionHistory.insert(p);
		undoStack.push(p);

		delete p; // We made deep copies inside insert and push.
	}

	void undoLastPrediction() {
		if (undoStack.isEmpty()) {
			cout << "No prediction to undo.\n";
			return;
		}
		Patient* p = undoStack.pop();
		cout << "Reverted prediction record for patient: " << p->name << "\n";
		delete p;
	}

	void searchPatient(int searchID) {
		ifstream in("patient.txt");
		int id, age, severity;
		string name;
		char comma;

		while (in >> id >> comma) {
			getline(in, name, ',');
			in >> age >> comma;
			in >> severity;
			in.ignore();

			if (id == searchID) {
				cout << "FOUND: " << name << " Age: " << age << "\n";
				return;
			}
		}
		cout << "Patient not found.\n";
	}

	void saveAllData() {
		FileHandler::saveRecords(predictionHistory);
	}
	void displayPatientRecords()
	{
		FileHandler::displayPatients();
	}
	void editPatient(int searchID)
	{
		fstream file("patient.txt", ios::in | ios::out);

		int id, age, severity;
		string name;
		char comma;

		bool found = false;

		while (file >> id >> comma)
		{
			getline(file, name, ',');
			file >> age >> comma;
			file >> severity;
			file.ignore();

			if (id == searchID)
			{
				cout << "Found: " << name << endl;

				cout << "Enter new age: ";
				cin >> age;

				cout << "Enter new severity (1-10): ";
				cin >> severity;

				cout << "Updated successfully.\n";
				found = true;
				break;
			}
		}

		if (!found)
			cout << "Patient not found.\n";

		file.close();
	}

	void run() {
		int choice;

		do {
			cout << "\n===============================================\n";
			cout << "   MEDICAL DIAGNOSIS PREDICTION SYSTEM   \n";
			cout << "===============================================\n";
			cout << "1. Add Patient\n";
			cout << "2. Display Patient Records\n";
			cout << "3. Prioritize Patients by Severity\n";
			cout << "4. Run Symptoms through AI Prediction Model\n";
			cout << "5. Undo Last Prediction\n";
			cout << "6. Search for Patient through Id\n";
			cout << "7. View Prediction History\n";
			cout << "8. Edit Patients\n";
			cout << "9. Exit\n";
			while (true) {
				cout << "Enter choice: ";

				if (!safeIntInput(choice)) {
					cout << "Invalid input! Enter a number between 1 and 9.\n";
					continue;
				}

				if (choice < 1 || choice > 9) {
					cout << "Choice must be between 1 and 9.\n";
					continue;
				}

				break;
			}
			switch (choice)
			{
			case 1:
				queuePatient();
				break;

			case 2:
				displayPatientRecords();
				break;

			case 3:
				prioritizePatients();
				break;

			case 4:
				predictNextPatient();
				break;

			case 5:
				undoLastPrediction();
				break;

			case 6:
				int Id;
				cout << "Enter search Id:";
				cin >> Id;
				searchPatient(Id);
				break;

			case 7:
				predictionHistory.display();
				saveAllData();
				break;

			case 8:
				int Id;
				cout << "Enter Id you want to edit:";
				cin >> Id;
				editPatient(Id);
				break;

			case 9:
				cout << "Exiting...\n";
				break;
			}


		} while (choice != 9);
	}
};