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
uint32_t Zombie::getETA() const { return _distance / _speed; }
uint32_t Zombie::getRoundsActive() const { return _rounds_active; }