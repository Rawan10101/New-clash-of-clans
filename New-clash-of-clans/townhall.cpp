#include "townhall.h"
#include <QDebug>
Townhall::Townhall( )
{
    townhallHealth = new Health();
    //health->setMaxHealth(10);
    QPixmap pixmap(":/images/Castle.png");
    pixmap = pixmap.scaledToWidth(50);
    pixmap = pixmap.scaledToHeight(50);
    this->setPixmap(pixmap);
    qDebug() << "testing townhall";
    //health->updateHealthBar();
    remove=false;
    //destroyed = 0; //bool variable to indicate if townhall got destroyed
}

// int Townhall::reduceHealth(){
//     return (health->getHealth())-1;
// }
// void Townhall::upgrade() //function is called when user chooses to upgrade and they have enough money
// {
//     health->setMaxHealth(health->getMaxHealth()*1.5); //increase max health by 1.5 every upgrade
// }

// void Townhall::townhallAttacked() //to handle collision with enemy
// {
//     health->decrementHealth();
//     if (health->getHealth() <= 0) // is destroyed
//     {
//         destroyed = 1;
//         //delete this;
//         //update health bar
//         //message
//         //sound

//     }
// }

// bool Townhall::getStatus()
// {
//     return destroyed;
// }



