// 9504853406CBAC39EE89AA3AD238AA12CA198043

//work on this after getting main project & verbose working

#include "Stats.h"

void Stats::setStatsArg(uint32_t statsArg) {
	_stats_arg = statsArg;	
}

void Stats::updateMostLeastActive(Zombie* zombie) {
	if (_most_active_zombies.size() < _stats_arg || 
		zombie->getRoundsActive() >= _most_active_zombies.top()->getRoundsActive()) {
		_most_active_zombies.push(zombie);
        if (_most_active_zombies.size()) { _most_active_zombies.pop(); }
	}	
	if (_least_active_zombies.size() < _stats_arg || 
		zombie->getRoundsActive() <= _least_active_zombies.top()->getRoundsActive()) {
        _least_active_zombies.push(zombie);
        if (_least_active_zombies.size()) { _least_active_zombies.pop(); }
	}
}

void Stats::printFirstZombiesKilled(const std::deque<Zombie*>& inactiveZombies) const {
	uint32_t N = std::min(_stats_arg, static_cast<uint32_t>(inactiveZombies.size()));

	std::cout << "First zombies killed:\n";

	auto it = inactiveZombies.begin();
	for (uint32_t i = 1; i < (N + 1); ++i) { //from 1 to N+1 so that it counts from 1 (for output req.)
		std::cout << (*it)->getName() << " " << i << "\n";	
		++it;
	}
}

void Stats::printLastZombiesKilled(const std::deque<Zombie*>& inactiveZombies) const {
	uint32_t N = std::min(_stats_arg, static_cast<uint32_t>(inactiveZombies.size()));

	std::cout << "Last zombies killed:\n";

	auto it = inactiveZombies.rbegin();
	for (uint32_t i = 0; i < N; ++i) { //from 1 to N+1 so that it counts from 1 (for output req.)
		std::cout << (*it)->getName() << " " << (N-i) << "\n";	
		++it;
	}
}

void Stats::printMostActiveZombies() const {
	//TODO: Implement
}

void Stats::printLeastActiveZombies() const {
	//TODO: Implement
}