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

class DiseaseData
{
public:
	string diseaseName;
	string description;

	DiseaseData()
	{
		diseaseName = "";
		description = "";
	}
	DiseaseData(string name, string desc)
	{
		diseaseName = name;
		description = desc;
	}
};
class ListNode
{
public:
	Patient* data;
	ListNode* next;

	ListNode(Patient* p)
	{
		data = new Patient(*p);
		next = NULL;
	}
	~ListNode()
	{
		delete data;
	}
};

class LinkedList
{
private:
	ListNode* head;
public:
	LinkedList()
	{
		head = NULL;
	}

	void insert(Patient* p)
	{
		ListNode* newNode = new ListNode(p);
		newNode->next = head;
		head = newNode;
	}

	void display()
	{
		ListNode* temp = head;
		if (!temp)
		{
			cout << "No prediction history found.\n";
			return;
		}
		while (temp != NULL)
		{
			cout << "Patient: " << temp->data->name << " | Predicted Disease: " << temp->data->diagnosedDisease << " (" << temp->data->predictionConfidence << "% confidence)\n";
			temp = temp->next;
		}
	}

	ListNode* getHead()
	{
		return head;
	}

	~LinkedList()
	{
		ListNode* temp = head;
		while (temp != NULL)
		{
			ListNode* next = temp->next;
			delete temp;
			temp = next;
		}
	}
};

class QueueNode
{
public:
	Patient* data;
	QueueNode* next;

	QueueNode(Patient* p)
	{
		data = p;
		next = NULL;
	}
};

class Queue
{
private:
	QueueNode* front;
	QueueNode* rear;
public:
	Queue()
	{
		front = NULL;
		rear = NULL;
	}

	void enqueue(Patient* p)
	{
		QueueNode* newNode = new QueueNode(p);
		if (rear == NULL)
		{
			front = rear = newNode;
			return;
		}
		rear->next = newNode;
		rear = newNode;
	}

	Patient* dequeue()
	{
		if (front == NULL)
		{
			return NULL;
		}
		QueueNode* temp = front;
		Patient* p = temp->data;
		front = front->next;
		if (front == NULL)
		{
			rear = NULL;
		}
		delete temp;
		return p;
	}

	bool isEmpty()
	{
		return front == NULL;
	}
};


class StackNode
{
public:
	Patient* data;
	StackNode* next;

	StackNode(Patient* p)
	{
		data = new Patient(*p);
		next = NULL;
	}
	~StackNode()
	{
		delete data;
	}
};

class Stack {
private:
	StackNode* top;
public:
	Stack() { top = NULL; }

	void push(Patient* p) {
		StackNode* newNode = new StackNode(p);
		newNode->next = top;
		top = newNode;
	}

	Patient* pop() {
		if (top == NULL) return NULL;
		StackNode* temp = top;
		Patient* p = new Patient(*(temp->data));
		top = top->next;
		delete temp;
		return p;
	}

	bool isEmpty() { return top == NULL; }
};

// --- 3.4 BINARY SEARCH TREE (Disease Dictionary) ---
class BSTNode {
public:
	DiseaseData* data;
	BSTNode* left;
	BSTNode* right;

	BSTNode(DiseaseData* d) {
		data = new DiseaseData(d->diseaseName, d->description);
		left = right = NULL;
	}
	~BSTNode() { delete data; }
};

class BST {
private:
	BSTNode* root;

	BSTNode* insertRec(BSTNode* node, DiseaseData* d) {
		if (node == NULL) return new BSTNode(d);
		if (d->diseaseName < node->data->diseaseName)
			node->left = insertRec(node->left, d);
		else if (d->diseaseName > node->data->diseaseName)
			node->right = insertRec(node->right, d);
		return node;
	}

	void inorderRec(BSTNode* root) {
		if (root != NULL) {
			inorderRec(root->left);
			cout << "- " << root->data->diseaseName << "\n";
			inorderRec(root->right);
		}
	}

	DiseaseData* searchRec(BSTNode* root, string key) {
		if (root == NULL || root->data->diseaseName == key) {
			if (root) return root->data;
			return NULL;
		}
		if (root->data->diseaseName < key)
			return searchRec(root->right, key);
		return searchRec(root->left, key);
	}

public:
	BST() { root = NULL; }
	void insert(DiseaseData* d) { root = insertRec(root, d); }
	void inorder() { inorderRec(root); }
	DiseaseData* search(string key) { return searchRec(root, key); }
};

// --- 3.5 MAX HEAP (Patient Triage by Severity) ---
class MaxHeap {
private:
	Patient** heapArray;
	int capacity;
	int heapSize;

	int parent(int i) { return (i - 1) / 2; }
	int left(int i) { return (2 * i + 1); }
	int right(int i) { return (2 * i + 2); }

	void swap(Patient*& a, Patient*& b) {
		Patient* temp = a;
		a = b;
		b = temp;
	}

	void maxHeapify(int i) {
		int l = left(i);
		int r = right(i);
		int largest = i;

		if (l < heapSize && heapArray[l]->severity > heapArray[largest]->severity)
			largest = l;
		if (r < heapSize && heapArray[r]->severity > heapArray[largest]->severity)
			largest = r;

		if (largest != i) {
			swap(heapArray[i], heapArray[largest]);
			maxHeapify(largest);
		}
	}

public:
	MaxHeap(int cap) {
		heapSize = 0;
		capacity = cap;
		heapArray = new Patient * [cap];
	}
	~MaxHeap() { delete[] heapArray; }

	void insert(Patient* p) {
		if (heapSize == capacity) {
			cout << "Heap Overflow!\n";
			return;
		}
		heapSize++;
		int i = heapSize - 1;
		heapArray[i] = p;

		while (i != 0 && heapArray[parent(i)]->severity < heapArray[i]->severity) {
			swap(heapArray[i], heapArray[parent(i)]);
			i = parent(i);
		}
	}

	Patient* extractMax() {
		if (heapSize <= 0) return NULL;
		if (heapSize == 1) {
			heapSize--;
			return heapArray[0];
		}
		Patient* root = heapArray[0];
		heapArray[0] = heapArray[heapSize - 1];
		heapSize--;
		maxHeapify(0);
		return root;
	}

	bool isEmpty() { return heapSize == 0; }
};
class LogisticRegression {
private:
	double* weights;
	double  bias;
	int     numFeatures;
	double  learningRate;
	int     iterations;

	double sigmoid(double z) { return 1.0 / (1.0 + exp(-z)); }

public:
	LogisticRegression(int features, double lr = 0.1, int iters = 200) {
		numFeatures = features;
		learningRate = lr;
		iterations = iters;
		weights = new double[numFeatures];
		for (int i = 0; i < numFeatures; i++) weights[i] = 0.0;
		bias = 0.0;
	}
	~LogisticRegression() { delete[] weights; }

	LogisticRegression(const LogisticRegression&) = delete;
	LogisticRegression& operator=(const LogisticRegression&) = delete;

	// Train with real feature matrix (full-batch gradient descent)
	void train(int** X, int* y, int numSamples) {
		for (int it = 0; it < iterations; it++) {
			double* dW = new double[numFeatures]();
			double  db = 0.0;
			for (int i = 0; i < numSamples; i++) {
				double z = bias;
				for (int j = 0; j < numFeatures; j++) z += weights[j] * X[i][j];
				double err = sigmoid(z) - y[i];
				db += err;
				for (int j = 0; j < numFeatures; j++) dW[j] += err * X[i][j];
			}
			double inv = 1.0 / numSamples;
			bias -= learningRate * db * inv;
			for (int j = 0; j < numFeatures; j++) weights[j] -= learningRate * dW[j] * inv;
			delete[] dW;
		}
	}

	double predictProbability(int* x) {
		double z = bias;
		for (int i = 0; i < numFeatures; i++) z += weights[i] * x[i];
		return sigmoid(z);
	}
};

// ============================================================================
// 5. MULTI-CLASS LOGISTIC REGRESSION (One-vs-Rest)
// ============================================================================

class MultiClassLR {
private:
	LogisticRegression** models;
	string* classes;
	int numClasses;
	int numFeatures;

	// ── CSV helpers (no extra headers) ─────────────────────────────────────

	// trim leading/trailing spaces and \r
	static void trimStr(string& s) {
		int start = 0, end = (int)s.size() - 1;
		while (start <= end && (s[start] == ' ' || s[start] == '\r')) start++;
		while (end >= start && (s[end] == ' ' || s[end] == '\r')) end--;
		s = s.substr(start, end - start + 1);
	}

	// find index of val in array of size n, return -1 if missing
	static int findIndex(const string* arr, int n, const string& val) {
		for (int i = 0; i < n; i++) if (arr[i] == val) return i;
		return -1;
	}

	// split one CSV line by comma → fills fields[], returns field count
	static int splitCSV(const string& line, string* fields, int maxFields) {
		int count = 0;
		string cur;
		for (int i = 0; i <= (int)line.size() && count < maxFields; i++) {
			char c = (i < (int)line.size()) ? line[i] : ',';
			if (c == ',') { trimStr(cur); fields[count++] = cur; cur = ""; }
			else cur += c;
		}
		return count;
	}

public:
	MultiClassLR(int nClasses, int nFeatures, string* classNames) {
		numClasses = nClasses;
		numFeatures = nFeatures;
		classes = new string[numClasses];
		models = new LogisticRegression * [numClasses];
		for (int i = 0; i < numClasses; i++) {
			classes[i] = classNames[i];
			models[i] = new LogisticRegression(numFeatures);
		}
	}
	~MultiClassLR() {
		for (int i = 0; i < numClasses; i++) delete models[i];
		delete[] models;
		delete[] classes;
	}
	MultiClassLR(const MultiClassLR&) = delete;
	MultiClassLR& operator=(const MultiClassLR&) = delete;
	void predictTopK(int* symptoms, string* topDiseases, double* topConfidences, int K = 5)
	{
		double* probs = new double[numClasses];
		bool* used = new bool[numClasses];

		for (int i = 0; i < numClasses; i++) {
			probs[i] = models[i]->predictProbability(symptoms) * 100.0;
			used[i] = false;
		}

		for (int k = 0; k < K; k++) {
			int best = -1;
			double bestVal = -1;

			for (int i = 0; i < numClasses; i++) {
				if (!used[i] && probs[i] > bestVal) {
					bestVal = probs[i];
					best = i;
				}
			}

			if (best == -1) break;

			used[best] = true;
			topDiseases[k] = classes[best];
			topConfidences[k] = probs[best];
		}

		delete[] probs;
		delete[] used;
	}

	// ── REAL TRAINING from CSV ──────────────────────────────────────────────
	void trainFromCSV(const string& csvPath, const string* symptomNames) {
		cout << "Loading dataset from: " << csvPath << " ...\n";

		ifstream fin(csvPath);
		if (!fin.is_open()) {
			cout << "ERROR: Cannot open " << csvPath << "\n"
				<< "Make sure the CSV is in the same folder as the executable.\n";
			return;
		}

		// allocate feature matrix and label array (MAX_ROWS rows)
		int** X = new int* [MAX_ROWS];
		int* y = new int[MAX_ROWS];
		for (int i = 0; i < MAX_ROWS; i++) {
			X[i] = new int[numFeatures]();   // zero-initialised
		}
		int numSamples = 0;

		string line;
		getline(fin, line); // skip header

		string* fields = new string[19]; // Disease + up to 17 symptom columns + guard

		while (getline(fin, line) && numSamples < MAX_ROWS) {
			if (line.empty()) continue;
			int nf = splitCSV(line, fields, 19);
			if (nf < 1) continue;

			string diseaseName = fields[0];
			int di = findIndex(classes, numClasses, diseaseName);
			if (di < 0) continue;   // disease not in our list – skip

			y[numSamples] = di;
			for (int j = 0; j < numFeatures; j++) X[numSamples][j] = 0;

			// columns 1..nf-1 are symptom names
			for (int c = 1; c < nf; c++) {
				if (fields[c].empty()) continue;
				int si = findIndex(symptomNames, numFeatures, fields[c]);
				if (si >= 0) X[numSamples][si] = 1;
			}
			numSamples++;
		}
		fin.close();
		delete[] fields;

		cout << "Loaded " << numSamples << " samples.\n";
		cout << "Training " << numClasses << " OvR classifiers (this takes ~10-20s)...\n";

		// One-vs-Rest: train one binary classifier per disease
		int* yBin = new int[numSamples];
		for (int c = 0; c < numClasses; c++) {
			for (int i = 0; i < numSamples; i++)
				yBin[i] = (y[i] == c) ? 1 : 0;
			models[c]->train(X, yBin, numSamples);

			if ((c + 1) % 5 == 0 || c == numClasses - 1)
				cout << "  Trained " << (c + 1) << "/" << numClasses << " classifiers\n";
		}
		delete[] yBin;

		for (int i = 0; i < MAX_ROWS; i++) delete[] X[i];
		delete[] X;
		delete[] y;

		cout << "Training complete.\n";
	}

	// ── PREDICTION ──────────────────────────────────────────────────────────
	string predict(int* symptoms, double& confidenceResult) {
		double maxProb = -1.0;
		int    bestClass = 0;
		cout << "\n";
		for (int c = 0; c < numClasses; c++) {
			double prob = models[c]->predictProbability(symptoms);
			//cout << classes[c] << " -> " << prob * 100.0 << "%\n";
			if (prob > maxProb) { maxProb = prob; bestClass = c; }
		}
		confidenceResult = maxProb * 100.0;
		return classes[bestClass];
	}
};


// ============================================================================
// 5. FILE HANDLING (Save/Load Operations)
// ============================================================================

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

// ============================================================================
// 6. MAIN PREDICTION SYSTEM CLASS
// ============================================================================

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
		cout << "\n--- AI System Prediction --- \n";
		if (H.isEmpty()) {
			cout << "No patients ready for prediction. Please queue and prioritize first.\n";
			return;
		}

		Patient* p = H.extractMax();
		cout << "Analyzing symptoms for " << p->name << " (Distress Level: " << p->severity << ")...\n";

		cout << "Answer 1 for YES, 0 for NO for the following symptoms:\n";

		// STEP 1: reset all symptoms to 0
		for (int i = 0; i < NUM_SYMPTOMS; i++)
			p->symptoms[i] = 0;

		
		displaySymptomsList();
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

		/*cout << "\n====================================\n";
		cout << "DIAGNOSIS REPORT\n";
		cout << "====================================\n";

		if (p->predictionConfidence < 25)
		{
			cout << "Prediction Confidence: "
				<< p->predictionConfidence << "%\n";

			cout << "No reliable disease prediction could be made.\n";
			cout << "Please consult a healthcare professional.\n";

			cout << "\nSymptoms Reported:\n";
			for (int i = 0; i < NUM_SYMPTOMS; i++)
			{
				if (p->symptoms[i] == 1)
					cout << "- " << symptomNames[i] << endl;
			}
		}
		else if (p->predictionConfidence < 50)
		{
			cout << "Prediction Confidence: "
				<< p->predictionConfidence << "%\n";

			cout << "Possible Disease: "
				<< p->diagnosedDisease << endl;

			cout << "Confidence Level: LOW\n";
		}
		else if (p->predictionConfidence < 75)
		{
			cout << "Prediction Confidence: "
				<< p->predictionConfidence << "%\n";

			cout << "Predicted Disease: "
				<< p->diagnosedDisease << endl;

			cout << "Confidence Level: MODERATE\n";
		}
		else
		{
			cout << "Prediction Confidence: "
				<< p->predictionConfidence << "%\n";

			cout << "Predicted Disease: "
				<< p->diagnosedDisease << endl;

			cout << "Confidence Level: HIGH\n";
		}

		cout << "====================================\n";*/
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

	void viewDiseaseDB() {
		cout << "\n--- Supported Disease Dictionary (BST Traversal) ---\n";
		diseaseDB.inorder();
	}

	void saveAllData() {
		FileHandler::saveRecords(predictionHistory);
	}
	void displayPatientRecords()
	{
		FileHandler::displayPatients();
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
			cout << "6. View Disease Dictionary\n";
			cout << "7. View Prediction History\n";
			cout << "8. Save Prediction Records\n";
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
				viewDiseaseDB();
				break;

			case 7:
				predictionHistory.display();
				break;

			case 8:
				saveAllData();
				break;

			case 9:
				cout << "Exiting...\n";
				break;
			}


		} while (choice != 9);
	}
};

// ============================================================================
// 7. ENTRY POINT
// ============================================================================

int main() {
	MedicalDiagnosisSystem app;
	app.run();
	return 0;
}
