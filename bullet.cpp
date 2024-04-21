#include "bullet.h"
#include "troop.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QDebug>
#include <QtMath>

Bullet::Bullet(qreal mouseX, qreal mouseY, qreal cannonX, qreal cannonY)
{
    this -> mouseX = mouseX;
    this -> mouseY = mouseY;
    this -> cannonX = cannonX;
    this -> cannonY = cannonY;
    QPixmap pixmap1(":/images/cannonball.png");
    pixmap1 = pixmap1.scaledToWidth(30); // Adjust size later
    pixmap1 = pixmap1.scaledToHeight(30);
    setPixmap(pixmap1);
    speed = 5; // Adjust the speed as needed

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(30); // Adjust the timer interval as needed

    qDebug() << "Inside constructor";
}

void Bullet::setDirection(qreal x, qreal y)
{
    // Calculate the direction vector from the current bullet position to the target position
    qreal dx = x - this->x();
    qreal dy = y - this->y();

    // Normalize the direction vector to ensure constant speed
    qreal length = qSqrt(dx * dx + dy * dy);
    directionX = dx / length;
    directionY = dy / length;
}

void Bullet::move()
{
    qreal dx = mouseX - cannonX;
    qreal dy = mouseY - cannonY;
    qreal length = qSqrt(dx * dx + dy * dy);
    qreal x_inc = dx / length;
    qreal y_inc = dy / length;
    // Move the bullet along its direction vector
    //qreal dx = directionX * speed;
    //qreal dy = directionY * speed;
    // qDebug() << dx; // Debug statement
    // qDebug() << dy; // Debug statement

    setPos(x() + x_inc*speed, y() + y_inc*speed);

    // Remove the bullet when it goes out of bounds
    if (y() < 0 || y() > scene()->height() || x() < 0 || x() > scene()->width())
    {
        scene()->removeItem(this);
        delete this;
    }
}
