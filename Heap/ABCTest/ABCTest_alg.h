#ifndef ABCTEST_ALG_H
#define ABCTEST_ALG_H

#include <vector>
#include <functional>
#include <algorithm>
#include <cmath>

const int UPPER_BOUND = 109;
const int LO_BOUND = -109;
const int SIZE_LO_BOUND = 1;
const int SIZE_HI_BOUND = 300;

int naiveABCTest(const std::vector<int>& _arr);

int myAlgorithm(const std::vector<int>& _arr);

#endif