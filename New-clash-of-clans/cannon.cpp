#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QDialog>
#include "cannon.h"
#include "bullet.h"
#include "health.h"
#include <QGraphicsRectItem>
#include <QTimer>

Cannon::Cannon()
{
   QPixmap pixmap(":/images/Cannon.png");
   pixmap = pixmap.scaledToWidth(100);
   pixmap = pixmap.scaledToHeight(100);
   this->setPixmap(pixmap);

   // remove=false;
}

// void Cannon::upgrade()
// {
// }
