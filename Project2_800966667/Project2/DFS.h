#ifndef DFS_H
#define DFS_H

#include<iostream>
#include <list>
#include <limits.h>
#include <vector>
#include <stack>

using namespace std;

class DFS {
//Performs depth first search using Adjacency list technique   
    
public:
    DFS(int , int);   
    virtual ~DFS();
    //Describes each directed edge in the form of adjacency list
    void addEdge(int , int );
    //Checks if graph is cyclic
    bool checkifCyclic();    
    //Recursively called function to check cycle in graph
    bool isGraphCyclic(int , bool *, bool *);
    //Topological sort
    void topologicalSort();
    //Implements topological sort and recursively called
    void performTopologicalSort(int , bool *, stack<int> &);
    
private:
    //Number of vertices
    int noOfVertices;  
    //Adjacency list pointer
    list<int> *m_Plist;  

};

#endif /* DFS_H */

