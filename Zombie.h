// 9504853406CBAC39EE89AA3AD238AA12CA198043

#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <cstdint>
#include <iostream>
#include <string>

class Zombie {
private:
    std::string _name; //must have name.
    uint32_t _distance; //can be >= 0. (so, init dist can be 0.)
    uint32_t _speed; //must be >0
    uint32_t _health;//must be >0
    uint32_t _rounds_active; //init to 1.

public:
    Zombie(std::string name, uint32_t distance, uint32_t speed, uint32_t health) 
        : _name(name), _distance(distance), _speed(speed), _health(health) {
            _rounds_active = 1;
    } //order: name, distance, speed, health. Speed and health must be greater than 0. 

    void setDistance(uint32_t newDistance);
    void setHealth(uint32_t newHealth);
    void incrementRoundsActive();
    void printCreated() const;
    void printMoved() const;
    void printDestroyed() const;

    std::string getName() const;
    uint32_t getDistance() const;
    uint32_t getSpeed() const;
    uint32_t getETA() const;
    uint32_t getHealth() const;
    uint32_t getRoundsActive() const;
};

struct ZombieComparator {
    bool operator()(const Zombie* z1, const Zombie* z2) {
        uint32_t eta1 = z1->getETA();
        uint32_t eta2 = z2->getETA();
        if (eta1 != eta2) { return eta1 > eta2; }
        //if (eta1 > eta2) { return true; } //first, compare ETAs
        //else if (eta1 < eta2) { return false; } //this is probably wrong. we dont return false, we go to the next criteria.

        uint32_t health1 = z1->getHealth();
        uint32_t health2 = z2->getHealth();
        if (health1 != health2) { return health1 > health2; }
        //if (health1 > health2) { return true; } //second, compare health
        //else if (health1 < health2) { return false; } //this is probably also wrong. we dont return false, we go to the next criteria.

        return z1->getName() > z2->getName(); //thirdly and lastly, compare names lexicographically
    }
};

struct MostActiveComparator { //for stats, N most active zombies
    bool operator()(const Zombie* z1, const Zombie* z2) const {
        uint32_t rounds1 = z1->getRoundsActive();        
        uint32_t rounds2 = z2->getRoundsActive();        
        if (rounds1 != rounds2)  { return rounds1 < rounds2; }

        return z1->getName() > z2->getName();
    }
};
struct LeastActiveComparator { //for stats, N least active zombies
    bool operator()(const Zombie* z1, const Zombie* z2) const {
        uint32_t rounds1 = z1->getRoundsActive();        
        uint32_t rounds2 = z2->getRoundsActive();        
        if (rounds1 != rounds2)  { return rounds1 > rounds2; }

        return z1->getName() > z2->getName();
    }
};

#endif //ZOMBIE_H