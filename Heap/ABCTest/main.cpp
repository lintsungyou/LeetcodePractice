#include <iostream>
#include <random>
#include <vector>
#include <unistd.h>
#include <getopt.h>
#include "ABCTest_alg.h"



static std::random_device rd;
static std::mt19937 generator(rd());
static std::uniform_int_distribution<int> uniRand(LO_BOUND, UPPER_BOUND);



void usage(const char* progname) {
    printf("Usage: %s [options]\n", progname);
    printf("Program Options:\n");
    printf("  -n  --nSize <N>  Use length <N> array \n");
    printf("  -t  --testSize <INT>   Use <INT> numbers of random testCase \n");
    printf("  -?  --help         This message\n");
    printf("-------------description and constraint-----------------------\n");
    printf("n == matrix.length\n");
	printf("n == matrix[i].length\n");
	printf("1 <= n <= 300\n");
	printf("-109 <= matrix[i][j] <= 109\n");
	//printf("All the rows and columns of matrix are guaranteed to be sorted in non-decreasing order.\n");
	printf("1 <= k <= n2\n");
}

void printArray(const std::vector<int>& _arr)
{
	for(int i = 0; i < _arr.size(); i++)
	{
		printf("{");
        printf("%d, ", _arr[i]);
		
		printf("}\n");
	}
}


bool verifyResult (const std::vector<int>& _arr, const int& _stdAnswer,const int& _myAnswer, const int& _testNum) {

    if(_stdAnswer != _myAnswer)
    {
    	printf("Wrong, In testNum%d:  stdAnswer:%d, myAnswer:%d\n", _testNum ,_stdAnswer, _myAnswer);
    	printArray(_arr);
    	return false;
    }

    printf("Right, In testNum%d: stdAnswer:%d, myAnswer:%d\n", _testNum ,_stdAnswer, _myAnswer);

    return true;
}

void initializeRandArray(std::vector<int>& _arr, const int& _N)
{
	
	for(int i = 0; i < _arr.size(); i++)
	{
		
			_arr[i] = uniRand(generator);
		
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
            	printf("array size should be in bound,1 <= n <= 300.\n");
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
    	std::vector<int> arrayTest;
        initializeRandArray(arrayTest, nSize);
        int stdAnswer = naiveABCTest(arrayTest);
        int myAnswer = myAlgorithm(arrayTest);

        if(verifyResult(arrayTest, stdAnswer, myAnswer, i))
        {
            rightTestNumber++;
        }
    }

    printf("get test %d/%d right\n", rightTestNumber, testSize);

    return 1;    


}


