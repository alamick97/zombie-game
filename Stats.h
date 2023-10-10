// 9504853406CBAC39EE89AA3AD238AA12CA198043

//work on this after getting main project & verbose working

#ifndef STATS_H
#define STATS_H

#include "Zombie.h"
//#include "Game.h"
#include <cstdint>
#include <queue>
#include <vector>

class Stats {
    size_t _stats_arg; //size_t for AG
    std::priority_queue<Zombie*, std::vector<Zombie*>, MostActiveComparator> _most_active_zombies;
    std::priority_queue<Zombie*, std::vector<Zombie*>, LeastActiveComparator> _least_active_zombies;

public:
    void setStatsArg(size_t statsArg); //size_t for AG
    void updateMostLeastActive(Zombie* zombie);  //active zombies consider all zombies! Not only dead ones!. To be used whenever round_active changes, so after creation and moving.
	void printFirstZombiesKilled(const std::deque<Zombie*>& inactiveZombies) const;
	void printLastZombiesKilled(const std::deque<Zombie*>& inactiveZombies) const;
    void printMostLeastActive(const std::deque<Zombie*>& masterDeque); 
	void printMostActiveZombies(); //doesnt need to be dead! all zombies!
	void printLeastActiveZombies(); //dont need to be dead! all zombies!
};

#endif //STATS_H