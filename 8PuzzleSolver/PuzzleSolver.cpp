#include "PuzzleSolver.h"
#include "cstdlib"
#include "iostream"
#include "fstream"
#include "string"
#include "cstddef"
#include "cmath"
#include "vector"
#include "sstream"
#include "map"
using namespace std;

PuzzleSolver::PuzzleSolver()
{
}


PuzzleSolver::PuzzleSolver(std::string input)
{
	inputString = input;
	this->CreateInitialState();
	this->CreateGoalState();
	this->StartSolving();
}

PuzzleSolver::PuzzleSolver(int **)
{
}

PuzzleSolver::~PuzzleSolver()
{
}

bool PuzzleSolver::GenerateMove()
{
	int ** currentState = copyState();
	//find blank space
	std::vector<int> blankPos = findSpace(currentState);
	int row = blankPos.at(0);
	int col = blankPos.at(1);
	std::string POSITION;

	//Now find the expected moving blocks
	//Find corner, centre, edge
	if ((row == 0 && col == 0) || (row == 0 && col == 2) || (row == 2 && col == 0) || (row == 2 && col == 2))
	{
		POSITION = "CORNER";
	}
	else if (row == 1 && col == 1)
	{
		POSITION = "CENTRE";
	}
	else
	{
		POSITION = "EDGE";
	}
	//if position is at corner then 2 blocks
	if (POSITION == "CORNER")
	{
		if (row == 0)
		{
			switch (col)
			{
			case 0:
			{
				int ** state1 = swap(0, 0, 0, 1, currentState);//swap with 0,1 
				int h1 = MisplacedTiles(state1);
				nodesGenerated++;
				int ** state2 = swap(0, 0, 1, 0, currentState);//swap with 1,0
				int h2 = MisplacedTiles(state2);
				nodesGenerated++;
				this->moveTilesAtCorner(h1, h2, state1, state2);
				break;
			}
			case 2:
			{
				int ** state1 = swap(0, 2, 0, 1, currentState);//swap with 0,1 
				int h1 = MisplacedTiles(state1);
				nodesGenerated++;
				int ** state2 = swap(0, 2, 1, 2, currentState);//swap with 1,2
				int h2 = MisplacedTiles(state2);
				nodesGenerated++;
				this->moveTilesAtCorner(h1, h2, state1, state2);
				break;
			}
			default:
			{
				std::cout << "Default caes";
				break;
			}
			}
		}
		if (row == 2)
		{
			switch (col)
			{
			case 0:
			{
				int ** state1 = swap(2, 0, 1, 0, currentState);//swap with 1,0 
				int h1 = MisplacedTiles(state1);
				nodesGenerated++;
				int ** state2 = swap(2, 0, 2, 1, currentState);//swap with 2,1
				int h2 = MisplacedTiles(state2);
				nodesGenerated++;
				this->moveTilesAtCorner(h1, h2, state1, state2);
				break;
			}
			case 2:
			{
				int ** state1 = swap(2, 2, 2, 1, currentState);//swap with 2,1 
				int h1 = MisplacedTiles(state1);
				nodesGenerated++;
				int ** state2 = swap(2, 2, 1, 2, currentState);//swap with 1,2
				int h2 = MisplacedTiles(state2);
				nodesGenerated++;
				this->moveTilesAtCorner(h1, h2, state1, state2);
				break;
			}
			default:
			{
				std::cout << "Default caes";
				break;
			}
			}
		}
	}
	if (POSITION == "EDGE")
	{
		if (row == 0 && col == 1)
		{
			int ** state1 = swap(0, 1, 0, 0, currentState);//swap with 0,0 
			int h1 = MisplacedTiles(state1);
			nodesGenerated++;
			int ** state2 = swap(0, 1, 0, 2, currentState);//swap with 0,2
			int h2 = MisplacedTiles(state2);
			nodesGenerated++;
			int **state3 = swap(0, 1, 1, 1, currentState);//swap with 1,1
			int h3 = MisplacedTiles(state3);
			nodesGenerated++;
			this->moveTilesAtEdge(h1, h2, h3, state1, state2, state3);
		}
		else if (row == 1 && col == 0)
		{
			int ** state1 = swap(1, 0, 0, 0, currentState);//swap with 0,0 
			int h1 = MisplacedTiles(state1);
			nodesGenerated++;
			int ** state2 = swap(1, 0, 2, 0, currentState);//swap with 2,0
			int h2 = MisplacedTiles(state2);
			nodesGenerated++;
			int **state3 = swap(1, 0, 1, 1, currentState);//swap with 1,1
			int h3 = MisplacedTiles(state3);
			nodesGenerated++;
			this->moveTilesAtEdge(h1, h2, h3, state1, state2, state3);
		}
		else if(row == 1 && col == 2)
		{
			int ** state1 = swap(1, 2, 0, 2, currentState);//swap with 0,2 
			int h1 = MisplacedTiles(state1);
			nodesGenerated++;
			int ** state2 = swap(1, 2, 2, 2, currentState);//swap with 2,2
			int h2 = MisplacedTiles(state2);
			nodesGenerated++;
			int **state3 = swap(1, 2, 1, 1, currentState);//swap with 1,1
			int h3 = MisplacedTiles(state3);
			nodesGenerated++;
			this->moveTilesAtEdge(h1, h2, h3, state1, state2, state3);
		}
		else
		{
			int ** state1 = swap(2, 1, 2, 0, currentState);//swap with 2,0 
			int h1 = MisplacedTiles(state1);
			nodesGenerated++;
			int ** state2 = swap(2, 1, 2, 2, currentState);//swap with 2,2
			int h2 = MisplacedTiles(state2);
			nodesGenerated++;
			int **state3 = swap(2, 1, 1, 1, currentState);//swap with 1,1
			int h3 = MisplacedTiles(state3);
			nodesGenerated++;
			this->moveTilesAtEdge(h1, h2, h3, state1, state2, state3);
		}
	}
	if (POSITION == "CENTRE")
	{
		int ** state1 = swap(1, 1, 0, 1, currentState);//swap with 0,1 
		int h1 = MisplacedTiles(state1);
		nodesGenerated++;
		int ** state2 = swap(1, 1, 1, 0, currentState);//swap with 1,0
		int h2 = MisplacedTiles(state2);
		nodesGenerated++;
		int **state3 = swap(1, 1, 1, 2, currentState);//swap with 1,2
		int h3 = MisplacedTiles(state3);
		nodesGenerated++;
		int **state4 = swap(1, 1, 2, 1, currentState);//swap with 2,1
		int h4 = MisplacedTiles(state3);
		nodesGenerated++;
		this->moveTilesAtCentre(h1, h2, h3, h4, state1, state2, state3, state4);
	}
	if (isEqual())
	{
		std::cout << "Game completed." << endl;
		//print no.of moves
		DisplayFunction();
		
		return true;
	}
	else
	{
		return false;
	}

	//if position is middle of edge then 3 blocks

	//if position is in centre then 4 blocks
}

int PuzzleSolver::MisplacedTiles()
{
	int misplacesTiles = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (m_InitialState[i][j] != m_GoalState[i][j])
			{
				misplacesTiles++;
			}
		}
			
	}
		
	return misplacesTiles - 1;
}

int PuzzleSolver::MisplacedTiles(int **currentState)
{
	int misplacesTiles = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (currentState[i][j] != m_GoalState[i][j])
			{
				misplacesTiles++;
			}
		}
			
	}
		
	return misplacesTiles - 1;
		
}

void PuzzleSolver::StartSolving()
{
	//Check if first state is goal state
	if (isEqual())
	{
		//terminate the program
		DisplayFunction();
		exit(0);
	}
	else
	{
		//Check Heuristic 
		//Number of misplaced tiles
		int h2 = MisplacedTiles();
		m_PHeuristic.push_back(h2);
		//int i = 0;
		while (!GenerateMove())
		{
			std::cout << "Game Solving" << endl;
		}
		exit(0);

	}
}

int ** PuzzleSolver::copyState()
{
	//int newState[3][3];
	int **newState = (int **)malloc(3 * sizeof(int *));
	// for each row allocate Cols ints
	for (int row = 0; row < 3; row++) {
		newState[row] = (int *)malloc(3 * sizeof(int));
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			newState[i][j] = m_InitialState[i][j];
		}
	}
	return newState;
}

std::vector<int>  PuzzleSolver::findSpace(int **currentState)
{
	std::vector<int> posVec ;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (currentState[i][j] == 0)
			{
				posVec.push_back(i);// first element is row number
				posVec.push_back(j);//second element is column number
			}
		}
	}
	return posVec;
}

void PuzzleSolver::modifyInitialState(int **newState)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			 m_InitialState[i][j] = newState[i][j] ;
		}
	}
	
}

bool PuzzleSolver::isEqual()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (m_InitialState[i][j] != m_GoalState[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

int ** PuzzleSolver::swap(int rval1, int cval1, int rval2, int cval2, int **currentState)
{
	//int **newState = 0;
	int **newState = (int **)malloc(3 * sizeof(int *));
	// for each row allocate Cols ints
	for (int row = 0; row < 3; row++) {
		newState[row] = (int *)malloc(3 * sizeof(int));
	}
	//newState = currentState;

	

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			newState[i][j] = currentState[i][j];
		}
	}
	int valToSwap = newState[rval1][cval1];
	std::swap(newState[rval1][cval1], newState[rval2][cval2]);
	return newState;
}

bool PuzzleSolver::StateSpace(int **newState, int hval)
{
	std::string stateSpace;
	std::stringstream ss;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			ss << newState[i][j];
		}
	}
	string str = ss.str();
	stateSpace.append(str);
	/*if (m_PHeuristic.size() > 4)
	{
		int h3 = m_PHeuristic.at(m_PHeuristic.size() - 1);
		int h2 = m_PHeuristic.at(m_PHeuristic.size() - 2);
		int h1 = m_PHeuristic.at(m_PHeuristic.size() - 3);
		std::cout << "H3 H2 H1 :::: " << h3 << "\t" << h2 << "\t" << h1 << endl;
		if ((h2 > h1 && h3 > h2) || (h1 == h2 && h3 > h2) || (h2 > h1 && h2 == h3))
		{
			std::cout << "HEURISTIC IS INCREASING";
			return false;
		}
	}*/
	bool isNewState = false;
	for (std::vector<std::string>::iterator iter = m_PNodeList.begin(); iter != m_PNodeList.end(); iter++)
	{
		if (*iter == stateSpace)
		{
			std::cout << "State already visited";
			return false;
		}
		else
		{
			isNewState = true;
			
			
		}
	}
	if (isNewState)
	{
		m_PNodeList.push_back(stateSpace);
		m_PHeuristic.push_back(hval);
	}
	return true;
}

void PuzzleSolver::DisplayFunction()
{
	std::cout << "REPORT:" << endl;
	//calculate mean heuristic value
	int hvalue = 0;
	for (std::vector<int>::iterator iter = m_PHeuristic.begin(); iter != m_PHeuristic.end(); iter++)
	{
		hvalue = hvalue + *iter;
	}
	hvalue = hvalue / (m_PHeuristic.size());
	std::cout << "The heuristic function: " << hvalue << endl;
	nodesExpanded = m_PNodeList.size() - 1;
	//Calculate gcost
	int gcost = nodesExpanded;
	std::cout << "g(cost): " << nodesExpanded << endl;
	std::cout << "Number of Nodes Expanded: " << nodesExpanded << endl;
	std::cout << "Number of Nodes Generated: " << nodesGenerated << endl;
	std::cout << "The state space representation:" << endl;
	for (std::vector<std::string>::iterator iter = m_PNodeList.begin(); iter != m_PNodeList.end(); iter++) 
	{
		std::cout << (*iter) << endl;
	}
	
	
}

void PuzzleSolver::moveTilesAtCorner(int h1, int h2, int **state1, int **state2)
{
	bool isStateExpanded = false;
	if (h1 < h2)
	{
		if (StateSpace(state1, h1))
		{
			modifyInitialState(state1);
		}
		else
		{
			isStateExpanded = true;
			StateSpace(state2, h2);
			modifyInitialState(state2);
		}
				
	}
	else if (h1 > h2)
	{
		if (StateSpace(state2, h2))
		{
			modifyInitialState(state2);
		}
		else
		{
			isStateExpanded = true;
			StateSpace(state1, h1);
			modifyInitialState(state1);
		}
	}
	else
	{
		modifyInitialState(state1);
		StateSpace(state1, h1);
	}
	if (state1 != NULL)
	{
		delete state1;
		state1 = NULL;
	}
	if (state2 != NULL)
	{
		delete state2;
		state2 = NULL;
	}
}

void PuzzleSolver::moveTilesAtEdge(int h1, int h2, int h3, int **state1, int **state2, int **state3)
{
	int n, c, d, swap;
	bool isStateExpanded = false;
	//Sort all heuristic in increasing order
	int arr[3] = { h1, h2, h3 };
	for (int c = 0; c < (3 - 1); c++)
	{
		for (int d = 0; d < 3 - c - 1; d++)
		{
			if (arr[d] > arr[d + 1]) /* For decreasing order use < */
			{
				swap = arr[d];
				arr[d] = arr[d + 1];
				arr[d + 1] = swap;
			}
		}
	}
	std::vector<int **> hstateVec;
	std::vector<int> hvalVec;
	for (c = 0; c < 3; c++)
	{
		if (arr[c] == h1)
		{
			hstateVec.push_back(state1);
			hvalVec.push_back(h1);
		}
		else if (arr[c] == h2)
		{
			hstateVec.push_back(state2);
			hvalVec.push_back(h2);
		}
		else
		{
			hstateVec.push_back(state3);
			hvalVec.push_back(h3);
		}
	}
	if (StateSpace(hstateVec.at(0), hvalVec.at(0)))
	{
		modifyInitialState(hstateVec.at(0));
	}
	else
	{
		if (StateSpace(hstateVec.at(1), hvalVec.at(1)))
		{
			modifyInitialState(hstateVec.at(1));
		}
		else
		{
			StateSpace(hstateVec.at(2), hvalVec.at(2));
			modifyInitialState(hstateVec.at(2));
		}
		
	}
	if (state1 != NULL)
	{
		delete state1;
		state1 = NULL;
	}
	if (state2 != NULL)
	{
		delete state2;
		state2 = NULL;
	}
	if (state3 != NULL)
	{
		delete state3;
		state3 = NULL;
	}

}

void PuzzleSolver::moveTilesAtCentre(int h1, int h2, int h3, int h4, int **state1, int **state2, int **state3, int **state4)
{
	int  swap;
	bool isStateExpanded = false;
	//Sort all heuristic in increasing order
	int arr[4] = { h1, h2, h3, h4 };
	for (int c = 0; c < (4 - 1); c++)
	{
		for (int d = 0; d < 4 - c - 1; d++)
		{
			if (arr[d] > arr[d + 1]) /* For decreasing order use < */
			{
				swap = arr[d];
				arr[d] = arr[d + 1];
				arr[d + 1] = swap;
			}
		}
	}
	std::vector<int **> hstateVec;
	std::vector<int> hvalVec;
	for (int c = 0; c < 4; c++)
	{
		if (arr[c] == h1)
		{
			hstateVec.push_back(state1);
			hvalVec.push_back(h1);
		}
		else if (arr[c] == h2)
		{
			hstateVec.push_back(state2);
			hvalVec.push_back(h2);
		}
		else if(arr[c] == h3)
		{
			hstateVec.push_back(state3);
			hvalVec.push_back(h3);
		}
		else
		{
			hstateVec.push_back(state4);
			hvalVec.push_back(h4);
		}
	}
	if (StateSpace(hstateVec.at(0), hvalVec.at(0)))
	{
		modifyInitialState(hstateVec.at(0));
	}
	else
	{
		if (StateSpace(hstateVec.at(1), hvalVec.at(1)))
		{
			modifyInitialState(hstateVec.at(1));
		}
		else
		{
			if (StateSpace(hstateVec.at(2), hvalVec.at(2)))
			{
				modifyInitialState(hstateVec.at(2));
			}
			else
			{
				StateSpace(hstateVec.at(3), hvalVec.at(3));
				modifyInitialState(hstateVec.at(3));
			}
		}

	}
	if (state1 != NULL)
	{
		delete state1;
		state1 = NULL;
	}
	if (state2 != NULL)
	{
		delete state2;
		state2 = NULL;
	}
	if (state3 != NULL)
	{
		delete state3;
		state3 = NULL;
	}
	if (state4 != NULL)
	{
		delete state4;
		state4 = NULL;
	}
}

void PuzzleSolver::CreateInitialState()
{
	std::string subString = inputString.substr(0, inputString.find_first_of(" "));
	std::cout << "Initial State : " <<subString << endl;
	int pos = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			m_InitialState[i][j] = subString.at(pos) - 48;
			pos++;
		}
	}
	std::string stateSpace;
	std::stringstream ss;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::stringstream ss;
			ss << m_InitialState[i][j];
			std::string str = ss.str();
			stateSpace.append(str);
		}
	}
	m_PNodeList.push_back(stateSpace);
	
}

void PuzzleSolver::CreateGoalState()
{
	int m_size = std::distance(inputString.begin(), inputString.end());
	std::string subString = inputString.substr(inputString.find_first_of(" ") + 1, m_size);
	std::cout <<"Goal State: " << subString << endl;
	int pos = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			m_GoalState[i][j] = subString.at(pos) - 48;
			pos++;
		}
	}
}

