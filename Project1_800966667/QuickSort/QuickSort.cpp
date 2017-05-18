#include "QuickSort.h"
#include "cstdlib"
#include "iostream"
#include "fstream"
#include "string"
#include "cstddef"
#include "cmath"
#include "vector"
#include "sstream"
#include "ctime"

using namespace std;

QuickSort::QuickSort()
{
}

QuickSort::QuickSort(std::string inputString)
{
	if (!inputString.empty())
	{
		numberofKeyComparisonsMedian = 0;
                numberofKeyComparisonsRandom = 0;
                noofkeyCompMedInsert = 0;
                noofkeyCompRadomInsert = 0;
		this->ReadInput(inputString);
		std::cout << "Total number of elements in input sequence: " << lastElementPos + 1 << endl;
		MEDIANCUTOFF = ((lastElementPos + 1) * 3) / 4;
                
                QuickSORTMEDIAN(inputM, 0, lastElementPos);
                QuickSORTRANDOMPIVOT(inputB, 0, lastElementPos);
                QuickSORTMedianwithInsertion(inputMI,0, lastElementPos);
                QuickSORTRandomPivotwithInsertion(inputRI, 0, lastElementPos);
                
                
		std::ofstream outputfile;
		std::__cxx11::string outputilepath ;
                outputilepath.append("SortedList.txt");
		outputfile.open(outputilepath.c_str());
                
                outputfile << "Randomized Pivot Element Sorted List: ";
                for (int i = 0; i <= lastElementPos; i++)
		{
			outputfile << inputB[i] << ",";
		}
                outputfile << "\nMedian Sorted List: ";
		for (int i = 0; i <= lastElementPos; i++)
		{
			outputfile << inputB[i] << ",";
		}
                outputfile << "\nRandomized Pivot Element Sorted with Insertion Sort List : ";
                for (int i = 0; i <= lastElementPos; i++)
		{
			outputfile << inputRI[i] << ",";
		}
                outputfile << "\nMedian Sorted with Insertion Sort List: ";
		for (int i = 0; i <= lastElementPos; i++)
		{
			outputfile << inputMI[i] << ",";
		}
                
                
		std::cout << "Number of key Comparisons using Median: " << numberofKeyComparisonsMedian << endl;
                std::cout << "Number of key Comparisons using Randomized Pivot Element: " << numberofKeyComparisonsRandom << endl;
                std::cout << "Number of key Comparisons using Median with Insertion Sort: " << noofkeyCompMedInsert << endl;
                std::cout << "Number of key Comparisons using Randomized Pivot Element with Insertion Sort: " << noofkeyCompRadomInsert << endl;
		outputfile.close();
		exit(0);
	}
}


QuickSort::~QuickSort()
{
}

int QuickSort::RandomizedPartition(int*A, int p , int r, bool useInsertion) {
    int i=p+rand()%(r-p+1);
//    std::cout << __FILE__<<__FUNCTION__<< i << endl;
    int temp;
    temp=A[r];
    A[r]=A[i];
    A[i]=temp;
    return Partition(A,p,r, false, useInsertion, 0);

}


int QuickSort::Partition(int *A, int p, int r, bool useMedian, bool useInsertion, int median)
{
	if (!useMedian)
	{
//            std::cout << __LINE__<<__FUNCTION__<< endl;
		int x = A[r];
		int i = p - 1;
		for (int j = p; j <= r - 1; j++)
		{
//                    std::cout << __LINE__<<__FUNCTION__<< endl;
			if (A[j] <= x)
			{
//                            std::cout << __LINE__<<__FUNCTION__<< endl;
				i++;
				std::swap(A[i], A[j]);
                                if(useInsertion){
                                    noofkeyCompRadomInsert++;
                                }
                                else{
                                    numberofKeyComparisonsRandom++;
                                }
				
			}

		}
		std::swap(A[i + 1], A[r]);
		return i + 1;
	}
	else
	{
		//Partitiong logic with median of 3 pivot
		int i = p;
		int j = r - 1;
                if(useInsertion){
                    while(1)
                    {
                            //Finding the value of i for inputM[i] > median
                            while(median > inputMI[++i])
                            {
                                    noofkeyCompMedInsert++;
                            }
                            //Finding the value of j for inputM[j] < median
                            while(median < inputMI[--j])
                            { 
                                    noofkeyCompMedInsert++;
                            }
                            if (i < j)
                            {
                                    noofkeyCompMedInsert++;
                                    std::swap(inputMI[i], inputMI[j]);
                            }
                            else
                            {
                                    noofkeyCompMedInsert++;
                                    break;
                            }

                    }
                    std::swap(inputMI[i], inputMI[r - 1]);
                    return i;
                }
                else{
                    while(1)
		{
//                        std::cout << __LINE__<<__FUNCTION__<< endl;
			//Finding the value of i for inputM[i] > median
			while(median > inputM[++i])
			{
//				numberofKeyComparisonsMedian++;
			}
			//Finding the value of j for inputM[j] < median
			while(median < inputM[--j])
			{ 
//				numberofKeyComparisonsMedian++;
			}
			if (i < j)
			{
				numberofKeyComparisonsMedian++;
				std::swap(inputM[i], inputM[j]);
			}
			else
			{
				numberofKeyComparisonsMedian++;
				break;
			}
			
		}
//                    std::cout << __LINE__<<__FUNCTION__<< i << endl;
		std::swap(inputM[i], inputM[r - 1]);
		return i;
                }
	}
}

void QuickSort::QuickSORTMEDIAN(int *A, int p, int r)
{
//    std::cout << __LINE__<<__FUNCTION__<< endl;
    if(p < r && p <= lastElementPos && r <= lastElementPos){
        int median = medianOfThree(p, r, false);
        int q = Partition(A, p, r, true, false, median);
        QuickSORTMEDIAN(A, p, q - 1);
        QuickSORTMEDIAN(A, q + 1, r);
    }
    else
    {
//            std::cout << __LINE__<<__FUNCTION__<< endl;
            Insertion(p,r);
    }
}


void QuickSort::QuickSORTMedianwithInsertion(int*A, int p, int r) {

    //    std::cout << __LINE__<<__FUNCTION__<< endl;
	if(r - p + 1 > CUTOFF)
	{ 
//            std::cout << __LINE__<<__FUNCTION__<< endl;
		int median = medianOfThree(p, r, true);
		int q = Partition(A, p, r, true, true, median);
		QuickSORTMEDIAN(A, p, q - 1);
		QuickSORTMEDIAN(A, q + 1, r);
	}
	else
	{
//            std::cout << __LINE__<<__FUNCTION__<< endl;
		InsertionSORT(p,r,true);
	}
}



void QuickSort::QuickSORTRANDOMPIVOT(int*A, int p, int r) {

//    std::cout << __LINE__<<__FUNCTION__<< p << " " << r << endl;
    if(p < r){
        int q = RandomizedPartition(A, p, r, false);
        QuickSORTRANDOMPIVOT(A, p, q - 1);
        QuickSORTRANDOMPIVOT(A, q + 1, r);
    }
}

void QuickSort::QuickSORTRandomPivotwithInsertion(int* A, int p, int r) {
//    std::cout << __LINE__<<__FUNCTION__<< endl;
    if (r - p + 1 > CUTOFF)
    {
//        std::cout << __LINE__<<__FUNCTION__<< endl;
            int q = RandomizedPartition(A, p, r, true);
            QuickSORTRANDOMPIVOT(A, p, q - 1);
            QuickSORTRANDOMPIVOT(A, q + 1, r);
    }
    else
    {
//        std::cout << __LINE__<<__FUNCTION__<< endl;
            InsertionSORT(p,r,false);
    }
}



void QuickSort::ReadInput(std::string inputString)
{
	std::stringstream ss(inputString);
	//std::cout << "Input Sequence : " << inputString << endl;
	std::vector<int> inputVec;
	int pos;
	while (ss.good())
	{
		string substr;
		getline(ss, substr, ',');
		//std::cout << "Comma separated : " << substr << endl;
		inputVec.push_back(std::atoi(substr.c_str()));
	}
	for (std::vector<int>::iterator iter = inputVec.begin(); iter != inputVec.end(); iter++)
	{
		pos = std::distance(inputVec.begin(), iter);
		inputM[pos] = inputVec.at(pos);
                inputB[pos] = inputVec.at(pos);
                inputMI[pos] = inputVec.at(pos);
                inputRI[pos] = inputVec.at(pos);
		//std::cout << inputM[pos] << "\t" << "pos:::" << pos << endl;
	}
        
	lastElementPos = pos;
}

void QuickSort::Insertion(int first, int last){
    int key = 0;
    int i = 0;

    for (int j = 1; j <= last; j++)
    {
            key = inputM[j];
            i = j - 1;
            while (inputM[i] > key && i >= first)
            {
                    inputM[i + 1] = inputM[i];
                    i--;
                    numberofKeyComparisonsMedian++;
            }
            inputM[i + 1] = key;
    }
}

void QuickSort::InsertionSORT(int first, int last, bool isMedian)
{
	int key = 0;
        int i = 0;
        if(isMedian){
            
            for (int j = 1; j <= last; j++)
            {
                    key = inputMI[j];
                    i = j - 1;
                    while (inputMI[i] > key && i >= first)
                    {
                            inputMI[i + 1] = inputMI[i];
                            i--;
                            noofkeyCompMedInsert++;
                    }
                    inputMI[i + 1] = key;
            }
        }
        else{
            
            for (int j = 1; j <= last; j++)
            {
                    key = inputRI[j];
                    i = j - 1;
                    while (inputRI[i] > key)
                    {
                            inputRI[i + 1] = inputRI[i];
                            i--;
                            noofkeyCompRadomInsert++;
                    }
                    inputRI[i + 1] = key;
            }
        }
	
}

int QuickSort::medianOfThree(int first, int last, bool useInsertion)
{
	int middle = (first + last) / 2;
//	std::cout << __LINE__ << "\t" << __FUNCTION__<< " middle:: " << middle <<" "<< first <<" " << last << endl;
	//Arrange the elements in ascending order and find middle element as median
        if(useInsertion){
            if(last <= lastElementPos){
                if (inputMI[first] > inputMI[middle])
                {
                        std::swap(inputMI[first], inputMI[middle]);
                        noofkeyCompMedInsert++;
                }
                if (inputMI[middle] > inputMI[last])
                {
                        std::swap(inputMI[middle], inputMI[last]);
                        noofkeyCompMedInsert++;
                }
                if(inputMI[first] > inputMI[last])
                {
                        std::swap(inputMI[first], inputMI[last]);
                        noofkeyCompMedInsert++;
                }
                return (inputMI[middle]);
            }
        }
        else{
//            if(last <= lastElementPos){
                if (inputM[first] > inputM[middle])
                {
                        std::swap(inputM[first], inputM[middle]);
                        numberofKeyComparisonsMedian++;
                }
                if (inputM[middle] > inputM[last])
                {
                        std::swap(inputM[middle], inputM[last]);
                        numberofKeyComparisonsMedian++;
                }
                if(inputM[first] > inputM[last])
                {
                        std::swap(inputM[first], inputM[last]);
                        numberofKeyComparisonsMedian++;
                }
                return (inputM[middle]);
//            }
        }
        return 0;
        
}
