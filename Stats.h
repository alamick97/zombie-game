// 9504853406CBAC39EE89AA3AD238AA12CA198043

//work on this after getting main project & verbose working

#include "Zombie.h"
#include "Game.h"
#include <queue>
#include <vector>

class Stats {
    std::priority_queue<Zombie*, std::vector<Zombie*>, MostActiveComparator> _most_active_zombies;
    std::priority_queue<Zombie*, std::vector<Zombie*>, LeastActiveComparator> _least_active_zombies;

public:
    void updateMostLeastActive(Zombie* zombie, uint32_t statsArg); 
    void printStatistics() const; //TODO: Implement!
};