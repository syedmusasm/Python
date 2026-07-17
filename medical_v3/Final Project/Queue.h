#pragma once
#include"QueueNode.h";
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