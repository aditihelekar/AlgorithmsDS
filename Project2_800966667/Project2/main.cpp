#include <cstdlib>
#include "DirectedGraph.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
DirectedGraph *m_DirectedGraph = new DirectedGraph();
    
    if(m_DirectedGraph != NULL)
    {
        delete m_DirectedGraph;
        m_DirectedGraph = NULL;
    }
    return 0;
}

