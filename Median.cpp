// 9504853406CBAC39EE89AA3AD238AA12CA198043

//STRATEGY: work on this after getting main project & verbose working
//USE CASE: This class is only meant to be used with destroyed zombies! (works regardless, but not intended use case.)

#include "Median.h"

void Median::insertNumber(uint32_t num) {
    leftHeap.push(num); //push to max heap, left, which finds the largest value for us.
    rightHeap.push(leftHeap.top()); //move largest val from left to right, since right stores larger half of nums
    leftHeap.pop(); 

    if (leftHeap.size() < rightHeap.size()) { //point: to keep the sizes no more than 1 off.
        leftHeap.push(rightHeap.top()); //this gets the smallest val in right and stores it in left, since right is a min-heap
        rightHeap.pop();
    }
}

uint32_t Median::getMedian() { //determines/gets/returns median
    if (leftHeap.size() > rightHeap.size()) { return leftHeap.top(); } //this will be the median, if total size is odd
    else { return (leftHeap.top() + rightHeap.top()) / 2; } //this will be the median, if total size is even
}