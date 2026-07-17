#pragma once
#include"BSTNode.h";
class BST {
private:
	BSTNode* root;

	BSTNode* insertRec(BSTNode* node, DiseaseData* d) {
		if (node == NULL) return new BSTNode(d);
		if (d->diseaseName < node->data->diseaseName)
			node->left = insertRec(node->left, d);
		else if (d->diseaseName > node->data->diseaseName)
			node->right = insertRec(node->right, d);
		return node;
	}

	void inorderRec(BSTNode* root) {
		if (root != NULL) {
			inorderRec(root->left);
			cout << "- " << root->data->diseaseName << "\n";
			inorderRec(root->right);
		}
	}

	DiseaseData* searchRec(BSTNode* root, string key) {
		if (root == NULL || root->data->diseaseName == key) {
			if (root) return root->data;
			return NULL;
		}
		if (root->data->diseaseName < key)
			return searchRec(root->right, key);
		return searchRec(root->left, key);
	}

public:
	BST() { root = NULL; }
	void insert(DiseaseData* d) { root = insertRec(root, d); }
	void inorder() { inorderRec(root); }
	DiseaseData* search(string key) { return searchRec(root, key); }
};
