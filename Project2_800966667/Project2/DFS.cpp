#include "DFS.h"

DFS::DFS(int Vertices, int edges)
{
    noOfVertices = Vertices;
    m_Plist = new list<int>[edges];
}

DFS::~DFS()
{
    if(m_Plist->size() > 0)
    {
        delete m_Plist;
    }
    
}
 
void DFS::addEdge(int u, int v)
{
    m_Plist[u].push_back(v);
}
 
bool DFS::isGraphCyclic(int vertex, bool verticesVisited[], bool *recursionStack)
{
    if(verticesVisited[vertex] == false)
    {
        verticesVisited[vertex] = true;
        recursionStack[vertex] = true;
        if(m_Plist[vertex].size() > 1 && m_Plist[vertex].size() <= noOfVertices)
        {
            for(list<int>::iterator iter = m_Plist[vertex].begin(); iter != m_Plist[vertex].end(); ++iter)
            {
//                if(*iter <= noOfVertices)
                {
                    if ( !verticesVisited[*iter] && isGraphCyclic(*iter, verticesVisited, recursionStack) )
                    {
                        return true;
                    }
                    else if (recursionStack[*iter])
                    {
                        return true;
                    }
                }
            }
        }
    }
    recursionStack[vertex] = false;  
    return false;
}
 
bool DFS::checkifCyclic()
{
    bool *visitedVertices = new bool[noOfVertices + 1];
    bool *recursionStack = new bool[noOfVertices + 1];
    for(int i = 0; i < noOfVertices; i++)
    {
        visitedVertices[i] = false;
        recursionStack[i] = false;
    }
 
    for(int i = 0; i < noOfVertices; i++)
    {
        if (isGraphCyclic(i, visitedVertices, recursionStack))
        {
            
            return true;
        }
    }
    cout << "\nTopological order is: " << endl;
    topologicalSort();
    return false;
}

void DFS::topologicalSort()
{
    stack<int> recursionStack;
    bool *visitedVertices = new bool[noOfVertices];
    for (int i = 0; i < noOfVertices; i++)
    {
        visitedVertices[i] = false;
    }
    for (int i = 1; i <= noOfVertices; i++)
    {
        if (visitedVertices[i] == false)
        {
            this->performTopologicalSort(i, visitedVertices, recursionStack);
        }
    }
    while (recursionStack.empty() == false)
    {
        cout << recursionStack.top() << "\t";
        recursionStack.pop();
    }
}
void DFS::performTopologicalSort(int vertex, bool visitedVertices[], stack<int>& recursionStack)
{
    visitedVertices[vertex] = true;
    if(m_Plist[vertex].size() > 1 && m_Plist[vertex].size() < noOfVertices)
    {
        for (list<int>::iterator iter = m_Plist[vertex].begin(); iter != m_Plist[vertex].end(); ++iter)
        {
            if (!visitedVertices[*iter])
            {
                performTopologicalSort(*iter, visitedVertices, recursionStack);
            }
        }
    }
    recursionStack.push(vertex);
}




