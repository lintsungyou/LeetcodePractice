#include <iostream>
#include <random>
#include <vector>
#include <unistd.h>
#include <getopt.h>
#include "KthSmallestSortedMatrix_alg.h"

const int UPPER_BOUND = 109;
const int LO_BOUND = -109;
const int SIZE_LO_BOUND = 1;
const int SIZE_HI_BOUND = 300;

static std::random_device rd;
static std::mt19937 generator(rd());
static std::uniform_int_distribution<int> uniRand(LO_BOUND, UPPER_BOUND);



void usage(const char* progname) {
    printf("Usage: %s [options]\n", progname);
    printf("Program Options:\n");
    printf("  -n  --nSize <N>  Use NxN matrix \n");
    printf("  -t  --testSize <INT>   Use <INT> numbers of random testCase \n");
    printf("  -?  --help         This message\n");
    printf("-------------description and constraint-----------------------\n");
    printf("n == matrix.length\n");
	printf("n == matrix[i].length\n");
	printf("1 <= n <= 300\n");
	printf("-109 <= matrix[i][j] <= 109\n");
	printf("All the rows and columns of matrix are guaranteed to be sorted in non-decreasing order.\n");
	printf("1 <= k <= n2\n");
}

void printMatrix(const std::vector<std::vector<int>>& _matrix)
{
	for(int i = 0; i < _matrix.size(); i++)
	{
		printf("{");
		for(int j = 0; j < _matrix[0].size(); j++)
		{
			if(j != (_matrix[0].size() - 1))
				printf("%d, ", _matrix[i][j]);
			else
				printf("%d", _matrix[i][j]);
		}
		printf("}\n");
	}
}


bool verifyResult (const std::vector<std::vector<int>>& _matrix,const int& _kthSmall,const int& _stdAnswer,const int& _myAnswer, const int& _testNum) {

    if(_stdAnswer != _myAnswer)
    {
    	printf("Wrong, In testNum%d: %dth smallest element search, stdAnswer:%d, myAnswer:%d\n", _testNum ,_kthSmall ,_stdAnswer, _myAnswer);
    	printMatrix(_matrix);
    	return false;
    }

    printf("Right, In testNum%d: %dth smallest element search, stdAnswer:%d, myAnswer:%d\n", _testNum ,_kthSmall ,_stdAnswer, _myAnswer);

    return true;
}

void initializeRandMatrix(std::vector<std::vector<int>>& _matrix, const int& _N)
{
	_matrix = std::vector<std::vector<int>>(_N, std::vector<int>(_N, 0));

	for(int i = 0; i < _matrix.size(); i++)
	{
		for(int j = 0; j < _matrix[0].size(); j++)
		{
			_matrix[i][j] = uniRand(generator);
		}
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
            	printf("matrix size should be in bound,1 <= n <= 300.\n");
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
    	std::random_device kthRd;
    	static std::mt19937 generatorKth(kthRd());
    	static std::uniform_int_distribution<int> uniRand(1, nSize);

    	std::vector<std::vector<int>> matrix;

	    initializeRandMatrix(matrix, nSize);

	    int kth = uniRand(generatorKth);

	    int stdAnswer = naiveKthSmallestInSortedMatrix(matrix, kth);
	    int myAnswer = myAlgorithm(matrix, kth);

	    if(verifyResult(matrix, kth, stdAnswer, myAnswer, i))
	    	rightTestNumber++;
    }

    printf("get test %d/%d right\n", rightTestNumber, testSize);

    return 1;    


}


