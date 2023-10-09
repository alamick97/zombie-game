// 9504853406CBAC39EE89AA3AD238AA12CA198043

//work on this after getting main project & verbose working

#include "Stats.h"

void Stats::updateMostLeastActive(Zombie* zombie, uint32_t statsArg) {
	if (_most_active_zombies.size() < statsArg || zombie->getRoundsActive() >= _most_active_zombies.top()->getRoundsActive()) {
		_most_active_zombies.push(zombie);
        if (_most_active_zombies.size()) { _most_active_zombies.pop(); }
	}	
	if (_least_active_zombies.size() < statsArg || zombie->getRoundsActive() <= _least_active_zombies.top()->getRoundsActive()) {
        _least_active_zombies.push(zombie);
        if (_least_active_zombies.size()) { _least_active_zombies.pop(); }
	}
}

void Stats::printStatistics() const {
    //TODO: Implement!
}
