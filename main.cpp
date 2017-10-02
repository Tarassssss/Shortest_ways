#include <cassert>
#include <iostream>
#include <stdio.h>
#include <limits.h>
#include "parse_stl.h"


// A utility function to find the vertex with minimum distance value, from the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[], int V)
{
	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

// A utility function to print the constructed distance array
void printSolution(int dist[], int n, int V)
{
	printf("Vertex   Distance from Sourcen\n");
	for (int i = 0; i < V; i++)
	{
		if (dist[i] == INT_MAX)
			std::cout << "Can't reach it\n";
		else
		std::cout << dist[i] << std::endl;
	}
}


int main(int argc, char* argv[]) {

  std::string stl_file_name = "./Example.stl";
	
  if (argc == 2) {
    stl_file_name = argv[1];
  } else if (argc > 2) {
    std::cout << "ERROR: Too many command line arguments" << std::endl;
  }
  std::vector<stl::point> points;
  auto info = stl::parse_stl(stl_file_name, points);
  for (int i(0); i < points.size(); i++)
	  points[i].index = i;

  std::vector<stl::triangle> triangles = info.triangles;
  std::cout << "STL HEADER = " << info.name << std::endl;
  
  int N = points.size();
  //Create the matrix where will be saved distances of appropriate vertices (indexes of arrays are indexes of vertices)

  float **A = new float *[N];
  for (int i(0); i < N; i++)
	  A[i] = new float[N];
  for (int i(0); i < N; i++)
	  for (int j(0); j < N; j++)
		  A[i][j] = 0;
  
  for (int i(0); i < points.size(); i++)
	  for (int j(0); j < points[i].leng.size(); j++)
		  A[i][points[i].leng[j].first] = points[i].leng[j].second;

      int V = N;	
	  int src = 0;
	  int *dist= new int[V];     // The output array.  dist[i] will hold the shortest distance from src to i

	  bool *sptSet= new bool[V]; // sptSet[i] will true if vertex i is included in shortest path tree or shortest distance from src to i is finalized

								 // Initialize all distances as INFINITE and stpSet[] as false
	  for (int i = 0; i < V; i++)
		  dist[i] = INT_MAX, sptSet[i] = false;

	  // Distance of source vertex from itself is always 0
	  dist[src] = 0;

	  // Find shortest path for all vertices
	  for (int count = 0; count < V - 1; count++)
	  {
		  // Pick the minimum distance vertex from the set of vertices not yet processed. u is always equal to src in first iteration.
		  int u = minDistance(dist, sptSet, V);

		  // Mark the picked vertex as processed
		  sptSet[u] = true;

		  // Update dist value of the adjacent vertices of the picked vertex.
		  for (int v = 0; v < V; v++)

			  // Update dist[v] only if is not in sptSet, there is an edge from u to v, and total weight of path from src to  v through u is smaller than current value of dist[v]
			  if (!sptSet[v] && A[u][v] && dist[u] != INT_MAX
				  && dist[u] + A[u][v] < dist[v])
				  dist[v] = dist[u] + A[u][v];
	  }

	  // print the constructed distance array
	  printSolution(dist, V, V);
	  system("pause");

  for (int i(0); i < N; i++)
	  delete[] A[i];
  delete[] A;
  delete[] dist;
  delete[] sptSet;
}
