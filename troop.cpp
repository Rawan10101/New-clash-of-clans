#include "troop.h"
#include "fence.h"
#include "townhall.h"
#include <QRandomGenerator>
#include <QDebug>
#include<QTimer>
#include "troop.h"
#include "health.h"
#include "townhall.h"
#include "fence.h"
#include "cannon.h"
#include <stdlib.h>
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include <QPushButton>
#include <QCoreApplication>
#include <iostream>
//#include <QDateTime>
#include <QRandomGenerator>
#include<QObject>
#include <QMetaObject>

Troop::Troop() {
    // Load enemy troop picture
    QPixmap picture(":/images/Barbarian1.png");
    picture = picture.scaledToHeight(40);
    picture = picture.scaledToWidth(40);
    this->setPixmap(picture);
    remove=false;
     speed = 1.0;
    // Create and start the 5-minute timer
    QTimer::singleShot(5 * 60 * 1000, [=]() {
        // Handle timer timeout (5 minutes elapsed)
        qDebug() << "5-minute timer finished";
    });


    m_timer = new QTimer(nullptr);
    connect(m_timer,SIGNAL(timeout()),this,SLOT (move()));

   health= new Health();
}
void Troop::stop() {
    stopped = true;
}

 /*
void Troop::move() {
    // Generate a random number to control movement
    int num = QRandomGenerator::global()->bounded(7);

    // Move the troop diagonally towards the middle
    this->setPos(x() + num, y() + num);

    // Check for collisions with fences or townhalls
    QList<QGraphicsItem*> colliding_items = collidingItems();
  //  while(){
    for (int i = 0; i < colliding_items.size(); ++i) {
        if (typeid(*(colliding_items[i])) == typeid(Cannon)) {
            if(Cannon.reduceHealth()<=0){
                   delete colliding_items[i];
                  scene()->removeItem(colliding_items[i]);
            }

        }

            if( typeid(*(colliding_items[i])) == typeid(Townhall) && health->getHealth()>=0) {
            if(Townhall.reduceHealth()<=0){
                delete colliding_items[i];
                  scene()->removeItem(colliding_items[i]);
            }
            }
                if (typeid(*(colliding_items[i])) == typeid(Fence)){

                if(Fence.reduceHealth()<=0){
                    delete colliding_items[i];
                      scene()->removeItem(colliding_items[i]);
                }
     }
           if(health->getHealth()==0){
               delete colliding_items[i];

           //}
*/



// const QMetaObject* Troop::metaObject() const {
//     return &static_cast<const QObject*>(this)->staticMetaObject;
// }

// void* Troop::qt_metacast(const char* name) {
//     if (!strcmp(name, "Troop"))
//         return static_cast<Troop*>(this);
//     return QObject::qt_metacast(name);
// }

// int Troop::qt_metacall(QMetaObject::Call call, int id, void** args) {
//     if (call == QMetaObject::InvokeMetaMethod) {
//         if (id < 0)
//             return -1;
//         if (id == 0)
//             move();
//     }
//     return QObject::qt_metacall(call, id, args);
// }
