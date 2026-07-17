#pragma once
#include"DiseaseData.h"
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