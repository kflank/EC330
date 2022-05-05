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

vector<int> Nodes; //global vector for part a
vector<vector<int>> All_path;
vector<vector<int>> Ryan;
vector<vector<int>> Mira;

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
	vector<int> temp;
	if (u == d)
	{
		for (int i = 0; i < path_index; i++)
		{
			temp.push_back(path[i]);
			//cout << path[i] << " ";

			if (i == 0)
				Nodes.push_back(path[0]);
		}
		All_path.push_back(temp);
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

bool Is_Intersect(river const &r, int node)
{
	vector<int> intersect;
	vector<vector<int>> Mat = make_matrix(r);
	int rows = Mat.size();
	int cols = Mat[0].size();

	for (int i = 0; i < cols; i++)
	{
		int counter = 0;
		for (int j = 0; j < rows; j++)
		{
			if (Mat[j][i] == 1)
			{
				//cout<<"counter at "<<i<<" "<<j<<endl;
				counter++;
			}
		}
		if (counter >= 2)
		{
			//cout<<"push back "<<i<<endl;
			intersect.push_back(i);
		}
	}
	//cout<<"node is "<<node<<endl;
	//cout<<"intersect size is "<<intersect.size()<<endl;
	for (int i = 0; i < intersect.size(); i++)
	{
		if (intersect[i] == node)
		{
			//cout << "i is: " << i << endl;
			//cout << "intersect of " << i << " is: " << intersect[i] << endl;
			//cout<<"node "<<intersect[i]<<" is an intersect node"<<endl;
			return true;
		}
	}
	//cout<<"node "<<node<<" is not an intersect node"<<endl;
	return false;
}

vector<int> Compare(vector<int> R_vec, vector<int> M_vec)
{
	vector<int> meetpoint;
	for (int i = 0; i < R_vec.size(); i++)
	{
		for (int j = 0; j < M_vec.size(); j++)
		{
			if (R_vec[i] == M_vec[j])
				meetpoint.push_back(R_vec[i]);
		}
	}
	return meetpoint;
}

int search_min(vector<int> vec1, vector<int> vec2)
{
	int min = 1000000;
	vec1.insert(vec1.end(), vec2.begin(), vec2.end());
	for (int i = 0; i < vec1.size(); i++)
	{
		if (vec1[i] <= min)
		{
			min = vec1[i];
		}
	}
	return min;
}

// part (b)
std::vector<int> meet(river const &r, int ryan, int mira)
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
	//vector<int> InDeg;
	vector<int> OutDeg;
	for (int i = 0; i < cols; i++)
	{
		int countOut = 0;
		int countIn = 0;
		for (int j = 0; j < rows; j++)
		{
			if (Mat[i][j] == 1)
			{
				countOut++;
			}
		}

		if (!countOut)
		{
			OutDeg.push_back(i);
			//cout << "row " << i << " has in degree of zero." << endl;
		}
	}
	sort(OutDeg.begin(), OutDeg.end());

	int s; //starting point
	int d; //end point

	for (int i = 0; i < OutDeg.size(); i++)
	{
			   //ryans starting point is 0
		d = OutDeg[i]; //if you are able to make it to the same node then you should be able to make it to the same Node out
		//cout << "Following are all different paths from " << s << " to " << d << " for ryan" << endl;
		g.printAllPaths(ryan, d);
		//cout<<"Ryan vector: "<<All_path[0][0]<<","<<All_path[0][1]<<","<<All_path[0][2]<<endl;
	}
	int Ryan_size = All_path.size();

	for (int i = 0; i < OutDeg.size(); i++)
	{
		   //Mira starting point is 2
		d = OutDeg[i]; //if you are able to make it to the same node then you should be able to make it to the same Node out
		//cout << "Following are all different paths from " << s << " to " << d << " for Mira" << endl;
		g.printAllPaths(mira, d);
	}

	int Mira_size = All_path.size() - Ryan_size;

	for (int i = 0; i < Ryan_size; i++)
	{
		Ryan.push_back(All_path[i]); //all the path Ryan traverses through
	}

	for (int i = Ryan_size; i < All_path.size(); i++)
	{
		Mira.push_back(All_path[i]); //all the paths Mira traverses through
	}

	vector<int> intersections;
	vector<int> temp1;
	vector<int> precursor;
	int num;
	for (int i = 0; i < Ryan.size(); i++)
	{
		for (int j = 0; j < Mira.size(); j++)
		{
			temp1 = Compare(Ryan[i], Mira[j]);
			precursor.insert(precursor.end(), temp1.begin(), temp1.end());
			if (!temp1.empty())
			{
				if (search(precursor.begin(), precursor.end(), temp1.begin(), temp1.end()) != precursor.end())
				{
					//if one of the intersections is found to check if one intersection might be a precursor to the other
					num = search_min(temp1, precursor);
					if (find(intersections.begin(), intersections.end(), num) == intersections.end())
						//if its a new intersection
						intersections.push_back(num);
				}
				else
				{
					num = search_min(temp1, temp1);
					if (find(intersections.begin(), intersections.end(), num) == intersections.end())
						//if its a new intersection
						intersections.push_back(num);
				}
			}
		}
	}

	return intersections;

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

	river r2 = {// river network in part (b)
				{0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 1, 0, 0, 1, 0, 0},
				{0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
				{0, 0, 0, 0, 0, 1, 0, 1, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

	//start(r1, 8);

	//create a vector of all indegree = 0 noded
	//vector<int> InDeg;

	/*
	vector<int> vecEPM;
	for (int i = Ryan_size - 1; i >= 0; i--)
	{
		int tempEPM;
		int counter = 1;
		for (int j = Mira_size - 1; j >= 0; j--)
		{
			for (int k = Ryan[i].size() - 1; k >= 0; k--)
			{
				for (int l = Mira[j].size() - 1; l >= 0; l--)
				{
					if (Ryan[i][k] == Mira[j][l])
					{
						tempEPM = Ryan[i][k];
					}
				}
				if (tempEPM && Is_Intersect(r1, tempEPM)) //the column temp has more than 2)
				{
					cout<<"push back at i: "<<i<<" j: "<<j<<" k: "<<k<<endl;
					cout<<"temp is: "<<tempEPM<<endl;
					vecEPM.push_back(tempEPM);
				}
			}
		}
	}

	vector<int> intersections;
	for (int i = 0; i < Ryan.size(); i++)
	{
		for (int j = 0; j < Mira.size(); j++)
		{
			int comparison = Compare(Ryan[i], Mira[j]);
			if (find(intersections.begin(), intersections.end(), comparison) == intersections.end())
			{
				intersections.push_back(comparison);
			}
		}
	}

	for (int i = 0; i < intersections.size(); i++)
	{
		cout << "intersections: " << intersections[i] << endl;
	}

	
for (int i = 0; i < vecEPM.size(); i++)
{
	cout<<" vecEPM is: "<<vecEPM[i]<<endl;
}


	return 0;
}
*/