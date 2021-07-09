#ifndef KTHSMALLESTSORTEDMATRIX_ALG_H
#define KTHSMALLESTSORTEDMATRIX_ALG_H

#include <vector>
#include <functional>
#include <algorithm>
#include <cmath>

int naiveKthSmallestInSortedMatrix(const std::vector<std::vector<int>>& _matrix, const int& _kthSmall);

int myAlgorithm(const std::vector<std::vector<int>>& _matrix, const int& _kthSmall);

#endif