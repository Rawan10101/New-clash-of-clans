#include "fence1.h"

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
Fence1::Fence1()
{
    QPixmap pixmap(":/images/Wall.png");
    pixmap = pixmap.scaledToWidth(50); //adjust size later
    pixmap = pixmap.scaledToHeight(50);
    this->setPixmap(pixmap);
    remove=false;
}
int Fence1::reduceHealth(){
    return health->getHealth()-1;
}
Fence1::~Fence1()
{
   // delete ui;
}
