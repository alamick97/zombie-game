// 9504853406CBAC39EE89AA3AD238AA12CA198043

//work on this after getting main project & verbose working

#include "Zombie.h"
#include "Game.h"
#include <cstdint>
#include <queue>
#include <vector>

class Stats {
    uint32_t _stats_arg;
    std::priority_queue<Zombie*, std::vector<Zombie*>, MostActiveComparator> _most_active_zombies;
    std::priority_queue<Zombie*, std::vector<Zombie*>, LeastActiveComparator> _least_active_zombies;

public:
    void setStatsArg(uint32_t statsArg);
    void updateMostLeastActive(Zombie* zombie);  //active zombies consider all zombies! Not only dead ones!. To be used whenever round_active changes, so after creation and moving.
	void printFirstZombiesKilled(const std::deque<Zombie*>& inactiveZombies) const;
	void printLastZombiesKilled(const std::deque<Zombie*>& inactiveZombies) const;
	void printMostActiveZombies(); //doesnt need to be dead! all zombies!
	void printLeastActiveZombies(); //dont need to be dead! all zombies!
};