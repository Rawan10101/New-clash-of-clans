#ifndef FENCE1_H
#define FENCE1_H

#include <QDialog>

#include <QGraphicsItem>
#include <QPainter>
#include <QPushButton>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QObject>
#include "health.h"

class Fence1 : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Fence1();
    ~Fence1();
    bool remove;
    Health* fenceHealth;
private:
    QPixmap fenceImage;
    QPixmap upgradedFenceImage;
    QPushButton* upgradeButton;
    int upgradeCost;
};

#endif // FENCE1_H
