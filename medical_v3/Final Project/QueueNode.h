#pragma once
#include"LinkedList.h";
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