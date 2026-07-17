#pragma once
#include"StackNode.h";
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