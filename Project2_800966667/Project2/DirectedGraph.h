#ifndef DIRECTEDGRAPH_H
#define DIRECTEDGRAPH_H

#include <cstdlib>
#include <sstream>
#include <string>
#include "DFS.h"

#define Infinity 1000

using namespace std;

class DirectedGraph {
public:
    DirectedGraph();
    virtual ~DirectedGraph();
    //Gets the data of graph from user
    void getGraphData();
    //constructs Graph using the data
    void constructGraph();
    //Detects if there is any cycle in the graph 
    void detectCycle();
    //Creates distance matrix for shortest path algorithm
    void createDistanceMatrix();
    
    int minimumDistance(int [], bool []);
    
    void DijikStrasAlgorithm();
    
    void primsAlgorithm();
    
    void printPath(int parent[], int j);
    
private:
    // Number of vertices and edges in the graph
    int noOfVertices, noOfEdges;
    //2d array of adjacency matrix and distance matrix
    int adjacencyMatrix[35][35], distanceMatrix[35][35], shortPathAdjMatrix[35][35];
    DFS *m_DFS;
};

#endif /* DIRECTEDGRAPH_H */

