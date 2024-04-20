#ifndef FENCE_H
#define FENCE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPushButton>
#include <QPixmap>
#include <health.h>
#include <QGraphicsPixmapItem>
#include <QObject>
class Fence: public QGraphicsPixmapItem
{

public:
    Fence(QPixmap pixmap);
    void setPixmap(const QPixmap& pixmap);
    void decreaseHealth();
    void upgrade();
    void onUpgradeButtonClicked();

private:
    QPixmap fenceImage;
    QPixmap upgradedFenceImage;
    QPushButton* upgradeButton;
    int upgradeCost;
   // Health* health;
};

#endif // FENCE_H
