// 9504853406CBAC39EE89AA3AD238AA12CA198043

#ifndef GAME_H
#define GAME_H

#include "Zombie.h"
#include "Median.h"
#include "Stats.h"

#include <cstdint>
#include <iostream>
#include <getopt.h>
#include <deque>
#include <queue> //for std::priority_queue
#include <string>

class Game {
private:
    //input handling vars
    int _argc;
    char ** _argv; 
    bool _verbose_flag;
    bool _stats_flag;
    bool _median_flag;
    bool _player_is_dead_flag;
    size_t _stats_arg; //size_t (instd. of uint32_t) for AG wError. 

    //game info (set from setGameInfo())
    std::string _junk;
    uint32_t _quiver_capacity;
    uint32_t _rand_seed;
    uint32_t _max_rand_dist;
    uint32_t _max_rand_speed;
    uint32_t _max_rand_health;

    //player info
    uint32_t _quiver_load;
    Zombie* _zombie_that_killed_player;

    //OutputMode _output_mode; //to remove
    //WARNING: Because of the way deque manages dynamic memory, make sure to use DEQUE for the Zombie objects, and NOT vector. 
    //          1) Master zombie list! -> Deque?
    std::deque<Zombie*> _master_deque; //deque bc it's dynamic & doesn't reallocate memory addresses (it uses "chunks")
    //          2) Active list! (Alive) -> PQ?
    std::priority_queue<Zombie*, std::vector<Zombie*>, ZombieComparator> _active_queue; 
    //          3) Inactive List (Dead) (no need for Inactive list)
    std::deque<Zombie*> _inactive_deque; //stores front->back = first-killed->last-killed. Pushes killed zombies to back.
                        //making inactive list anyways, even though suboptimal memory. Need to get this done before optimizing. 
                                         //mainly used for first/last killed list. (STATS mode)
                                            //plan: - When printing first zombies killed, loop & print/pop 
        //make seperate classes for STATS and MEDIAN. STATS should have 2 deques with size of stats input arg int. 

public:
    Game(int argc, char** argv); //default constructor 
    //TODO implement function to setGameInfo (quiver capacity, seed, max rand ___)
    bool isVerboseOn() const;
    bool isStatsOn() const;
    bool isMedianOn() const;
    void setGameInfo(); //TODO: Implement
    void refillQuiver();
    void moveZombies();//NOTE: This also increments "rounds active" for each active zombie. Should move ea. active Zombie for the round, even if you die.
    void pushToMasterList(Zombie* zombie);
    void pushToActiveList(Zombie* zombie);
    //void shootZombies(); //uses quiver_load
    void shootZombies(Median* median);
    void deleteZombies(); //deletes all Zombie ptrs that were created on the heap! Remember to do this!
    void printOutput();//prints output according to input option flags. //TODO: Implement
    void setPlayerIsDeadFlag(); //sets flag to true. To be used when player dies (any zombie has dist=0 after moving.)
    bool isPlayerDead() const; //returns if _player_is_dead_flag is set to true or false. 
    bool areZombiesActive() const; //returns true if active_list is empty
    uint32_t getRandSeed() const;
    uint32_t getMaxDist() const; //ORDER SHOULD ALWAYS BE: Dist, Speed, Health
    uint32_t getMaxSpeed() const;
    uint32_t getMaxHealth() const;
    size_t getStatsArg() const;
    size_t getNumZombiesStillActive() const;
    std::priority_queue<Zombie*, std::vector<Zombie*>, ZombieComparator> getActiveZombies();
    const std::deque<Zombie*>& getInactiveZombies() const;
    const std::deque<Zombie*>& getAllZombies(); //for stats use: most/least active output.
    std::string getNameOfZombieThatKilled() const;
    std::string getNameOfLastZombie() const;
    //============================================================================
    //FOR DEBUGGING (START) ==============================================
    void printMasterDeque() const;
    //FOR DEBUGGING (END) ================================================
};

#endif // GAME_H