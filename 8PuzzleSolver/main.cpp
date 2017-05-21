#include "cstdlib"
#include "iostream"
#include "fstream"
#include "string"
#include "cstddef"
#include "PuzzleSolver.h"
using namespace std;

std::string ReadInput() {
	std::string STRING, inputFilePath;
	std::ifstream inputfile;
	std::cout << "Enter file name: ";
	std::cin >> inputFilePath;
	inputfile.open(inputFilePath);
	if (!inputfile)
	{
		std::cout << "Unable to open file";
	}
	else
	{
		if (!inputfile.eof()) // To get you all the lines.
		{
			getline(inputfile, STRING); // Saves the line in STRING.
		}

		inputfile.close();
	
	}
	return STRING;
}

void main(void)
{
	std::string Input=ReadInput();
	PuzzleSolver *m_PSolver = new PuzzleSolver(Input);
}