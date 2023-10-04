// 9504853406CBAC39EE89AA3AD238AA12CA198043

#include "Zombie.h"

uint32_t Zombie::getHealth() const { return _health; }
std::string Zombie::getName() const { return _name; }
float Zombie::getETA() const { return static_cast<float>(_distance) / _speed; }


struct ZombieComparator {
    bool operator()(const Zombie* z1, const Zombie* z2) {
        float eta1 = z1->getETA();
        float eta2 = z2->getETA();
        if (eta1 < eta2) { return true; } //first, compare ETAs
        else if (eta1 > eta2) { return false; }

        uint32_t health1 = z1->getHealth();
        uint32_t health2 = z2->getHealth();
        if (health1 < health2) { return true; } //second, compare health
        else if (health1 > health2) { return false; }

        return z1->getName() < z2->getName(); //thirdly and lastly, compare names lexicographically




        float eta1 = z1->getETA();
        float eta2 = z2->getETA();
        if (eta1 != eta2) { return eta1 < eta2; } //first, compare ETAs

        uint32_t health1 = z1->getHealth();
        uint32_t health2 = z2->getHealth();
        if (health1 != health2) { return health1 < health2; } //second, compare health

        return z1->getName() < z2->getName(); //thirdly and lastly, compare names lexicographically
    }
};