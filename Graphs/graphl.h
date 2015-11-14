#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "nodedata.h"
const int MAXNODESL = 100;

struct EdgeNode; // forward reference for the compiler

struct GraphNode { // structs used for simplicity, use classes if desired
	EdgeNode* edgeHead = NULL; // head of the list of edges
	NodeData data;
	bool visited;
};
struct EdgeNode {
	int adjGraphNode; // subscript of the adjacent graph node
	EdgeNode* nextEdge = NULL;
};

class graphl
{
public:
	
	graphl();
	~graphl();

	void depthFirstSearch();
	void initializeData();
	void buildGraph(istream&);
	void makeEmpty();
	bool insertEdge(int, int);
	bool removeEdge(int);
	void displayGraph();
	void displaySpace(int) const;

private:
	void removeNode(int);
	int size = 0;
	GraphNode AdjList[MAXNODESL];
	void depthFirstSearch(int);
};

