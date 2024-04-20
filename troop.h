#ifndef TROOP_H
#define TROOP_H

#include <QDialog>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <health.h>
#include <cannon.h>
#include <townhall.h>
#include<QTimer>
class Troop : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Troop();

    void collide();
protected:


private:
    int collisionCount;
    int collisionTimerCount;
    Health* health;
    Cannon* cannon;
   // int upgradeCost;
    Townhall* castle;
    QTimer* collisionTimer;
    QTimer* moveTimer;
};


#endif // TROOP_H
