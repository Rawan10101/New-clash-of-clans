/*
#ifndef TOWER_H
#define TOWER_H

#include <QObject>
#include <QGraphicsRectItem>
#include "health.h"
class Tower : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit Tower(QObject *parent = nullptr);

    int getHealth() const;
    void decreaseHealth();
    void upgrade();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private slots:
    void move();

private:
    Health* health1;
    QImage towerImage;
};

#endif // TOWER_H
*/
