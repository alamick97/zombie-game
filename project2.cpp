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

		//NOTE: if condition for 
		//(step 1):
		//(step 2):
		//(step 3):
		//(step 4): if you are dead, BREAK from loop.
		//(step 5):
		//if dead break out (step 4)
	}
	//NOTE: can implement everything w/o statistics and median, just do that afterwords

	// Testing==========BEGIN===================================================
	// Testing==========END=====================================================

	return 0;
}
