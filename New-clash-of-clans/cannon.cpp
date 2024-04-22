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

   // health->setMaxHealth(10); // Set the max health of the cannon
   QPixmap pixmap(":/images/Cannon.png");
   pixmap = pixmap.scaledToWidth(100);
   pixmap = pixmap.scaledToHeight(100);
   this->setPixmap(pixmap);

   remove=false;
}

// int Cannon::reduceHealth(){
//     return health->getHealth()-1;
// }


// void Cannon::upgrade()
// {
//     health->setMaxHealth(health->getMaxHealth() * 1.5); // Increase max health by 1.5 every upgrade
  // Set health back to max health
// }
