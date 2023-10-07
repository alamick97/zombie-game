// 9504853406CBAC39EE89AA3AD238AA12CA198043

#include "Game.h"
#include "P2random.h"
#include <iostream>

struct Round {
	uint32_t next_round = 0;
	uint32_t num_rand_zombies = 0;
	uint32_t num_named_zombies = 0;
};

void printCreated (std::string name, uint32_t dist, uint32_t speed, uint32_t health) const {
	std::cout << "Created: " << name;
	std::cout << " (distance: " << dist;
	std::cout << ", speed: " << speed;
	std::cout << ", health: " << health << ")\n";
}

int main (int argc, char** argv) {
	// Speeds up project's I/O
	std::ios_base::sync_with_stdio(false);

	Game game(argc, argv); //creates game object on the stack
	game.setGameInfo(); //unit tested. gets quiv. cap., rand seed, max rands. 

	P2random randZombGenerator;
	randZombGenerator.initialize(game.getRandSeed(), game.getMaxDist(), game.getMaxSpeed(), game.getMaxHealth()); 

	std::string junk;
	uint32_t current_round = 0;
	uint32_t next_round = 0;
	bool playerIsDead = false;
	Round round;

	while (!std::cin.fail() && game.areZombiesActive()) { //Zombie Manipulation Order: MOVE->CREATE->DESTROY
		//start new round
		current_round++;
		//STEP 1: print round
		std::cout << "Round " << current_round << "\n"; //prints round
		//STEP 2: refill quiver
		game.refillQuiver();
		//STEP 3: move zombies and sets _player_is_dead_flag if you get killed (distance for any zombie = 0)
		game.moveZombies(); //NOTE: This also increments "rounds active" for each active zombie. 
		//STEP 4: check if you're dead (distance for any zombie = 0)
		if (game.isPlayerDead()) { break; } //Note: ONLY place to check if you are dead. EVEN IF zombie spawns w/ dist=0, must MOVE first. 
		
		if (round.next_round == 0) {
			std::getline(std::cin, junk);	//removes "---" line
			std::cin >> junk >> round.next_round;
		}
		//STEP 5: New zombies appear
		if (round.next_round == current_round) {
			std::cin >> junk >> round.num_rand_zombies;
			std::cin >> junk >> round.num_named_zombies;

			std::string zName;
			uint32_t zDist;
			uint32_t zSpeed;
			uint32_t zHealth;

			for (uint32_t i = 0; i < round.num_rand_zombies; ++i) { //create rand zombies
				zName = randZombGenerator.getNextZombieName();
				zDist = randZombGenerator.getNextZombieDistance();
				zSpeed = randZombGenerator.getNextZombieSpeed();
				zHealth = randZombGenerator.getNextZombieHealth();
				Zombie randZombie(zName, zDist, zSpeed, zHealth);
				//TODO: push to appropriate zombie list(s)
				game.pushToMasterList(randZombie);//push to master list
				game.pushToActiveList(randZombie);//push to active list 
				if (game.isVerboseOn()) { printCreated(zName, zDist, zSpeed, zHealth); } //TODO: Make sure this is correctly implemented.
			}

			for (uint32_t i = 0; i < round.num_named_zombies; ++i) { //create named zombies
				std::cin >> zName;
				std::cin >> junk >> zDist;
				std::cin >> junk >> zSpeed;
				std::cin >> junk >> zHealth;

				Zombie namedZombie(zName, zDist, zSpeed, zHealth); //initialize named zombie w/ zombie constructor
				//TODO: push to appropriate zombie list(s)
				if (game.isVerboseOn()) { printCreated(zName, zDist, zSpeed, zHealth); } //TODO: Make sure this is correctly implemented.
			}

			//TODO: DESTROY ZOMBIES HERE 
			//STEP 6: Shoot zombies
			game.shootZombies();

			//TODO: print median here
			//print median stuff here
		}


		//print victory/defeat output
		if (game.isPlayerDead()) {
			std::cout << "DEFEAT IN ROUND " << current_round << "! ";
			std::cout << "... ate your brains!\n";
		} else {
			std::cout << "VICTORY IN ROUND " << current_round << "! ";
			std::cout << "{name of zombie} was the last zombie.\n";
		}

		//IF NEW ZOMBIES GENERATED (CURR_ROUND == NEXT_ROUND):
		//read in new zombies (if apploiabel)
			//create zombie from cin info
				//NOTE: remember to increment rounds active at some point during the round, for each active zombie!
			//then push into deque
		//when create zombies, push into master
		//	then push the zombie ptrs into active_list (PQ) {make sure the address of the zombie pushed into master list is same as 
		//		that pushed into active list PQ}	



		//shoot zombie from top of PQ until zombie is dead, or out of arrows (ONLY 1 OF 2 OF THESE SITUATIONS CAN HAPPEN!)
			//dont want to shoot one at a time, that will take too long. Instead, you want to check how much the zombie's health
			//is. Make a function for this. If the zombie's health is less than your quiver capacity, then kill that zombie, update
			//quiver load, and move on to the next zombie. Idea: can make a while loop for quivers != 0, and have two conditions:
			//PSEUDO:
			//quiver_load = quiver_capacity
			//while(quiver load != 0)
			//1) if (quiver capacity > zombie health): reduce health by appropriate amount, then go to next zombie
			//2) else { zombie_health = zombie_health - quiver_load}


		//NOTE: PQ implementation, in general, should all be hardcoded into this while loop.

		//pseudo: from cin, add zombies to the master & active lists (at same time?)

		//pseudo: If zombie health is 0 (after shooting), then move it from the active list to inactive list.
		/*
		//STEPS LAID OUT IN SPEC:
		//(step 1): player refills quiver so it contains quiver_capacity arrows
		//(step 2): existing zombies move toward the player and attack if they have reached the player
		//(step 3): new zombies appear
		//(step 4): player shoots zombies with arrows
					//NOTE: At STEP 4, if player is dead, BREAK from the loop.
		*/
		//(STEP 5 (additional, paoletti description)): "check round with next round", current round is incremented with each while loop.


		if (game.isMedianOn()) {
			std::cout << "At the end of round ..., median life is ...\n"; //for median. TODO: Implement/finish
		}
	}
	//NOTE: can implement everything w/o statistics and median, just do that afterwords (only implement w/ verbose, helps debugging)

	return 0;
}
