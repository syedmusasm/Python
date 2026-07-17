#pragma once
#include"Stack.h";
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
