#ifndef TOWNHALL_H
#define TOWNHALL_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include "health.h"

class Townhall: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Townhall( QPixmap pixmap);
    void upgrade();
    void townhallAttacked();
    bool getStatus();
private:
    Health* health;
    bool destroyed;
};


#endif // TOWNHALL_H

/*OLD CODE*/
// #ifndef TOWNHALL_H
// #define TOWNHALL_H

// #include <QDialog>
// #include <QObject>
// #include <QGraphicsItem>
// #include <QPainter>
// #include <QImage>
// #include "health.h"

// namespace Ui {
// class TownHall;
// }

// class TownHall : public QDialog, public QGraphicsItem
// {
//     Q_OBJECT

// public:
//     explicit TownHall(QWidget *parent = nullptr);
//     ~TownHall();

//     void reduceHealth();
//     void move();
//     void upgrade();

// protected:
//     QRectF boundingRect() const override;
//     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

// private:
//     Ui::TownHall *ui;
//     Health *health;
// };

// #endif // TOWNHALL_H
