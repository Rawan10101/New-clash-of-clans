#include "health.h"
using namespace std;
Health::Health()
{

    maxHealth_= 10;

}

int Health::getHealth() const {
    return health_;
}

int Health::getMaxHealth() const {
    return maxHealth_;
}


void Health::setMaxHealth(int newMaxHealth) {
    maxHealth_ = newMaxHealth;

}

void Health::decrementHealth() {
    health_--;
}

void Health::incrementHealth() {
    health_++;
}
