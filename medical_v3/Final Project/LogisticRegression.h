#pragma once
#include"MaxHeap.h";
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