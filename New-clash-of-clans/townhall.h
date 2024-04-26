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
    //void upgrade();
    //void townhallAttacked();
    //bool getStatus();
    //int reduceHealth();
    bool remove;
    Health* townhallHealth;

private:
    //bool destroyed;
};


#endif // TOWNHALL_H

