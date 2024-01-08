// 9504853406CBAC39EE89AA3AD238AA12CA198043

#include "Game.h"
#include "P2random.h"
#include "Median.h"
#include "Stats.h"
#include <cstdint>
#include <iostream>

struct Round {
	uint32_t next_round = 0;
	uint32_t num_rand_zombies = 0;
	uint32_t num_named_zombies = 0;
};

int main (int argc, char** argv) {
	std::ios_base::sync_with_stdio(false); // Speeds up project's I/O

	Median median; //for median info. not used if not enabled.
	Stats stats; //for stats info. not used if not enabled.
	Game game(argc, argv); //creates game object on the stack
	game.setGameInfo(); //unit tested. gets quiv. cap., rand seed, max rands. 
	if (game.isStatsOn()) { stats.setStatsArg(game.getStatsArg()); }

	P2random randZombGenerator; //declares rand zomb gen
	randZombGenerator.initialize(game.getRandSeed(), game.getMaxDist(), game.getMaxSpeed(), game.getMaxHealth()); //inits rand zomb gen

	std::string junk;
	uint32_t current_round = 0;
	uint32_t next_round = 0;
	(void) next_round; //suppressees unused variable warning (it's used in conditional while-loop)
	bool playerIsDead = false;
	(void) playerIsDead; //suppressees unused variable warning (it's used in conditional while-loop)
	Round round;

	//NOTE: There is always at least one round! (input constraint)
	while (!std::cin.fail() || game.areZombiesActive()) { //Zombie Manipulation Order: MOVE->CREATE->DESTROY
		//start new round
		current_round++;
		//STEP 1: print round (only if verbose flag is enabled)
		if (game.isVerboseOn()) { std::cout << "Round: " << current_round << "\n"; } //prints round 
		//STEP 2: refill quiver
		game.refillQuiver(); //makes _quiver_load = _quiver_capacity, which was found before while loop.
		//STEP 3: move all ACTIVE zombies and sets _player_is_dead_flag if you get killed (distance for any zombie = 0)
		game.moveZombies(); //NOTE: This also increments "rounds active" for each active zombie. Also updates stats most/least active after moving (since this changes who is most/least active.) 
		//STEP 4: check if you're dead (distance for any zombie = 0)
		if (game.isPlayerDead()) { break; } //Note: ONLY place to check if you are dead. EVEN IF zombie spawns w/ dist=0, must MOVE first (it must MOVE before ATTACKING!). 
		
		if (round.next_round == 0) { 
			std::getline(std::cin, junk);	//removes trailing whitespace
			std::getline(std::cin, junk);	//removes "---" line
			std::cin >> junk >> round.next_round; //gets next round info from input file!
		}
		//STEP 5: New zombies appear (Create zombies!)
		if (round.next_round == current_round) { //only to be done when curr round reaches specified input round!
			std::cin >> junk >> round.num_rand_zombies;
			std::cin >> junk >> round.num_named_zombies;

			std::string zName;
			uint32_t zDist;
			uint32_t zSpeed;
			uint32_t zHealth;

			for (uint32_t i = 0; i < round.num_rand_zombies; ++i) { //create rand zombies based on info given
				zName = randZombGenerator.getNextZombieName();
				zDist = randZombGenerator.getNextZombieDistance();
				zSpeed = randZombGenerator.getNextZombieSpeed();
				zHealth = randZombGenerator.getNextZombieHealth();

				Zombie* randZombie = new Zombie(zName, zDist, zSpeed, zHealth);
				//pushes to appropriate lists
				game.pushToMasterList(randZombie);//push to master list. This must be done in order of creation. 
				game.pushToActiveList(randZombie);//push to active list 
				//if (game.isStatsOn()) { stats.updateMostLeastActive(randZombie); } //for stats, most/least active output
				//verbose output
				if (game.isVerboseOn()) { randZombie->printCreated(); }
			}

			for (uint32_t i = 0; i < round.num_named_zombies; ++i) { //create named zombies based on info given
				std::cin >> zName;
				std::cin >> junk >> zDist;
				std::cin >> junk >> zSpeed;
				std::cin >> junk >> zHealth;

				Zombie* namedZombie = new Zombie(zName, zDist, zSpeed, zHealth); //initialize named zombie w/ zombie constructor
				//pushes to appropriate lists
				game.pushToMasterList(namedZombie);//push to master list. This must be done in order of creation. 
				game.pushToActiveList(namedZombie);//push to active list 
				//if (game.isStatsOn()) { stats.updateMostLeastActive(namedZombie); } //for stats, most/least active output
				//verbose output
				if (game.isVerboseOn()) { namedZombie->printCreated(); }
			}
			round.next_round = 0; //resets next round
		}
		//STEP 6: Shoot zombies
		game.shootZombies(&median); 
		//FINAL STEP (in loop): Print median! (total for all destroyed zombies in game)
		//TODO: Finish Median implementation!
		if (game.isMedianOn()) { //NOTE: Median is for all zombies destroyed thus far in game.
			std::cout << "At the end of round " << current_round << ", the median zombie lifetime is " << median.getMedian() << "\n"; //TODO: Implement/finish
		}
	}

	//print victory/defeat output
	if (game.isPlayerDead()) {
		std::cout << "DEFEAT IN ROUND " << current_round << "! ";
		std::cout << game.getNameOfZombieThatKilled() << " ate your brains!\n";
	} else { //if player isn't dead, then you mustve won.
		std::cout << "VICTORY IN ROUND " << current_round << "! ";
		std::cout << game.getNameOfLastZombie() << " was the last zombie.\n";
	}

	//STATISTICS OUTPUT:
	if (game.isStatsOn()) {
		//Needs:
		//-Num zombies still active
		std::cout << "Zombies still active: " << game.getNumZombiesStillActive() << "\n";
		//-First n Zombies Killed (inactive list, by order)
		stats.printFirstZombiesKilled(game.getInactiveZombies());
		//-Last n Zombies Killed
		stats.printLastZombiesKilled(game.getInactiveZombies());

		stats.determineMostLeastActive(game.getAllZombies());
		//-n Most active Zombies (_rounds_active) 
		stats.printMostActiveZombies();
		//-n Least active Zombies (_rounds_active) 
		stats.printLeastActiveZombies();
	}

	//deletes all dangling zombie ptrs to prevent memory leaks. 
	game.deleteZombies(); //deletes all Zombie ptrs created on the heap during the while loop! Must be done to prevent mem leaks!

	return 0;
}