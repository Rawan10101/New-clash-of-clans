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
    Bullet(qreal mouseX, qreal mouseY, qreal cannonX, qreal cannonY);

    void setDirection(int x, int y);
    qreal speed;
public slots:
    void move();
    //bool collidesWithEnemy();
    void setDirection(qreal x, qreal y);

protected:
           //QRectF boundingRect() const override;
           //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    qreal directionX;
    qreal directionY;
    qreal mouseX,  mouseY,  cannonX,  cannonY;
    //qreal speed;
};

#endif // BULLET_H
