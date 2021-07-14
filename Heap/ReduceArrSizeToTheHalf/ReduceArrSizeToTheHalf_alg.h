#ifndef REDUCEARRSIZETOTHEHALF_ALG_H
#define REDUCEARRSIZETOTHEHALF_ALG_H

#include <vector>
#include <functional>
#include <algorithm>
#include <cmath>
#include <iostream>

#define STD_PRIORITY_QUEUE true
#define	SELF_DEFINED_BHEAP false

const int HI_BOUND = 6;
const int LO_BOUND = 1;
const int SIZE_LO_BOUND = 1;
const int SIZE_HI_BOUND = 100000;

int naiveReduceArrSizeToTheHalf(const std::vector<int>& _arr);

int myAlgorithm(const std::vector<int>& _arr,  bool _stdOrSelfDefinedBHeap);

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

#endif