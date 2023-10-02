// 9504853406CBAC39EE89AA3AD238AA12CA198043

#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <iostream>
#include <string>

class Zombie {
private:
    std::string _name;
    uint32_t _distance;
    uint32_t _speed;
    uint32_t _health;

public:
    Zombie(std::string name, uint32_t distance, uint32_t speed, uint32_t health) 
        : _name(name), _distance(distance), _speed(speed), _health(health) {} //order: name, distance, speed, health. Speed and health must be greater than 0. 

    std::string getName() const;
    float getETA() const; //for comparator use
    uint32_t getHealth() const;

};

struct ZombieComparator;

#endif //ZOMBIE_H