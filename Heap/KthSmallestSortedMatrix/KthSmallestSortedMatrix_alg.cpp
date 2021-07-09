#include "KthSmallestSortedMatrix_alg.h"
#include <vector>
#include <functional>
#include <queue>



int naiveKthSmallestInSortedMatrix(const std::vector<std::vector<int>>& _matrix, const int& _kthSmall)
{
	int N = _matrix.size();

	std::vector<int> indexArr = std::vector<int>(N*N, 0);

	for(int i = 0; i < N*N; i++)
		indexArr[i] = i;

	std::sort(std::begin(indexArr), std::end(indexArr), [&](int a, int b){
		return _matrix[(int)(a/N)][a % N] < _matrix[(int)(b/N)][b % N];
	});

	int targetIndex = indexArr[_kthSmall-1];
	return _matrix[(int)(targetIndex/N)][targetIndex % N];
}

int myAlgorithm(const std::vector<std::vector<int>>& _matrix, const int& _kthSmall)
{
	   int r = _matrix.size();
       int c = _matrix[0].size();
       std::priority_queue<int> pq;
        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                pq.push(_matrix[i][j]);
                if(pq.size()>_kthSmall)
                	pq.pop();
            }
        }
        return pq.top();
}
