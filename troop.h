// troop.h

#ifndef TROOP_H
#define TROOP_H

#include <QGraphicsPixmapItem>
#include <QObject> // Add this line
#include <QGraphicsScene>
#include<health.h>
class Troop :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT // Add this macro

public:
    Troop();
    bool remove;
    void stop();
    qreal speed;

bool stopped = false;
public slots:
 //   void move();

private:
   // QGraphicsScene* scene;
    QTimer* m_timer;
    Health* health;

};

#endif // TROOP_H
