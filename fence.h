#ifndef FENCE_H
#define FENCE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPushButton>
#include <QPixmap>
#include <health.h>
#include <QGraphicsPixmapItem>
#include <QObject>
class Fence:  public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Fence();
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
