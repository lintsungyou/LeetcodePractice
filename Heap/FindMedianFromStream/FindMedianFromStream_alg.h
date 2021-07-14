#ifndef FINDMEDIANFROMSTREAM_ALG_H
#define FINDMEDIANFROMSTREAM_ALG_H

#include <vector>
#include <functional>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>

#define STD_PRIORITY_QUEUE true
#define	SELF_DEFINED_BHEAP false
#define FIND_MEDIAN_RATE 10

const int HI_BOUND = 105;
const int LO_BOUND = -105;
const int SIZE_LO_BOUND = 1;
const int SIZE_HI_BOUND = 100000;

std::vector<double> naiveFindMedianFromStream(const std::vector<int>& _arr);

std::vector<double> myAlgorithm(const std::vector<int>& _arr, bool _stdOrSelfDefinedBHeap);

class BHeap{
public:
	//constructor
	BHeap();
	BHeap(std::vector<int> _inp);

	//method
	bool isMaxHeap(int i = 0);
	int extractMax();
	void print(){
		for(auto item : mBinaryTree)
			{std::cout << item << ", ";} 
		std::cout << std::endl;

	}

private:
	void heapify(int _root); // heapify from specific root
	void swapByIndex(int _x, int _y);

	std::vector<int>mBinaryTree;
	int heapSize;
};

class MedianStructure{
public:
	//constructor
	explicit MedianStructure(bool _stdOrSelfDefinedBHeap);

	void addNum(int _num);
	double findMedian();
	void printTop();
private:
	bool stdOrSelfDefinedBHeap;
	

	std::priority_queue<int, std::vector<int> ,std::greater<int>> upperStdHeap;
	std::priority_queue<int> lowerStdHeap;

	BHeap upperHeap;
	BHeap lowerHeap;



};

#endif