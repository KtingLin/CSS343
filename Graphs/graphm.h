#pragma once
#include "nodedata.h"
#include <string>
#include <iostream>
#include <vector>

const int MAXNODES = 100;

class GraphM
{
public:

	////////////////
	//Constructors//
	////////////////

	//default constructor
	GraphM();
	
	//destructor that does nothing
	~GraphM();

	////////////////////
	//Member Functions//
	////////////////////

	//Builds the graph from the given text file
	//IMPORTANT: After 0 0 0, if there is more,
	//this function will display the previous entries
	//then continue on to the next set
	void buildGraph(ifstream&);
	//Inserts an edge with the first int being
	//
	bool insertEdge(int, int, int);
	bool removeEdge(int, int);
	void findShortestPath();
	void displayAll() const;
	void display(int, int) const;
	void displaySpace(int) const;
	void analyzePaths();


private:

	struct TableType 
	{
		bool visited; // whether node has been visited
		int dist; // currently known shortest distance from source
		int path; // previous node in path of min dist
	};

	NodeData data[MAXNODES]; // data for graph nodes information
	int C[MAXNODES][MAXNODES]; // Cost array, the adjacency matrix
	int size = 0; // number of nodes in the graph
	TableType T[MAXNODES][MAXNODES]; // stores visited, distance, path 
	int paths[MAXNODES][MAXNODES];
	void initializeData();
	void initializeDataAfter();
	void displayPaths(int, int) const;

};

