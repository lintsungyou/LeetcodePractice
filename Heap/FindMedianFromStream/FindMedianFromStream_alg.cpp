#include "FindMedianFromStream_alg.h"
#include <vector>
#include <functional>
#include <algorithm>
#include <queue>
#include <cmath>
#include <limits>
#include <unordered_map>


std::vector<double> naiveFindMedianFromStream(const std::vector<int>& _arr) //
{
	std::vector<double> answer;
	std::vector<int> numList;

	// for(const auto &item : _arr)
	// {
	// 	std::cout << item << ",";
	// }
	// std::cout << "\n";

	for(const auto &item : _arr)
    {
        if(item <= HI_BOUND && item >= LO_BOUND)
        {
        	numList.push_back(item);	
        }            
        else{
        	//FIND MEDIAN iS CALLED
			std::sort(numList.begin(), numList.end());			
			if(numList.size() % 2 == 0)
				answer.push_back((numList[numList.size()/2] + numList[numList.size()/2 - 1])/2.0);
			else
				answer.push_back(numList[floor(numList.size()/2)]);

        }
    }

 //    for(const auto &item : answer)
	// {
	// 	std::cout << item << ",";
	// }
	// std::cout << "\n";

    return answer;

}

std::vector<double> myAlgorithm(const std::vector<int>& _arr, bool _stdOrSelfDefinedBHeap)
{
	std::vector<double> answer;

	MedianStructure myMS(_stdOrSelfDefinedBHeap);

	// for(const auto &item : _arr)
	// {
	// 	std::cout << item << ",";
	// }
	// std::cout << "\n";

	for(int i = 0; i < _arr.size(); i++)
    {		

        if(_arr[i] <= HI_BOUND && _arr[i] >= LO_BOUND)
        {
        	myMS.addNum(_arr[i]);	
        }            
        else{

        	answer.push_back(myMS.findMedian());			
        }
    }

    return answer;

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


MedianStructure::MedianStructure(bool _stdOrSelfDefinedBHeap)
{
	stdOrSelfDefinedBHeap = _stdOrSelfDefinedBHeap;
}

void MedianStructure::addNum(int _num)
{
	//printf("add %d\n", _num);
	if(stdOrSelfDefinedBHeap == STD_PRIORITY_QUEUE)
	{
		if(upperStdHeap.size() == 0)
		{
		
			upperStdHeap.push(_num);
			return;
		}
		else if(lowerStdHeap.size() == 0)
		{
			
			
			if(_num < upperStdHeap.top())
				lowerStdHeap.push(_num);
			else
			{
				lowerStdHeap.push(upperStdHeap.top());
				//printTop();
				upperStdHeap.pop();
				upperStdHeap.push(_num);

				//printTop();

			}
		
			return;
		}
		else if(_num > upperStdHeap.top())
		{
			upperStdHeap.push(_num);
			//printTop();
			if(upperStdHeap.size() - lowerStdHeap.size() ==2)
			{
				lowerStdHeap.push(upperStdHeap.top());
				upperStdHeap.pop();
			}
			else if(lowerStdHeap.size() - upperStdHeap.size() ==2)
			{
				upperStdHeap.push(lowerStdHeap.top());
				lowerStdHeap.pop();
			}
			//printTop();
		}
		else if(_num < lowerStdHeap.top())
		{
			lowerStdHeap.push(_num);
			//printTop();

			if(upperStdHeap.size() - lowerStdHeap.size() ==2)
			{
				lowerStdHeap.push(upperStdHeap.top());
				upperStdHeap.pop();
			}
			else if(lowerStdHeap.size() - upperStdHeap.size() ==2)
			{
				upperStdHeap.push(lowerStdHeap.top());
				lowerStdHeap.pop();
			}
			//printTop();

		}
		else
		{
			(upperStdHeap.size() > lowerStdHeap.size())? lowerStdHeap.push(_num) : upperStdHeap.push(_num);
			//printTop();
		}
	}else{
		
	}
}

double MedianStructure::findMedian(){
	if(stdOrSelfDefinedBHeap == STD_PRIORITY_QUEUE)
	{
		if(upperStdHeap.size() > lowerStdHeap.size())
		{
			return upperStdHeap.top();

		}
		else if(upperStdHeap.size() < lowerStdHeap.size())
		{
			return lowerStdHeap.top();
		}
		else
		{
			return (double)(upperStdHeap.top() + lowerStdHeap.top())/2.0;
		}
	}else{
		return 0.0;
	}
}

void MedianStructure::printTop(){
	printf("upperTop:%d, lowerTop:%d, upperTopLen:%d, lowerTopLen:%d\n", 
		upperStdHeap.top(), lowerStdHeap.top(), upperStdHeap.size(), lowerStdHeap.size());
}
