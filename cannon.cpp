#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
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
   pixmap = pixmap.scaledToWidth(100); //adjust size later
   pixmap = pixmap.scaledToHeight(100);
    this->setPixmap(pixmap);
   remove=false;
}
void Cannon::reduceHealth(){
   health->getHealth()-1;
}
int Cannon::getHealth(){
    return health->getHealth();
}

void Cannon::upgrade()
{
    health->setMaxHealth(health->getMaxHealth() * 1.5); // Increase max health by 1.5 every upgrade

}


void Cannon::cannonAttacked()
{
    health->decrementHealth();
    if (health->getHealth() <= 0)
    {
        // Cannon is destroyed
        scene()->removeItem(this);
        delete this;
        // Update health bar
        //health->updateHealthBar();
        // Display message
        // Play sound
    }
}
/*
void Cannon::setBulletDirection(int x, int y)
{
    bulletDirectionX = x;
    bulletDirectionY = y;
}

void Cannon::shootBullet()
{
    Bullet *bullet = new Bullet();
    bullet->setPos(x() + pixmap().width() / 2, y());
    bullet->setDirection(bulletDirectionX, bulletDirectionY);
    scene()->addItem(bullet);
    bulletMoving = true;
    bulletFired = true;

    bulletTimer->start(10);
}
*/


//Notes:
//bullet movement handled in bullet class
//add the code to direct the cannon towards the firing location
//fix the paintEvent function
//figure out how much the health decreases every attack and handle it in the cannonAttacked function
//when cannon gets destroyed, display message to inform user that cannon has been destroyed
//add sound when cannon is destroyed








