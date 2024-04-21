#ifndef FENCE1_H
#define FENCE1_H

#include <QDialog>

#include <QGraphicsItem>
#include <QPainter>
#include <QPushButton>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QObject>
namespace Ui {
class Fence1;
}

class Fence1 : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Fence1();
    ~Fence1();
 //   void setPixmap(const QPixmap& pixmap);
   // void decreaseHealth();
   // void upgrade();
   // void onUpgradeButtonClicked();

private:
    QPixmap fenceImage;
    QPixmap upgradedFenceImage;
    QPushButton* upgradeButton;
    int upgradeCost;
};

#endif // FENCE1_H
