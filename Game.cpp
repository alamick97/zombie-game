// 9504853406CBAC39EE89AA3AD238AA12CA198043

#include "Game.h"
#include <string>


Game::Game(int argc, char** argv) : _argc(argc), _argv(argv) { //default constructor
    //default initialization of values
    _verbose_flag = false;
    _stats_flag = false;
    _median_flag = false;
	_player_is_dead_flag = false;

    int opt;
	int opt_idx;

	static struct option long_opts[] = {
		{"verbose", no_argument, 0, 'v'},	//no arg req
		{"statistics", required_argument, 0, 's'},	//uint32_t arg req
		{"median", no_argument, 0, 'm'},	//no arg req
		{"help", no_argument, 0, 'h'},	//arg req.
	};

	while ((opt = getopt_long(_argc, _argv, "vs:mh", long_opts, &opt_idx)) != -1) {
		switch(opt) {
			case 'v':
                _verbose_flag = true;   
				break;
			case 's':
                _stats_flag = true;
                _stats_arg = std::stoul(optarg);
				break;
			case 'm':
                _median_flag = true;
				break;
			case 'h':
				std::cout << "HELP:\n";
				std::cout <<"---------------\n";
				std::cout << "To use the program, do the following:\n";
				std::cout << "Run the executable with an input file which follows the required specs.\n";
				std::cout << "The following options are available:\n";
				std::cout << "-v for verbose mode, -s for statistics mode (requires an integer argument)\n";
                std::cout << "and -m for median mode.\n";
                std::exit(0);
		}
	}
}

void Game::setGameInfo() {
	std::getline(std::cin, _junk);
		
	std::cin >> _junk >> _quiver_capacity;
	std::cin >> _junk >> _rand_seed;
	std::cin >> _junk >> _max_rand_dist; //order is distance, speed, health
	std::cin >> _junk >> _max_rand_speed;
	std::cin >> _junk >> _max_rand_health;
}

bool Game::isVerboseOn() const { return _verbose_flag; }
bool Game::isStatsOn() const { return _stats_flag; }
bool Game::isMedianOn() const { return _median_flag; }
void Game::refillQuiver() { _quiver_load = _quiver_capacity; }
void Game::setPlayerIsDeadFlag() { _player_is_dead_flag = true; }
bool Game::isPlayerDead() const { return _player_is_dead_flag; }
uint32_t Game::getRandSeed() const { return _rand_seed; }
uint32_t Game::getMaxDist() const { return _max_rand_dist; }
uint32_t Game::getMaxSpeed() const { return _max_rand_speed; }
uint32_t Game::getMaxHealth() const { return _max_rand_health; }

void Game::moveZombies() { //moves each active zombie by subtracting speed from distance. (for one round)
	for (auto it = _master_deque.begin(); it != _master_deque.end(); ++it) { //iterates front to back of _master_deque (in order of creation)
		Zombie* zombie = *it; //dereference iterator (ptr to Zombie ptr) to get zombie ptr (Zombie*)
		//1. check if health 0. if so, skip
		if (zombie->getHealth() == 0) { continue; }
		//2. move zombies:
		uint32_t newDistance = zombie->getDistance() - std::min(zombie->getDistance(), zombie->getSpeed());
		zombie->setDistance(newDistance);
		//INCREMENT ROUNDS ACTIVE HERE
		zombie->incrementRoundsActive();
		//3. check if dist=0. if so, you're dead.
		if (zombie->getDistance() == 0) { _player_is_dead_flag = true; }
	}
}

void Game::pushToMasterList(Zombie* zombie) { //note: we are pushing to a STL deque that takes <Zombie>!
	_master_deque.push_back(zombie); //hence, the master list has zombies ordered chronologically by order of creation (front to back). Hence we push_back.
}

void Game::pushToActiveList(Zombie* zombie) { //note: we are pushing to a PQ that takes <Zombie*>!
	_active_queue.push(zombie);
}

void Game::shootZombies() { 
	while (_quiver_load != 0 && !_active_queue.empty()) { //when quiver_load isn't empty AND active_list isn't empty (need to check here, since zombies get popped from active list.)
		Zombie* tempZomb = _active_queue.top();//get zombie from active list (PQ)
		uint32_t arrowsShot = std::min(_quiver_load, tempZomb->getHealth());
		_quiver_capacity -= arrowsShot;
		tempZomb->setHealth(tempZomb->getHealth() - arrowsShot);

		if (tempZomb->getHealth() == 0) {
			_inactive_deque.push_back(_active_queue.top()); //for first/last killed list
			_active_queue.pop();//pop zombie
		}
	}
}

void Game::deleteZombies() { //deletes all zombie ptrs, which are all stored in _master_deque! Also clears any containers w/ Zombie*.
	for (Zombie* zombie: _master_deque) { //since other containers are only subsets of _master_deque, only have to call delete on _master_deque.
		delete zombie;
	}
	_master_deque.clear();
	std::priority_queue<Zombie*, std::vector<Zombie*>, ZombieComparator>().swap(_active_queue);
	_inactive_deque.clear();
	//TODO: Clear any inactive lists here.	
}

bool Game::areZombiesActive() const { return !_active_queue.empty(); }