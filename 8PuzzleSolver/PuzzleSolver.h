#include "cstdlib"
#include "vector"
class PuzzleSolver
{
public:
	PuzzleSolver();
	PuzzleSolver(std::string);
	PuzzleSolver(int **);
	~PuzzleSolver();

	/*!
	* Function to generates the moves for bsocks
	*/
	bool GenerateMove();

	/*!
	* Checks the number of misplaced tiles in initial state
	*/
	int MisplacedTiles();

	/*!
	* Checks the number of misplaced tiles in current state
	\param<int **> array of current state
	*/
	int MisplacedTiles(int **);

	/*!
	* Starts the solution finding
	*/
	void StartSolving();

	/*!
	* Copies the initial state to new object
	*/
	int **copyState();

	/*!
	* Finds space in the array
	\ param<int **> array of current state
	*/
	std::vector<int>  findSpace(int **);

	/*!
	* Modifies initial state
	\ param <int **> array of current state
	*/
	void modifyInitialState(int **);

	/*!
	* Checks if current state is equal to goal state
	*/
	bool isEqual();

	/*!
	* Swaps numbers from given current state and location
	\ param <int> row and column number
	\ param <int **> array of current state
	*/
	int ** swap(int, int, int, int, int **);

	/*!
	* Generates State space
	*/
	bool StateSpace(int **, int );

	/*!
	* Displays the final report
	*/
	void DisplayFunction();

	/*!
	* Moves tiles if the blank space is at corner
	\ param <int> heuristic value
	\ param <int **> nodes generated
	*/
	void moveTilesAtCorner(int, int, int **, int **);

	/*!
	* Moves tiles if the blank space is at edge
	\ param <int> heuristic value
	\ param <int **> nodes generated
	*/
	void moveTilesAtEdge(int, int, int,int **, int **, int **);

	/*!
	* Moves tiles if the blank space is at centre
	\ param <int> heuristic value
	\ param <int **> nodes generated
	*/
	void moveTilesAtCentre(int, int, int, int, int **, int **, int **, int **);

	/*!
	* Creates initial state
	*/
	void CreateInitialState();

	/*!
	* Creates goal state
	*/
	void CreateGoalState();
private:
	/*!
	* List of nodes expanded
	*/
	std::vector<std::string> m_PNodeList;

	/*!
	* Input from user
	*/
	std::string inputString;

	/*!
	* Creates initial state and goal state
	*/
	int m_InitialState[3][3], m_GoalState[3][3];

	/*!
	* List of Heuristic values at nodes expanded
	*/
	std::vector<int> m_PHeuristic;

	/*!
	* Nodes generated and expanded
	*/
	int nodesGenerated, nodesExpanded;
};

