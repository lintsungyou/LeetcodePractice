#include <iostream>
#include <random>
#include <vector>
#include <unistd.h>
#include <getopt.h>
#include "FindMedianFromStream_alg.h"



static std::random_device rd;
static std::mt19937 generator(rd());
static std::uniform_int_distribution<int> uniRand(LO_BOUND - (int)(LO_BOUND * FIND_MEDIAN_RATE)/100, HI_BOUND + (int)(HI_BOUND * FIND_MEDIAN_RATE)/100);



void usage(const char* progname) {
    printf("Usage: %s [options]\n", progname);
    printf("Program Options:\n");
    printf("  -n  --numLength <N>  there will be n calls of addNum \n");
    printf("  -t  --testSize <INT>   Use <INT> numbers of random testCase \n");
    printf("  -s  --selfDefHeap  If this tag is added, myalgorithm() will use self defined heap\n");
    printf("  -?  --help         This message\n");
    printf("-------------description and constraint-----------------------\n");
    printf("At most 100000 calls will be made to addNum and findMedian\n");
	printf("-105 <= num <= 105\n");
	printf("The median is the middle value in an ordered integer list. If the size of the list is even,\n");
	printf(" there is no middle value and the median is the mean of the two middle values.\n");
    printf("Implement the MedianFinder class:\n");

    printf(">>MedianFinder() initializes the MedianFinder object.\n");
    printf(">>void addNum(int num) adds the integer num from the data stream to the data structure.\n");
    printf(">>double findMedian() returns the median of all elements so far. Answers within 10-5 of the actual answer will be accepted.\n");
}

template <class T>
void printArr(const std::vector<T>& _arr)
{
    printf("{");
	for(int i = 0; i < _arr.size(); i++)
	{
        if(i == (_arr.size()-1))
        {
          if(_arr[i] > HI_BOUND || _arr[i] < LO_BOUND)
            printf("FindMedian ");
          else
            printf("%.2f",(double)_arr[i]);
        }
        else{
          if(_arr[i] > HI_BOUND || _arr[i] < LO_BOUND)
          {
            printf("FindMedian, ");
          }
          else
		    printf("%.2f, ", (double)_arr[i]);
        }
	}
    printf("}\n");
}


bool verifyResult (const std::vector<int>& _arr,const std::vector<double>& _stdAnswer,const std::vector<double>& _myAnswer, const int& _testNum) {

    bool rightAns = true;

    for(int i = 0; i < _stdAnswer.size(); i++)
    {
        if(_myAnswer.size() != _stdAnswer.size())
        {
            rightAns = false;
            break;
        }
        if(abs(_stdAnswer[i] - _myAnswer[i]) >= 0.49){
            rightAns = false;
            break;
        }
    }

    if(!rightAns)
    {
    	printf("Wrong, In testNum%d\n)", _testNum);
        printf("  stdAnswer:");
        printArr(_stdAnswer);
        printf("  myAnswer:");
        printArr(_myAnswer);
        printf("  Array:");
    	printArr(_arr);
    	return false;
    }

    printf("Right, In testNum%d\n", _testNum);

    return true;
}

void initializeRandArr(std::vector<int>& _arr, const int& _N)
{
	_arr.reserve(_N);

	for(int i = 0; i < _N; i++)
	{
		_arr.push_back(uniRand(generator));
        if(i == 0)
        {
            //prevent FIND_MEDIAN is the first call;
            if(_arr[0] > HI_BOUND || _arr[0] < LO_BOUND)
            {
                _arr.pop_back();
                i--;
            }
        }
	}	
}


int main(int argc, char** argv){

	// parse commandline options ////////////////////////////////////////////
    int opt, numLength, testSize, kth;
    numLength = 10;
    testSize = 10;
    bool heapChoice = STD_PRIORITY_QUEUE;  
    static struct option long_options[] = {
        {"numLength", 1, 0, 'n'},
        {"testSize", 1, 0, 't'},
        {"selfDefHeap", 0, 0, 's'},
        {"help", 0, 0, '?'},
        {0 ,0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "n:t:s?", long_options, NULL)) != EOF) {

        switch (opt) {
        case 'n':
        {
            std::cout << "here1\n";
            numLength = atoi(optarg);
            if(numLength > SIZE_HI_BOUND || numLength < SIZE_LO_BOUND)
            {
            	printf("array size should be in bound,%d <= n <= %d.\n", SIZE_LO_BOUND, SIZE_HI_BOUND);
            	printf("exit\n");
            }
            break;
        }
        case 't':
        {
            std::cout << "here2\n";
            testSize = atoi(optarg);
            break;
        }
        case 's':
        {
            std::cout << "here3\n";

            heapChoice = SELF_DEFINED_BHEAP;
            break;
        }
        case '?':
        default:
            usage(argv[0]);
            return 1;
        }
    }

    int rightTestNumber = 0;

    for(int i = 0; i < testSize; i++)
    {
    
    	std::vector<int> array;
        std::vector<double> answerNaive;
        std::vector<double> answerMyAlgorithm;

	    initializeRandArr(array, numLength);

        answerNaive = naiveFindMedianFromStream(array);

        answerMyAlgorithm = myAlgorithm(array, heapChoice);


	    if(verifyResult(array,answerNaive, answerMyAlgorithm, i))
	    	rightTestNumber++;
    }

    printf("get test %d/%d right\n", rightTestNumber, testSize);

    return 1;    


}


