// 9504853406CBAC39EE89AA3AD238AA12CA198043

#include "Zombie.h"

void Zombie::setDistance(uint32_t newDistance) { _distance = newDistance; }
void Zombie::setHealth(uint32_t newHealth) { _health = newHealth; }
void Zombie::incrementRoundsActive() { _rounds_active++; }

void Zombie::printCreated () const {
	std::cout << "Created: " << _name;
	std::cout << " (distance: " << _distance;
	std::cout << ", speed: " << _speed;
	std::cout << ", health: " << _health << ")\n";
}
void Zombie::printMoved() const {
	std::cout << "Moved: " << _name;
	std::cout << " (distance: " << _distance;
	std::cout << ", speed: " << _speed;
	std::cout << ", health: " << _health << ")\n";
}

void Zombie::printDestroyed() const {
	std::cout << "Destroyed: " << _name;
	std::cout << " (distance: " << _distance;
	std::cout << ", speed: " << _speed;
	std::cout << ", health: " << _health << ")\n";
}

std::string Zombie::getName() const { return _name; }
uint32_t Zombie::getDistance() const { return _distance; }
uint32_t Zombie::getSpeed() const { return _speed; }
uint32_t Zombie::getHealth() const { return _health; }
//float Zombie::getETA() const { return static_cast<float>(_distance) / _speed; }
uint32_t Zombie::getETA() const { return _distance / _speed; }
uint32_t Zombie::getRoundsActive() const { return _rounds_active; }

struct ZombieComparator {
    bool operator()(const Zombie* z1, const Zombie* z2) {
        uint32_t eta1 = z1->getETA();
        uint32_t eta2 = z2->getETA();
        //float eta1 = z1->getETA(); //commented out because want uint32_t integer comparison
        //float eta2 = z2->getETA(); //commented out because want uint32_t integer comparison
        if (eta1 < eta2) { return true; } //first, compare ETAs
        else if (eta1 > eta2) { return false; }

        uint32_t health1 = z1->getHealth();
        uint32_t health2 = z2->getHealth();
        if (health1 < health2) { return true; } //second, compare health
        else if (health1 > health2) { return false; }

        return z1->getName() < z2->getName(); //thirdly and lastly, compare names lexicographically
    }
};

struct MostActiveComparator { //for stats, N most active zombies
    bool operator()(const Zombie* z1, const Zombie* z2) const {
        return z1->getRoundsActive() < z2->getRoundsActive();
    }
};
struct LeastActiveComparator { //for stats, N least active zombies
    bool operator()(const Zombie* z1, const Zombie* z2) const {
        return z1->getRoundsActive() > z2->getRoundsActive();
    }
};