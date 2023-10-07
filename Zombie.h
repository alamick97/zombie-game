// 9504853406CBAC39EE89AA3AD238AA12CA198043

#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <iostream>
#include <string>

class Zombie {
private:
    std::string _name; //must have name.
    uint32_t _distance; //can be >= 0. (so, init dist can be 0.)
    uint32_t _speed; //must be >0
    uint32_t _health;//must be >0
    uint32_t _rounds_active; //must be init to 0.

public:
    Zombie(std::string name, uint32_t distance, uint32_t speed, uint32_t health) 
        : _name(name), _distance(distance), _speed(speed), _health(health) {
            _rounds_active = 0;
    } //order: name, distance, speed, health. Speed and health must be greater than 0. 

    void setDistance(uint32_t newDistance);
    void setHealth(uint32_t newHealth);
    void incrementRoundsActive();

    std::string getName() const;
    uint32_t getDistance() const;
    uint32_t getSpeed() const;
    float getETA() const; //for comparator use
    uint32_t getHealth() const;
};

struct ZombieComparator;

#endif //ZOMBIE_H