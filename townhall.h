#ifndef TOWNHALL_H
#define TOWNHALL_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include "health.h"

class Townhall: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Townhall( );
    void upgrade();
    void townhallAttacked();
    bool getStatus();
    void reduceHealth();
    int getHealth();
    bool remove;
private:
    Health* health;
    bool destroyed;
};


#endif // TOWNHALL_H
