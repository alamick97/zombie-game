// 9504853406CBAC39EE89AA3AD238AA12CA198043

#include "Game.h"
#include <string>


Game::Game(int argc, char** argv) : _argc(argc), _argv(argv) { //default constructor
    //default initialization of values
    _verbose_flag = false;
    _stats_flag = false;
    _median_flag = false;
	_youDied_flag = false;

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

bool Game::verboseOn() const { return _verbose_flag; }
bool Game::statsOn() const { return _stats_flag; }
bool Game::medianOn() const { return _median_flag; }
bool Game::youDied() const { return _youDied_flag; }
void Game::refillQuiver() { _quiver_load = _quiver_capacity; }
uint32_t Game::getRandSeed() const { return _rand_seed; }
uint32_t Game::getMaxDist() const { return _max_rand_dist; }
uint32_t Game::getMaxSpeed() const { return _max_rand_speed; }
uint32_t Game::getMaxHealth() const { return _max_rand_health; }

void Game::shootZombies() { 
	//TODO: finish implementing
	//NOTE: Maybe use min(distance,speed), or if (distance < speed) { distance = 0; return distance? }
	while (_quiver_load != 0 && !_active_queue.empty()) { //when quiver_load isn't empty AND active_list isn't empty (need to check here, since zombies get popped from active list.)
		Zombie* tempZomb = _active_queue.top();//get zombie from active list (PQ)
		uint32_t tempHealth = tempZomb->getHealth();
		//2 Cases: 
		if (_quiver_load >= tempZomb->getHealth()) { //if quiver load is more than zombie's health
			_quiver_load = _quiver_load - tempZomb->getHealth(); //adjust quiver load
			tempHealth = 0; //set health accordingly 
		} else if (_quiver_load < tempZomb->getHealth()) {
			tempHealth = tempHealth - _quiver_load; //set health accordingly
		}

		tempZomb->setHealth(tempHealth);//updates heath accordingly

		if (tempHealth == 0) {
			_inactive_deque.push_front(_active_queue.top()); //for first/last killed list
			_active_queue.pop();//pop zombie
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

bool Game::noZombiesActive() const { return _active_queue.empty(); }