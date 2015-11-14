#include "graphm.h"
const int MAXLINESIZE = 60;
const int RIDICULOUSNUMBER = 987654321;

GraphM::GraphM()
{
	initializeData();
}


GraphM::~GraphM()
{
}

void GraphM::initializeData()
{
	for (int x = 0; x < MAXNODES; x++)
	{
		for (int y = 0; y < MAXNODES; y++)
		{
			if (x == y)
			{
				C[x][y] = 0;
			}
			else
			{
				C[x][y] = RIDICULOUSNUMBER;
			}
		}
	}
	for (int x = 0; x < MAXNODES; x++)
	{
		for (int y = 0; y < MAXNODES; y++)
		{
			if (x == y)
			{
				T[x][y].dist = 0;
			}
			else
			{
				T[x][y].dist = RIDICULOUSNUMBER;
			}
			T[x][y].visited = false;
			T[x][y].path = x;
		}
	}
}

void GraphM::initializeDataAfter()
{
	for (int x = 0; x < MAXNODES; x++)
	{
		for (int y = 0; y < MAXNODES; y++)
		{
			if (x == y)
			{
				T[x][y].dist = 0;
			}
			else
			{
				T[x][y].dist = RIDICULOUSNUMBER;
			}
			T[x][y].visited = false;
			T[x][y].path = x;
		}
	}
}

void GraphM::buildGraph(ifstream& infile)
{
	int count;
	for (;;)
	{
		char s[MAXLINESIZE];
		for (int i = 0; i < MAXLINESIZE; i++)
		{
			s[i] = ' ';
		}
		infile.getline(s, MAXLINESIZE);
		if (infile.eof())
		{
			break;
		}
		count = 1;
		initializeData();
		if (isdigit(s[0]))
		{
			size = (((int) s[0]) - 48);
			for (int i = 1; i <= size; i++)
			{
				data[count] = NodeData();
				data[count].setData(infile);
				count++;
			}
			infile.getline(s, MAXLINESIZE);
			for (;;)
			{
				if (infile.eof())
				{ 
					break;
				}
				int i = 0, first, second, third;
				string temp;
				while (isdigit(s[i]))
				{
					temp += s[i];
					i++;
				}
				first = atoi(temp.c_str());
				i++;
				temp = "";
				while (isdigit(s[i]))
				{
					temp += s[i];
					i++;
				}
				second = atoi(temp.c_str());
				i++;
				temp = "";
				while (isdigit(s[i]))
				{
					temp += s[i];
					i++;
				}
				third = atoi(temp.c_str());
				if (first == 0 && second == 0 && third == 0)
				{
					return;
				}
				if (first > size || first <= 0 || second > size || second <= 0)
				{
					break;
				}
				insertEdge(first, second, third);
				infile.getline(s, MAXLINESIZE);
			}
		}
	}
}

bool GraphM::insertEdge(int first, int second, int amount)
{
	if (first > size || first <= 0 || second > size || second <= 0)
	{
		return false;
	}
	C[first][second] = amount;
	initializeDataAfter();
	return true;
}

bool GraphM::removeEdge(int first, int second)
{
	if (first > size || first <= 0 || second > size || second <= 0)
	{
		return false;
	}
	C[first][second] = RIDICULOUSNUMBER;
	initializeDataAfter();
	return true;
}

void GraphM::findShortestPath()
{
	int smallest, k, v;
	for (int i = 1; i <= size; i++)
	{
		for (int j = 1; j <= size; j++)
		{
			smallest = RIDICULOUSNUMBER;
			for (k = 1; k <= size; k++)
			{
				if (C[i][k] <= smallest && !T[i][k].visited)
				{
					v = k;
					smallest = C[i][k];
				}
			}
			for (k = 1; k <= size; k++)
			{
				if (T[i][k].dist > C[i][v] + C[v][k])
				{
					T[i][k].dist = C[i][v] + C[v][k];
					C[i][k] = C[i][v] + C[v][k];
					T[i][k].path = v;
				}
				if (C[i][k] < T[i][k].dist)
				{
					T[i][k].dist = C[i][k];
					T[i][k].path = k;
				}
			}
			T[i][v].visited = true;
		}
		/*
		for (int j = 1; j <= size; j++)
		{
			std::cout << "from " << i
				<< " to " << j << " is "
				<< T[i][j].dist << endl;
		}
		*/
	}
	analyzePaths();
	for (int i = 0; i <= size; i++)
	{
		for (int j = 1; j <= size; j++)
		{
			T[i][j].visited = false;
		}
	}
}

void GraphM::analyzePaths()
{
}

void GraphM::displayAll() const
{
	std::cout << "Description";
	displaySpace(5);
	std::cout << "From node";
	displaySpace(2);
	std::cout << "To node";
	displaySpace(2);
	std::cout << "Dijkstra's";
	displaySpace(2);
	std::cout << "Path" << endl;
	for (int i = 1; i <= size; i++)
	{
		std::cout << data[i] << endl;
		for (int j = 1; j <= size; j++)
		{
			if (i != j)
			{
				displaySpace(20);
				std::cout << i;
				displaySpace(8);
				std::cout << j;
				displaySpace(10);
				if (T[i][j].dist != RIDICULOUSNUMBER)
				{
					std::cout << T[i][j].dist;
					displaySpace(8);
					displayPaths(i, j);
					std::cout << endl;
				}
				else
				{
					std::cout << "---";
					displaySpace(8);
					std::cout << endl;
				}
			}
		}
	}
	std::cout << endl << endl;
}

void GraphM::displaySpace(int num) const
{
	for (int i = 0; i < num; i++)
	{
		std::cout << " ";
	}
}

void GraphM::display(int first, int second) const
{
	displaySpace(2);
	std::cout << first;
	displaySpace(5);
	std::cout << second;
	displaySpace(5);
	if (T[first][second].dist != RIDICULOUSNUMBER)
	{
		std::cout << T[first][second].dist;
		displaySpace(5);
		displayPaths(first, second);
		std::cout << endl;
	}
	else
	{ 
		std::cout << "---";
		displaySpace(5);
		std::cout  << endl;
	}
	for (int i = 1; i <= size; i++)
	{
		std::cout << data[i] << endl
			<< endl << endl;
	}
}

void GraphM::displayPaths(int i, int j) const
{
	if (i != j)
	{
		if (T[i][j].path != 0)
		{
			displayPaths(i, T[i][j].path);
		}
	}
	std::cout << j;
	displaySpace(1);
}