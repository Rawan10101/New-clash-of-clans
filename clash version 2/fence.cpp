
#include "fence.h"
#include "troop.h"
#include <QTimer>
#include <QList>
#include <QDebug>
#include "globalvariables.h"
#include <QPixmap>
#include<QObject>
#include<QGraphicsScene>
#include <globalvariables.h>
#include<game.h>
Fence::Fence(QPixmap pixmap)
    //: collisionCount(0), collisionTimerCount(0), upgradeCost(20)
{

    setPixmap(pixmap);
   //  health = new Health(NULL);
  // health->setMaxHealth(10); // adjust max health later
    //health->updateHealthBar();

   //health = new Health(NULL); //Pass the correct parameter

    fenceImage.load(":/images/fence.png");
   upgradedFenceImage.load(":/images/upgraded_fence.png");

   //upgradeButton = new QPushButton("Upgrade", nullptr);
   // upgradeButton->setFixedSize(80, 30);
   // upgradeButton->setVisible(false);

   //connect(upgradeButton, &QPushButton::clicked, this, &Fence::onUpgradeButtonClicked);

    //QTimer* timer = new QTimer(this);
  //connect(timer, SIGNAL(timeout()), this, SLOT(move()));
   // timer->start(50);
}

void Fence::setPixmap(const QPixmap& pixmap) {
    fenceImage=pixmap;
}
 void Fence::decreaseHealth()
 {/*
  health->decrementHealth();

     if (health->getHealth() <= 0)
   {
        delete this;
     }
*/
 }

 void Fence::upgrade()
 { /*
     if (upgradeCost <= 20) {  // Assuming playerMoney is a variable that holds the player's available money
         health->setMaxHealth(health->getMaxHealth()*1.5); //increase max health by 1.5 every upgrade
         health->setHealth(health->getMaxHealth()); //sets health back to max health
      fenceImage = upgradedFenceImage;
         upgradeButton->setVisible(false);
         qDebug() << "Fence upgraded!";
     } else {
         qDebug() << "Insufficient funds to upgrade the fence!";
     }
  */
  }



 void Fence::onUpgradeButtonClicked()
 {
   // upgrade();
 }


