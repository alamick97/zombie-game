// 9504853406CBAC39EE89AA3AD238AA12CA198043

//work on this after getting main project & verbose working

#include "Stats.h"

void Stats::setStatsArg(size_t statsArg) {
	_stats_arg = statsArg;	
}

void Stats::printFirstZombiesKilled(const std::deque<Zombie*>& inactiveZombies) const {
	//uint32_t N = std::min(_stats_arg, static_cast<uint32_t>(inactiveZombies.size()));
	size_t N = std::min(_stats_arg, inactiveZombies.size()); //size_t for AG

	std::cout << "First zombies killed:\n";

	auto it = inactiveZombies.begin();
	for (uint32_t i = 1; i < (N + 1); ++i) { //from 1 to N+1 so that it counts from 1 (for output req.)
		std::cout << (*it)->getName() << " " << i << "\n";	
		++it;
	}
}

void Stats::printLastZombiesKilled(const std::deque<Zombie*>& inactiveZombies) const {
	//uint32_t N = std::min(_stats_arg, static_cast<uint32_t>(inactiveZombies.size()));
	size_t N = std::min(_stats_arg, inactiveZombies.size()); //size_t for AG

	std::cout << "Last zombies killed:\n";

	auto it = inactiveZombies.rbegin();
	for (uint32_t i = 0; i < N; ++i) { //from 1 to N+1 so that it counts from 1 (for output req.)
		std::cout << (*it)->getName() << " " << (N-i) << "\n";	
		++it;
	}
}

void Stats::updateMostLeastActive(Zombie* zombie) {
	if (_most_active_zombies.size() < _stats_arg || 
		zombie->getRoundsActive() >= _most_active_zombies.top()->getRoundsActive()) {
		_most_active_zombies.push(zombie);
        if (_most_active_zombies.size() > _stats_arg) { _most_active_zombies.pop(); }
	}	
	if (_least_active_zombies.size() < _stats_arg || 
		zombie->getRoundsActive() <= _least_active_zombies.top()->getRoundsActive()) {
        _least_active_zombies.push(zombie);
        if (_least_active_zombies.size() > _stats_arg) { _least_active_zombies.pop(); }
	}
}

void Stats::printMostActiveZombies() { //original way to call most/least active, destroys queues
	std::cout << "Most active zombies:\n";
	size_t count = 0;
	while (!_most_active_zombies.empty() && count < _stats_arg) {
		std::cout << _most_active_zombies.top()->getName() << " " << _most_active_zombies.top()->getRoundsActive() << "\n";
		_most_active_zombies.pop();
		++count;
	}
}

void Stats::printLeastActiveZombies() { //original way to call most/least active, destroys queues
	std::cout << "Least active zombies:\n";
	size_t count = 0;
	while (!_least_active_zombies.empty() && count < _stats_arg) {
		std::cout << _least_active_zombies.top()->getName() << " " << _least_active_zombies.top()->getRoundsActive() << "\n";
		_least_active_zombies.pop();
		++count;
	}
}

/* ALTERNATIVE VERSIONS THAT PRESERVE MOST & LEAST ACTIVE QUEUES. PROBABLY UNNECESSARY - CAN DELETE IF ORIGINALS WORK.
void Stats::printMostActiveZombies() {
	std::cout << "Most active zombies:\n";
	auto temp_queue = _most_active_zombies;
	uint32_t count = 0;
	while (!temp_queue.empty() && count < _stats_arg) {
		Zombie* zombie = temp_queue.top();
		std::cout << zombie->getName() << " " << zombie->getRoundsActive() << "\n";
		temp_queue.pop();
		++count;
	}
}

void Stats::printLeastActiveZombies() {
	std::cout << "Least active zombies:\n";
	auto temp_queue = _least_active_zombies;
	uint32_t count = 0;
	while (!temp_queue.empty() && count < _stats_arg) {
		Zombie* zombie = temp_queue.top();
		std::cout << zombie->getName() << " " << zombie->getRoundsActive() << "\n";
		temp_queue.pop();
		++count;
	}
}
*/