#include "ReduceArrSizeToTheHalf_alg.h"
#include <vector>
#include <functional>
#include <algorithm>
#include <queue>
#include <cmath>
#include <unordered_map>


int naiveReduceArrSizeToTheHalf(const std::vector<int>& _arr) //
{
	//printf("naive start\n");
	std::array<int, HI_BOUND - LO_BOUND+1> occurTimeArr;
	std::fill(occurTimeArr.begin(), occurTimeArr.end(), 0);
	
	for(int i = 0; i < _arr.size(); i++)
	{
		//printf("index %d++", _arr[i] - LO_BOUND);
		occurTimeArr[_arr[i] - LO_BOUND]++;
	}

	std::sort(occurTimeArr.begin(), occurTimeArr.end(), [](int a, int b)->bool{return a > b;});
	int reducedElements = 0;
	int result = 0;
	for(int i = 0; i < occurTimeArr.size(); i++)
	{
		reducedElements += occurTimeArr[i];
		result++;
		//printf("reduced: %d, occurTimeI: %d, result: %d\n", reducedElements, occurTimeArr[i], result);
		if(reducedElements >= _arr.size()/2)
			break;
	}
		//printf("naive end\n");

	return result;
}

int myAlgorithm(const std::vector<int>& _arr)
{
	  std::unordered_map<int, int> numberToTimes;
	  for(int i = 0; i < _arr.size(); i++)
	  {
	  	std::unordered_map<int, int>::const_iterator constIt = numberToTimes.find(_arr[i]);

	  	if(constIt != numberToTimes.end())
	  	{
	  		numberToTimes[_arr[i]]++;
	  	}
	  	else{
	  		numberToTimes.insert(std::make_pair(_arr[i], 1));
	  	}
	  }

      std::unordered_map<int, int>::const_iterator constIt = numberToTimes.begin();
      std::vector<int> forHeap;

      for(constIt; constIt != numberToTimes.end(); constIt++)
      {
      	forHeap.push_back(constIt->second);
      }



      BHeap maxHeap(forHeap);
      //maxHeap.print();
      int result = 0;
      int reducedElements = 0;
      for(int i = 0; i < forHeap.size(); i++)
      {
      	int maxFromHeap = maxHeap.extractMax();
      	reducedElements+= maxFromHeap;
      	//printf("extract: %d\n", maxFromHeap);
      	result++;
      	//maxHeap.print();
      	if(reducedElements >= _arr.size()/2)
			break;
      }
      return result;
}


BHeap::BHeap(){
	heapSize = 0;
}

BHeap::BHeap(std::vector<int> _inp){
	mBinaryTree = _inp;
	heapSize = _inp.size();

	for(int i = floor((heapSize-1)/2); i >=0; i--)
	{
		heapify(i);
	}
}

	
bool BHeap::isMaxHeap(int i){
	// root i == leafNode , it's definitely a MaxHeap
	if(i >= floor((heapSize - 1)/2))
		return true;

	//If an internal node is greater than its children, and the fact is recursively true, the heap is a MaxHeap 
	if(mBinaryTree[i] >= mBinaryTree[2*i + 1] && mBinaryTree[i] >= mBinaryTree[2*i + 2] &&
		isMaxHeap(2*i + 1) && isMaxHeap(2*i + 2));
		return true;

	return false;
}

int BHeap::extractMax(){
	int max = mBinaryTree[0];
	mBinaryTree[0] = mBinaryTree[heapSize - 1];
	mBinaryTree.erase(mBinaryTree.begin() + heapSize - 1);
	heapSize--;
	heapify(0);

	return max;
}

void BHeap::heapify(int _root)
{
	int leftIndex = 2 * _root + 1;
	int rightIndex = 2 * _root + 2;

	if(leftIndex >= heapSize)
		return;
	else if(rightIndex >= heapSize)
	{
		if(mBinaryTree[_root] < mBinaryTree[leftIndex]) //not following the rule of maxheap
		{
			swapByIndex(_root, leftIndex);
			heapify(leftIndex);
		}
	}
	else{
		if(mBinaryTree[_root] > std::max(mBinaryTree[leftIndex], mBinaryTree[rightIndex]))
			return;

		int targetIndex = (mBinaryTree[leftIndex] > mBinaryTree[rightIndex])? leftIndex : rightIndex;

		swapByIndex(_root, targetIndex);
		heapify(targetIndex); 
	}


}

void BHeap::swapByIndex(int _x, int _y){
	int tmp = mBinaryTree[_x];
	mBinaryTree[_x] = mBinaryTree[_y];
	mBinaryTree[_y] = tmp;
}