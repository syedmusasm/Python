#pragma once
#include"Queue.h";
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