#include "troop.h"
#include "health.h"
#include "QPixmap"
#include <QGraphicsPixmapItem>

Troop::Troop()
{
    QPixmap pixmap1(":/images/cannonball.png");
    pixmap1 = pixmap1.scaledToWidth(10); // Adjust size later
    pixmap1 = pixmap1.scaledToHeight(10);
    this->setPixmap(pixmap1);

  //  health = new Health(NULL); // Initialize health for the troop

    // Create timers for troop movement and collision detection
    moveTimer = new QTimer(this);
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    moveTimer->start(100); // Set timer interval for troop movement

    collisionTimer = new QTimer(this);
    connect(collisionTimer, SIGNAL(timeout()), this, SLOT(collide()));
    collisionTimer->start(100); // Set timer interval for collision detection

    // Initialize collision counters
    collisionCount = 0;
    collisionTimerCount = 0;
}


void Troop::collide()
{

    QList<QGraphicsItem*> collidingItemsList = collidingItems();
    for (int i = 0; i < collidingItemsList.size(); i++)
    {
        if ((typeid(*collidingItemsList[i]) == typeid(cannon) && health->getHealth() > 0) ||
            (typeid(*collidingItemsList[i]) == typeid(castle) && health->getHealth() > 0))
        {

            collisionCount++;
            collisionTimerCount++;

            if (collisionCount >= 10 )
            {
            //  health->decrementHealth();
                collisionCount = 0;
                collisionTimerCount = 0;
            }


            if (health->getHealth() <= 0)
            {
           //     upgradeButton->setVisible(false);
            }
            else
            {
             //   upgradeButton->setVisible(true);
            }

            return;
        }
    }
    //  Reset the collision count if no collisions occur within 10 seconds
    if (collisionTimerCount >= 10)
    {
        collisionCount = 0;
        collisionTimerCount = 0;
    }

}
