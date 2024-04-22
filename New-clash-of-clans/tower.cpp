// #include "tower.h"
// #include "player.h"
// #include "troop.h"
// #include <QTimer>
// #include <QGraphicsScene>
// #include <QList>
// #include <QPainter>
// #include "health.h"

// Tower::Tower(QObject *parent)
//     : QObject(parent), QGraphicsRectItem()
// {
//     setRect(0, 0, 10, 50);
//     health1=new Health;
//    // towerImage.load(":/images/tower");

//     QTimer* timer = new QTimer(this);
//     connect(timer, SIGNAL(timeout()), this, SLOT(move()));
//     timer->start(50);
// }





// void Tower::upgrade()
// {

// }

// void Tower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
// {
//     painter->drawImage(rect(), towerImage);
//     qreal width = rect().width() * health1->getHealth() / 6.0;
//     QRectF healthBarRect(rect().topLeft(), QSizeF(width, 5));
//     painter->fillRect(healthBarRect, Qt::green);
// }

// void Tower::move()
// {
//     QList<QGraphicsItem*> collidingItemsList = collidingItems();
//     for (int i = 0; i < collidingItemsList.size(); i++)
//     {
//         if (typeid(*(collidingItemsList[i])) == typeid(Troop) && health1->getHealth() > 0)
//         {
//             health1->decrementHealth();

//             delete collidingItemsList[i];
//             return;
//         }
//     }
// }
