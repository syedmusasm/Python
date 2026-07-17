#pragma once
#include"ListNode.h";
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