#ifndef TROOP_H
#define TROOP_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsScene>
#include "health.h"

class Troop :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Troop();
    bool remove;
    void stop();
    qreal speed;

bool stopped = false;

private:
    QTimer* m_timer;
    Health* health;

};

#endif // TROOP_H
