// 9504853406CBAC39EE89AA3AD238AA12CA198043

//STRATEGY: work on this after getting main project & verbose working
//USE CASE: This class is only meant to be used with destroyed zombies! (works regardless, but not intended use case.)
#ifndef MEDIAN_H
#define MEDIAN_H

#include <cstdint>
#include <queue>
#include <vector>
class Median {
    std::priority_queue<uint32_t> leftHeap; //max heap
    std::priority_queue<uint32_t, std::vector<uint32_t>, std::greater<uint32_t>> rightHeap; //min heap

public:
    void insertNumber(uint32_t num); //should insert only when zombies die!
    uint32_t getMedian(); //gets/returns median
};

#endif //MEDIAN_H