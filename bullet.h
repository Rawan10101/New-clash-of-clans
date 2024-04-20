#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QObject>
//#include <QPainter>

class Bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bullet();

    void setDirection(int x, int y);
    void move();
    //bool collidesWithEnemy();

protected:
    //QRectF boundingRect() const override;
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    int directionX;
    int directionY;
    //qreal speed;
};

#endif // BULLET_H
