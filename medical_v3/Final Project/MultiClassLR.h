#pragma once
#include"LogisticRegression.h";
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