//https://www.geeksforgeeks.org/find-paths-given-source-destination/

#include "river.h"
#include <algorithm> // you are allowed to use std::sort from this library
#include <vector>
#include <queue>
#include <iostream>
#include <list>
// add your includes here

using namespace std;

vector<vector<int>> make_matrix(river M);
vector<int> Nodes; //global vector

class Graph
{
	int V;			// No. of vertices in graph
	list<int> *adj; // Pointer to an array containing adjacency lists

	// A recursive function used by printAllPaths()
	void printAllPathsUtil(int, int, bool[], int[], int &);

public:
	Graph(int V); // Constructor
	void addEdge(int u, int v);
	void printAllPaths(int s, int d);
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

void Graph::addEdge(int u, int v)
{
	adj[u].push_back(v); // Add v to u’s list.
}

// Prints all paths from 's' to 'd'
void Graph::printAllPaths(int s, int d)
{
	// Mark all the vertices as not visited
	bool *visited = new bool[V];

	// Create an array to store paths
	int *path = new int[V];
	int path_index = 0; // Initialize path[] as empty

	// Initialize all vertices as not visited
	for (int i = 0; i < V; i++)
		visited[i] = false;

	// Call the recursive helper function to print all paths
	printAllPathsUtil(s, d, visited, path, path_index);
}

void Graph::printAllPathsUtil(int u, int d, bool visited[],
							  int path[], int &path_index)
{
	// Mark the current node and store it in path[]
	visited[u] = true;
	path[path_index] = u;
	path_index++;

	// If current vertex is same as destination, then print
	// current path[]
	if (u == d)
	{
		for (int i = 0; i < path_index; i++)
		{
			//cout << path[i] << " ";
			if (i == 0)
				Nodes.push_back(path[0]);
		}
		//cout << endl;
	}
	else // If current vertex is not destination
	{
		// Recur for all the vertices adjacent to current vertex
		list<int>::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
			if (!visited[*i])
				printAllPathsUtil(*i, d, visited, path, path_index);
	}

	// Remove current vertex from path[] and mark it as unvisited
	path_index--;
	visited[u] = false;
}

// part (a)

std::vector<int> start(river const &r, int t)
{

	vector<vector<int>> Mat = make_matrix(r);
	int rows = Mat.size();
	int cols = Mat[0].size();

	Graph g(rows);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (Mat[i][j] == 1)
			{
				g.addEdge(i, j);
			}
		}
	}

	//create a vector of all indegree = 0 noded
	vector<int> InDeg;
	for (int i = 0; i < cols; i++)
	{
		int count = 0;
		for (int j = 0; j < rows; j++)
		{
			if (Mat[j][i] == 1)
			{
				count++;
			}
		}
		if (!count)
		{
			InDeg.push_back(i);
		}
	}
	sort(InDeg.begin(), InDeg.end());

	int s;
	int d = t;

	for (int i = 0; i < InDeg.size(); i++)
	{
		s = InDeg[i];
		g.printAllPaths(s, d);
	}
	for (int i = 0; i < Nodes.size(); i++)
	{
		//cout<<"Nodes of "<<i<<" is: "<<Nodes[i]<<endl;
	}
	return Nodes; // don't forget to change this
}

// part (b)
std::vector<int> meet(river const &r, int ryan, int mira)
{

	// your implementation here

	return {}; // don't forget to change this
}

vector<vector<int>> make_matrix(river M)
{

	vector<vector<int>> Matrix;
	int rows = M.size();
	int cols = M[0].size();

	for (int i = 0; i < rows; i++)
	{
		vector<int> v1;
		for (int j = 0; j < cols; j++)
		{
			if (M[i][j] == 1)
			{
				v1.push_back(1);
			}
			else if (M[i][j] == 0)
			{
				v1.push_back(0);
			}
		}
		Matrix.push_back(v1);
	}

	return Matrix;
}

/*
// Driver program
int main()
{
	// Create a graph given in the above diagram
	river r1 = {// river network in part (a)
				{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
				{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
				{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};





start(r1, 8);





vector<vector<int>> Mat = make_matrix(r1);
int rows = Mat.size();
int cols = Mat[0].size();


Graph g(rows);
	
for (int i = 0; i < rows; i++)
{
	for (int j = 0; j < cols; j++)
	{
		if (Mat[i][j] == 1)
		{
			g.addEdge(i,j);
		}
	}
}

//create a vector of all indegree = 0 noded
	vector<int> InDeg;
	for (int i = 0; i < cols; i++)
	{
		int count = 0;
		for (int j = 0; j < rows; j++)
		{
			//count = 0;
			if (Mat[j][i] == 1)
			{
				count++;
			}
		}
		if(!count){
			InDeg.push_back(i);
			//cout << "row " << i << " has in degree of zero." << endl;
		}
	}
	sort(InDeg.begin(), InDeg.end());
		

	int s;
	int d = 1;

	for (int i = 0; i < InDeg.size(); i++)
	{
		s = InDeg[i];
		cout << "Following are all different paths from " << s << " to " << d << endl;
		g.printAllPaths(s, d);
	}

	



	return 0;
}


*/
