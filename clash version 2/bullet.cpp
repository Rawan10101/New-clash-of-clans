#include "bullet.h"
#include "troop.h"
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QGraphicsScene>

Bullet::Bullet()
{
    //bullet picture
    QPixmap pixmap1(":/images/cannonball.png");
    pixmap1 = pixmap1.scaledToWidth(10); //adjust size later
    pixmap1 = pixmap1.scaledToHeight(10);
    this->setPixmap(pixmap1);

    //to move
    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this,SLOT (move()));
    timer->start(50);
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

    //handling movement in x
    if (x() > directionX) //it should move to the left
    {
        this->setPos(x()-10, y());
    }
    else
        if (x() < directionX) //it should move to the right
        {
            this->setPos(x()+10, y());
        }

    //handling movement in y
    if (y() > directionY) //it should move up
    {
        this->setPos(x(), y()-10);
    }
    else
        if (y() < directionY) //it should move down
        {
            this->setPos(x(), y()+10);
        }

    //remove bullet when it goes out of bounds
        if(y() < 0 || y() > 600 || x() < 0 || x() > 800)
        {
            scene()->removeItem(this);
            delete this;
        }

}


/*NOTES*/
//adjust size of bullet
//adjust timer
//handle collision with enemy
//handle money/scoring
//add sound



/*OLD CODE*/
// Bullet::Bullet()
//     : directionX(0),
//     directionY(0),
//     speed(5.0)
// {
//     setFlag(QGraphicsItem::ItemIsFocusable);
// }


    // qreal dx = directionX * speed;
    // qreal dy = directionY * speed;
    // setPos(mapToParent(dx, dy));


// bool Bullet::collidesWithEnemy()
// {
//     return false;
// }

// QRectF Bullet::boundingRect() const
// {
//     return QRectF(-5, -5, 10, 10);
// }

// void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
// {
//     Q_UNUSED(option);
//     Q_UNUSED(widget);

//     painter->setBrush(Qt::red);
//     painter->drawEllipse(boundingRect());
// }
