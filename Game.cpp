// 9504853406CBAC39EE89AA3AD238AA12CA198043

#include "Game.h"
#include <string>


Game::Game(int argc, char** argv) : _argc(argc), _argv(argv) { //default constructor
    //default initialization of options flags
    _verbose_flag = false;
    _stats_flag = false;
    _median_flag = false;

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

bool Game::getMedianFlag() { return _median_flag; }

void Game::refillQuiver() { _quiver_load = _quiver_capacity; }

void Game::setGameInfo() {
	std::getline(std::cin, _junk);
		
	std::cin >> _junk >> _quiver_capacity;
	std::cin >> _junk >> _rand_seed;
	std::cin >> _junk >> _max_rand_dist; //order is distance, speed, health
	std::cin >> _junk >> _max_rand_speed;
	std::cin >> _junk >> _max_rand_health;
}

bool Game::allZombiesDead() const { return active_list.empty(); }