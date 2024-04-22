#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QObject>

class Bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:

    Bullet(qreal mouseX, qreal mouseY, qreal cannonX, qreal cannonY);
    void setDirection(int x, int y);
    qreal speed;

public slots:
    void move();
    void setDirection(qreal x, qreal y);

private:
    qreal directionX;
    qreal directionY;
    qreal mouseX,  mouseY,  cannonX,  cannonY;
};

#endif // BULLET_H
