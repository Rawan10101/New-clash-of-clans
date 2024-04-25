#include "troop.h"
#include "fence1.h"
#include "townhall.h"
#include "health.h"
#include "cannon.h"
#include <QRandomGenerator>
#include <QDebug>
#include<QTimer>
#include <stdlib.h>
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include <QPushButton>
#include <QCoreApplication>
#include <iostream>
#include <QRandomGenerator>
#include<QObject>

Troop::Troop() {

    QPixmap picture(":/images/Barbarian1.png");
    picture = picture.scaledToHeight(40);
    picture = picture.scaledToWidth(40);
    this->setPixmap(picture);
    remove=false;
     speed = 1.0;

    QTimer::singleShot(5 * 60 * 1000, [=]() { //5-minute timer
        qDebug() << "5-minute timer finished";
    });

    // m_timer = new QTimer(nullptr); //timer to move enemy troop
    // connect(m_timer,SIGNAL(timeout()),this,SLOT (move()));

   // health= new Health();
}

void Troop::stop() {
    stopped = true;
}
