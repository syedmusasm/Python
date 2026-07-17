#pragma once
#include"BST.h";
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