// 9504853406CBAC39EE89AA3AD238AA12CA198043

#ifndef GAME_H
#define GAME_H

#include "Zombie.h"

#include <iostream>
#include <getopt.h>
#include <deque>
#include <queue> //for std::priority_queue


class Game {
private:
    //input handling vars
    int _argc;
    char ** _argv; 
    bool _verbose_flag;
    bool _stats_flag;
    bool _median_flag;
    uint32_t _stats_arg;

    //...
    uint32_t quiver_capacity;

    //OutputMode _output_mode; //to remove
    //TODO: Implement:
    //          1) Master zombie list! -> Deque?
    std::deque<Zombie> master_deque; //deque bc it's dynamic & doesn't reallocate memory addresses (it uses "chunks")
    //          2) Active list! (Alive) -> PQ?
    std::priority_queue<Zombie*, std::vector<Zombie*>, ZombieComparator> active_queue; 
    //          3) Inactive List (Dead) (no need for Inactive list)
        //make seperate classes for STATS and MEDIAN. STATS should have 2 deques with size of stats input arg int. 

    //need 2 other PQ's for Most (1 PQ) & Least (1 PQ) active
    /*when we find that the game has ended, */
public:
    Game(int argc, char** argv); //default constructor 
    
    //TODO implement function to setGameInfo (quiver capacity, seed, max rand ___)
    void setGameInfo();
    bool allZombiesDead() const; //returns true if active_list is empty
    void printOutput();//prints output according to input option flags.
};


#endif // GAME_H