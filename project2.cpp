// 9504853406CBAC39EE89AA3AD238AA12CA198043

#include "Game.h"
#include <iostream>

int main (int argc, char** argv) {
	// Speeds up project's I/O
	std::ios_base::sync_with_stdio(false);

	Game game(argc, argv); //creates game object on the stack

	//TODO: Use getline, or whatever, to skip the first line comment. Try a small vim folder to make sure this works.
	


	//TODO: Read in preliminary game info (quiver_capacity, random_seed, max_rand_dist/speed/health



	//NOTE: This while loop is made to go per-round
	//cin.fail (no more rounds) && all zombies dead (active list is empty)
	while (!std::cin.fail() && !game.allZombiesDead()) {
		//start new round
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

		//STEPS LAID OUT IN SPEC:
		//(step 1): player refills quiver so it contains quiver_capacity arrows
		//(step 2): existing zombies move toward the player and attack if they have reached the player
		//(step 3): new zombies appear
		//(step 4): player shoots zombies with arrows
					//NOTE: At STEP 4, if player is dead, BREAK from the loop.

		//(STEP 5 (additional, paoletti description)): "check round with next round", current round is incremented with each while loop.
	}
	//NOTE: can implement everything w/o statistics and median, just do that afterwords (only implement w/ verbose, helps debugging)

	return 0;
}
