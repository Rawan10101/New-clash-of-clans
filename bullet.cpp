#include "bullet.h"
#include "troop.h"
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <qmath.h>
#include <QtMath>
Bullet::Bullet()
{

    QPixmap pixmap1(":/images/cannonball.png");
    pixmap1 = pixmap1.scaledToWidth(30); //adjust size later
    pixmap1 = pixmap1.scaledToHeight(30);
    this->setPixmap(pixmap1);
    speed=0.25;
    //to move

    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this,SLOT (move()));
    timer->start(90);
    qDebug()<<"inside constructor";

}

void Bullet::setDirection(int x, int y) //receives target position from cannon
{
    directionX = x;
    directionY = y;
}

void Bullet::move()
{

    // handling collision with enemy
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; i++)
    {
        if (typeid(*(colliding_items[i])) == typeid(Troop))
        {
            //call function for when enemy is hit from enemy troop class
            scene()->removeItem(this);
            delete this;
            //update score / increase player's money
            //sound
            return;
        }
    }

    qDebug()<<" inside move";
    /*//handling movement in x
    if (x() >= directionX) //it should move to the left
    {
        this->setPos(x()-10, y());
    }
    else
        if (x() <= directionX) //it should move to the right
        {
            this->setPos(x()+10, y());
        }

    //handling movement in y
    if (y() >= directionY) //it should move up
    {
        this->setPos(x(), y()-10);
    }
    else
        if (y() <= directionY) //it should move down
        {
            this->setPos(x(), y()+10);
        }*/

    qreal dx = directionX * this->speed;
    qreal dy = directionY * this->speed;

    if(directionX > x() && directionY > y())
    {
        this->setPos(x() + dx, y() + dy);
    }
    else if(directionX > x() && directionY < y())
    {
        this->setPos(x() + dx, y() - dy);
    }
    else if (directionX < x() && directionY > y())
    {
        this->setPos(x() - dx, y() + dy);
    }
    else if (directionX < x() && directionY < y())
    {
        this->setPos(x() - dx, y() - dy);
    }


    //remove bullet when it goes out of bounds
    if(y() < 0 || y() > scene()->height() || x() < 0 || x() > scene()->width() || (x() == directionX && y() == directionY))
    {
        qDebug() << "remove";
        scene()->removeItem(this);
        delete this;
    }

}


