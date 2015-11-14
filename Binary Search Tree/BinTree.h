#pragma once
#include <iostream>
#include <string>
#include "NodeData.h"
using namespace std;

class BinTree
{
	friend ostream & operator<<(ostream &, const BinTree &);

public:

	////////////////
	//Constructors//
	////////////////
	BinTree(); // constructor
	BinTree(const BinTree &); // copy constructor
	~BinTree(); // destructor, calls makeEmpty

	////////////////////
	//Member Functions//
	////////////////////
	bool isEmpty() const; // true if tree is empty, otherwise false
	void makeEmpty(); // make the tree empty so isEmpty returns true
	bool insert(NodeData *); // inserts a new node into the tree
	bool retrieve(const NodeData &, NodeData*&) const; // finds the NodeData and sets the pointer to that Data
	void displaySideways() const; // provided, displays the tree sideways
	void bstreeToArray(NodeData *[]); // Creates an array from a tree then empties the tree
	void arrayToBSTree(NodeData *[]); // Takes an array and makes a balanced BS Tree from it
	int getHeight(const NodeData &) const; // Gets the height of a certain Node containing the parameter

	//////////////////////
	//Operator Overloads//
	//////////////////////
	BinTree& operator=(const BinTree &); // Operator = overload
	bool operator==(const BinTree &) const; // Operator == overload
	bool operator!=(const BinTree &) const; // Operator != overload

private:

	//////////////////
	//Node Structure//
	//////////////////
	struct Node 
	{
		NodeData *data; // pointer to data object
		Node *left; // left subtree pointer
		Node *right; // right subtree pointer
	};
	Node* root; // root of the tree

	////////////////////
	//Helper Functions//
	////////////////////
	void sideways(Node*, int) const; // provided, helper for displaySideways()
	void makeEmpty(Node *, NodeData *&); // make empty helper 
	bool childrenExist(Node *leaf) const; // checks to see if a Node has a left or right
	bool insert(NodeData *, Node *); // insert helper
	bool retrieve(const NodeData &, NodeData *&, Node *) const; // retrieve helper
	bool retrieveNode(const NodeData &, Node *, Node *&ret) const; // a get Height helper to get a Node
	void getHeightHelper(Node *, int &, int n) const; // helper function to get height of a Node
	void bstreeToArray(NodeData* [], Node *, int &); // helper to bstree to array
	void arrayToBSTree(NodeData* array[], Node* &, int, int); // helper to array to bstree
	//void deleteNodeData(NodeData *&); //deletes Node Data from a Node

	/////////////////////////////
	//Operator Overload Helpers//
	/////////////////////////////
	void operatorEqualsHelper(Node *&, const Node *); //Provided for = and copy constructor
	bool ComparisonHelper(Node *, Node *) const; //Provided for != and ==
	void inOrderHelper(Node *, ostream&) const; // Helper to print the tree in order
};


