#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QObject>

class Health : public QObject
{
    Q_OBJECT

public:
    Health();

    int getHealth();
    int getMaxHealth();
    void setMaxHealth(int newMaxHealth);
    void decrementHealth();
    void incrementHealth();


private:
    int maxHealth;
    int health;
};

#endif // HEALTH_H
