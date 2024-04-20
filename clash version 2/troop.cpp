#include "troop.h"
#include "health.h"
#include "townhall.h"
#include "fence.h"
#include <stdlib.h>
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include <QPushButton>
#include <QCoreApplication>
#include <iostream>
#include <QDateTime>
#include "workers.h"

Troop::Troop()

{
    //enemy troop picture
    //put picture in resource file

    QPixmap picture("/Users/mac/Clash0fClans1/images/enemy-jpg");
    picture = picture.scaledToHeight(40);
    picture = picture.scaledToWidth(40);
    this->setPixmap(picture);

    //the position where enemies will appear (random)
    int random_num = arc4random() % 700;
    this->setPos (random_num,0);

    // 5 minute timer
    bool timerFinished = 0;
    timerFinished = QDateTime::currentDateTime().toTime_t();
    if(QDateTime::currentDateTime().toTime_t() - timerFinished >= 5 * 60 * 1000) //5 mins in milliseconds
        timerFinished =true;

    //while statement will stop if time finished or castle is destroyed
    timer->start(100);

    while(!timerFinished && !getstatus()) // and random_number won't be inside the fence dimentions
    {
        connect(timer,SIGNAL(timeout()),this,SLOT (move()));

    }




}

void Troop:: move()
{
    //generating a random number
    int num=arc4random()% 7;
    // enemies move diagonally towards the middle
    this->setPos(x()+num,y()+num);
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; i++)
    {
        if (typeid(*(colliding_items[i])) == typeid(Fence)||typeid(*(colliding_items[i])) == typeid(Townhall))
        {
            //call function for when enemy collides with fence to stop moving
            disconnect(timer,SIGNAL(timeout()),this, SLOT(move()) );
            return;
        }
        //else continue moving
    }


}



//set position of the scene to start displaying the enemies outside of it.
