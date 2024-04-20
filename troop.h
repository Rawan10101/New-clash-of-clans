#ifndef TROOP_H
#define TROOP_H

#include <QDialog>
#include <QObject>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include "townhall.h"
#include "workers.h"


class Troop : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

    QTimer* timer = new QTimer();
QTimer* timer5 = new QTimer();

public:
    Troop();


public slots:
    void move();
    //void castle_collision(Townhall* castle);
};

#endif // TROOP_H


