#include "graphl.h"
const int MAXLINESIZE = 60;
const int RIDICULOUSNUMBER = 987654321;

graphl::graphl()
{
	initializeData();
}


graphl::~graphl()
{
	makeEmpty();
}

void graphl::makeEmpty()
{
	for (int i = 1; i <= size; i++)
	{
		if (AdjList[i].edgeHead == NULL)
		{
			return;
		}
		else
		{
			EdgeNode *t = AdjList[i].edgeHead;
			EdgeNode *deleter = NULL;
			while (t != NULL)
			{
				deleter = t;
				t = t->nextEdge;
				delete deleter;
			}
			delete t;
			t = NULL;
		}
		AdjList[i].edgeHead = NULL;
	}
}

void graphl::initializeData()
{
	for (int i = 1; i <= MAXNODESL; i++)
	{
		AdjList[i].visited = false;
	}
}

void graphl::buildGraph(istream& infile)
{
	int fromNode, toNode; 

	makeEmpty();   

	infile >> size;             
	if (infile.eof()) return; 

	string s;        
	getline(infile, s);

	for (int i = 1; i <= size; i++) {
		AdjList[i].data.setData(infile);
	}

	for (;;) {
		infile >> fromNode >> toNode;
		if (fromNode == 0 && toNode == 0)
		{
			getline(infile, s);
			int pos = infile.tellg();
			if (infile.eof())
			{
				return;
			}
			else
			{
				infile.seekg(pos);
				displayGraph();
				initializeData();
				buildGraph(infile);
			}
		}

		insertEdge(fromNode, toNode);
	}
}

bool graphl::insertEdge(int first, int amount)
{
	if (first > size || first <= 0 || amount <= 0)
	{
		return false;
	}
	/*
	if (AdjList[first].edgeHead == NULL)
	{
		AdjList[first].edgeHead = new EdgeNode;
		AdjList[first].edgeHead->adjGraphNode = amount;
		return true;
	}*/
	else
	{
		EdgeNode *insert = new EdgeNode;
		insert->adjGraphNode = amount;
		insert->nextEdge = AdjList[first].edgeHead;		
		AdjList[first].edgeHead = insert;
		return true;
	}
}

bool graphl::removeEdge(int index) {
	EdgeNode* current;
	current = AdjList[index].edgeHead;
	AdjList[index].edgeHead = AdjList[index].edgeHead->nextEdge;

	current->nextEdge = NULL;
	delete current;
	current = NULL;
	return true;
}

void graphl::depthFirstSearch()
{
	for (int i = 1; i <= size; i++)
	{
		if (!AdjList[i].visited)
		{
			depthFirstSearch(i);
		}
	}
}

void graphl::depthFirstSearch(int v)
{
	AdjList[v].visited = true;
	std::cout << v << " ";
	EdgeNode *traverse = AdjList[v].edgeHead;
	while (traverse != NULL)
	{
		if (!AdjList[traverse->adjGraphNode].visited)
		{
			depthFirstSearch(traverse->adjGraphNode);
			traverse = traverse->nextEdge;
		}
		else
		{
			traverse = traverse->nextEdge;
		}
	}
}

void graphl::displayGraph()
{
	std::cout << "Graph:" << endl;
	for (int i = 1; i <= size; i++)
	{
		std::cout << "Node " << i;
		displaySpace(8);
		std::cout << AdjList[i].data << endl;
		EdgeNode *t = AdjList[i].edgeHead;
		while (t != NULL)
		{
			displaySpace(2);
			std::cout << "edge " << i 
				<< " " << t->adjGraphNode 
				<< endl;
			t = t->nextEdge;
		}
	}
	std::cout << endl << endl
		<< "Depth-first ordering: ";
	depthFirstSearch();
	std::cout << endl << endl << endl;
}

void graphl::displaySpace(int num) const
{
	for (int i = 0; i < num; i++)
	{
		std::cout << " ";
	}
}