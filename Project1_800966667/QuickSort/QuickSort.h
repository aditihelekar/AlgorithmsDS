#pragma once
#include <string>
#include <ctime>
#include <time.h>

#define _CRT_SECURE_NO_WARNINGS true
#define MAX_SIZE 100000
#define CUTOFF 10
class QuickSort
{
public:
	QuickSort();
	QuickSort(std::string);
	~QuickSort();
	int Partition(int *, int, int, bool , bool, int);
        int RandomizedPartition(int *, int, int, bool);
	void QuickSORTMEDIAN(int *, int, int );
        void QuickSORTMedianwithInsertion(int *, int, int );
        void QuickSORTRANDOMPIVOT(int *, int, int );
        void QuickSORTRandomPivotwithInsertion(int *, int, int );
	void ReadInput(std::string);
	void InsertionSORT(int, int, bool);
	int medianOfThree(int, int , bool);
        void Insertion(int, int);

	//Variables
	int inputM[MAX_SIZE], inputB[MAX_SIZE], inputMI[MAX_SIZE], inputRI[MAX_SIZE];
	int lastElementPos;
	int median, numberofKeyComparisonsMedian, numberofKeyComparisonsRandom, MEDIANCUTOFF, noofkeyCompMedInsert, noofkeyCompRadomInsert;
};

