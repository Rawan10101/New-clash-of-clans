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
    QPixmap pixmap("C:/Users/HP/Desktop/file1/Wall1.webp");
    pixmap = pixmap.scaledToWidth(50); //adjust size later
    pixmap = pixmap.scaledToHeight(50);
    this->setPixmap(pixmap);
}

Fence1::~Fence1()
{
   // delete ui;
}
