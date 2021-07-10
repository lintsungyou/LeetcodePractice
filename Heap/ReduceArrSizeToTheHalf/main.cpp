#include <iostream>
#include <random>
#include <vector>
#include <unistd.h>
#include <getopt.h>
#include "ReduceArrSizeToTheHalf_alg.h"



static std::random_device rd;
static std::mt19937 generator(rd());
static std::uniform_int_distribution<int> uniRand(LO_BOUND, HI_BOUND);



void usage(const char* progname) {
    printf("Usage: %s [options]\n", progname);
    printf("Program Options:\n");
    printf("  -n  --nSize <N>  Use N length array \n");
    printf("  -t  --testSize <INT>   Use <INT> numbers of random testCase \n");
    printf("  -?  --help         This message\n");
    printf("-------------description and constraint-----------------------\n");
    printf("1 <= arr.length <= 105\n");
	printf("arr.length is even.\n");
	printf("1 <= arr[i] <= 105\n");
	printf("You are given an integer array arr. You can choose a set of integers and remove all the occurrences of these integers in the array..\n");
	printf("Return the minimum size of the set so that at least half of the integers of the array are removed\n");
}

void printArr(const std::vector<int>& _arr)
{
    printf("{");
	for(int i = 0; i < _arr.size(); i++)
	{
        if(i == (_arr.size()-1))
          printf("%d", _arr[i]);
        else
		  printf("%d, ", _arr[i]);
	}
    printf("}\n");
}


bool verifyResult (const std::vector<int>& _arr,const int& _stdAnswer,const int& _myAnswer, const int& _testNum) {

    if(_stdAnswer != _myAnswer)
    {
    	printf("Wrong, In testNum%d:  stdAnswer:%d, myAnswer:%d\n", _testNum ,_stdAnswer, _myAnswer);
    	printArr(_arr);
    	return false;
    }

    printf("Right, In testNum%d:  stdAnswer:%d, myAnswer:%d\n", _testNum ,_stdAnswer, _myAnswer);

    return true;
}

void initializeRandArr(std::vector<int>& _arr, const int& _N)
{
	_arr.reserve(_N);

	for(int i = 0; i < _N; i++)
	{
		_arr.push_back(uniRand(generator));
	}	
}


int main(int argc, char** argv){

	// parse commandline options ////////////////////////////////////////////
    int opt, nSize, testSize, kth;
    nSize = 2;
    testSize = 10;
    static struct option long_options[] = {
        {"nSize", 1, 0, 'n'},
        {"testSize", 1, 0, 't'},
        {"help", 0, 0, '?'},
        {0 ,0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "n:t:?", long_options, NULL)) != EOF) {

        switch (opt) {
        case 'n':
        {
            nSize = atoi(optarg);
            if(nSize > SIZE_HI_BOUND || nSize < SIZE_LO_BOUND)
            {
            	printf("array size should be in bound,%d <= n <= %d.\n", SIZE_LO_BOUND, SIZE_HI_BOUND);
            	printf("exit\n");
            }
            break;
        }
        case 't':
        {
            testSize = atoi(optarg);
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

	    initializeRandArr(array, nSize);

	    int stdAnswer = naiveReduceArrSizeToTheHalf(array);
	    int myAnswer = myAlgorithm(array);

	    if(verifyResult(array,stdAnswer, myAnswer, i))
	    	rightTestNumber++;
    }

    printf("get test %d/%d right\n", rightTestNumber, testSize);

    return 1;    


}


