#include "health.h"

using namespace std;
Health::Health()
{
    maxHealth = 10;
    health = maxHealth;
}

int Health::getHealth() {
    return health;
}

int Health::getMaxHealth() {
    return maxHealth;
}

void Health::setMaxHealth(int newMaxHealth) {
    maxHealth = newMaxHealth;

}

void Health::decrementHealth() {
    health--;
}

void Health::incrementHealth() {
    health++;
}
