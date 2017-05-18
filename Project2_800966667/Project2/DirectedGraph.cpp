#include "DirectedGraph.h"
#include <iostream>
#include <fstream>

#include <iostream>
#include <fstream>
#include <memory>
#include "DirectedGraph.h"

DirectedGraph::DirectedGraph() 
{
    noOfVertices = 0;
    noOfEdges = 0;
    getGraphData();
    if(noOfEdges > 1 && noOfVertices > 1)
    {
        m_DFS = new DFS(noOfVertices,noOfEdges);
        constructGraph();
        detectCycle();
        DijikStrasAlgorithm();
    }
}

DirectedGraph::~DirectedGraph() 
{
    if(m_DFS != NULL)
    {
        delete m_DFS;
        m_DFS = NULL;
    }
    delete[] adjacencyMatrix;
}

void DirectedGraph::getGraphData()
{
    int inputVertices, inputEdges;
    string directedEdge = "";
    string token;
    cout << "Enter the total number of vertices:" << endl;
    cin >> inputVertices;
    noOfVertices = inputVertices;
    cout << "Enter the total number of edges:" << endl;
    cin >> inputEdges;
    noOfEdges = inputEdges;
    if(noOfEdges > 1 && noOfVertices > 1)
    {
        cout << "Enter the directed edges in the form of <u v w>: " << endl;
        int rowU, colV, weight;
        int edge[3];
        int i = 0;
        for(int i =0; i < noOfVertices ; i++)
        {
            for(int j = 0; j < noOfVertices; j++)
            {
                adjacencyMatrix[i][j] = 0;
            }
        }
        while(inputEdges)
        {
            i = 0;
            if(!directedEdge.empty())
            {
                directedEdge.clear();
            }
            cin >> directedEdge;
            if(directedEdge.find(",") == 0)
            {
                cout << "Please enter edges in correct format." << endl;
                cin >> directedEdge;
            }
            
            stringstream inputStream(directedEdge);


            while(std::getline(inputStream, token, ',')) 
            {
                edge[i] = std::atoi(token.c_str());
                i++;
            }
            rowU = edge[0];
            colV = edge[1];
            weight = edge[2];
            adjacencyMatrix[rowU-1][colV-1] = weight;
            inputEdges--;
        }
        int count = 0;
        
        cout << "The adjacency matrix for the given graph is: "<< endl;
        for(int i =0; i < noOfVertices ; i++)
        {
            for(int j = 0; j < noOfVertices ; j++)
            {
                if(count < noOfVertices)
                {
                    cout << adjacencyMatrix[i][j];
                    count++;
                }
                else
                {
                    count = 1;
                    cout << endl;
                    cout << adjacencyMatrix[i][j];
                }
            }
        }
    }
           
}
void DirectedGraph::constructGraph()
{
    for(int i =0; i < noOfVertices ; i++)
    {
        for(int j = 0; j < noOfVertices ; j++)
        {
            if(adjacencyMatrix[i][j] >= 1)
            {
                m_DFS->addEdge(i+1, j+1);
            }
        }
    }
}
void DirectedGraph::detectCycle()
{
    if(m_DFS->checkifCyclic())
    {
        cout << "\nGraph is cyclic." << endl;
    }
    else
    {
        cout << "\nGraph is not cyclic." << endl;
    }
}
void DirectedGraph::createDistanceMatrix()
{
    for (int i = 0; i < noOfVertices; i++)
    {
        for (int j = 0; j < noOfVertices; j++)
        {
            distanceMatrix[i][j] = adjacencyMatrix[i][j];
            if(distanceMatrix[i][j] == 0)
            {
                if(i == j)
                {
                    distanceMatrix[i][j] = 0;
                }
                else
                {
                    distanceMatrix[i][j] = Infinity;
                }
            }
        }
    }
    
}

void DirectedGraph::primsAlgorithm()
{
    int selected[noOfVertices], ne; 
    int False =0;
    int True =1;
    int minimum,x,y;
    int adjMatrix[noOfVertices][noOfVertices];
    for (int i = 0; i < noOfVertices; i++)
    {
        for (int j = 0; j < noOfVertices; j++)
        {
            adjMatrix[i][j] = 0;
        }
    }

    for(int i=0;i<noOfVertices;i++)
       selected[i]=false;

    selected[0]=true;
    ne=0;

    while(ne < noOfVertices-1)
    {
       minimum=Infinity;

       for(int i=0;i<noOfVertices;i++)
       {
          if(selected[i]==1)
          {
            for(int j=0;j<noOfVertices;j++)
            {
               if(selected[j]==0)
               {
                  if(minimum > distanceMatrix[i][j])
                  {
                       minimum = distanceMatrix[i][j];
                       x =i;
                       y=j;
                  }
               }
            }
          }
       }
       selected[y]=1;
       cout<<"\n"<<x+1<<" --> "<<y+1;
       adjMatrix[x][y] = adjacencyMatrix[x][y];
       ne=ne+1;
    }
    int count = 0;
    cout << "\nThe adjacency matrix for the Minimum spanning tree is: "<< endl;
    for(int i =0; i < noOfVertices ; i++)
    {
        for(int j = 0; j < noOfVertices ; j++)
        {
            if(count < noOfVertices)
            {
                cout << adjMatrix[i][j];
                count++;
            }
            else
            {
                count = 1;
                cout << endl;
                cout << adjMatrix[i][j];
            }
        }
    }
}

int DirectedGraph::minimumDistance(int distance[], bool shortestPath[])
{
   int min = INT_MAX, min_index;
  
   for (int v = 0; v < noOfVertices; v++)
   {
     if (shortestPath[v] == false && distance[v] <= min)
     {
         min = distance[v];
         min_index = v;
     }
   }
  
   return min_index;
}

void DirectedGraph::DijikStrasAlgorithm()
{
    int distance[noOfVertices], parentNodes[noOfVertices];      
    bool shortestPath[noOfVertices]; 
    int source = 0;
    for(int i =0; i < noOfVertices ; i++)
    {
        for(int j = 0; j < noOfVertices; j++)
        {
            shortPathAdjMatrix[i][j] = 0;
        }
    }
    for (int i = 0; i < noOfVertices; i++)
    {
       distance[i] = Infinity;
       shortestPath[i] = false;
       parentNodes[0] = -1;
    }
    distance[source] = 0;
    for (int count = 0; count < noOfVertices-1; count++)
    {
      int u = minimumDistance(distance, shortestPath);
      shortestPath[u] = true;
      for (int v = 0; v < noOfVertices; v++)

          
        if (!shortestPath[v] && adjacencyMatrix[u][v] && distance[u] != Infinity && distance[u] + adjacencyMatrix[u][v] < distance[v])
        {
            parentNodes[v]  = u;
            distance[v] = distance[u] + adjacencyMatrix[u][v];
        }
    }
    cout << "Vertex" << "\tDistance from Source Vertex 1" << endl ;
    for (int i = 0; i < noOfVertices; i++)
        cout << " "<< i+1 << "\t\t" << distance[i] << endl;

    for(int a = 0; a < noOfVertices; a++)
    {
        int start = parentNodes[a];
        int end = a;
        shortPathAdjMatrix[start][end] = adjacencyMatrix[start][end];
    }
    int count = 0;
    cout << "\nThe adjacency matrix for the Shortest Path Tree is: "<< endl;
    for(int i =0; i < noOfVertices ; i++)
    {
        for(int j = 0; j < noOfVertices ; j++)
        {
            
            if(count < noOfVertices)
            {
                cout << shortPathAdjMatrix[i][j];
                count++;
            }
            else
            {
                count = 1;
                cout << endl;
                cout << shortPathAdjMatrix[i][j];
            }
        }
    }
    
}






