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
int Cannon::reduceHealth(){
    return health->getHealth()-1;
}

void Cannon::upgrade()
{
    health->setMaxHealth(health->getMaxHealth() * 1.5); // Increase max health by 1.5 every upgrade
  // Set health back to max health
}

void Cannon::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        // Create a new bullet
        Bullet *bullet = new Bullet();
        bullet->setDirection(event->position().x(), event->position().y());
        bullet->setPos(x(), y()); // Set the position of the bullet at the position of the cannon
        scene()->addItem(bullet);
    }
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

//Notes:
//bullet movement handled in bullet class
//add the code to direct the cannon towards the firing location
//fix the paintEvent function
//figure out how much the health decreases every attack and handle it in the cannonAttacked function
//when cannon gets destroyed, display message to inform user that cannon has been destroyed
//add sound when cannon is destroyed









/*
 OLD CODE
 #include "cannon.h"

 Cannon::Cannon(QWidget *parent, QGraphicsScene* scene)
     : QDialog(parent),
       ui(new Ui::Cannon),
       scene(scene),
       health(new Health()),
       bullet(nullptr),
       bulletTimer(new QTimer(this)),
       bulletDirectionX(0),
       bulletDirectionY(0),
       bulletFired(false),
       bulletMoving(false)
 {

     setFocusPolicy(Qt::StrongFocus);

     Connect the bullet timer signal to the moveBullet slot
     connect(bulletTimer, SIGNAL(timeout()), this, SLOT(moveBullet()));
 }

 Cannon::~Cannon()
 {
     delete ui;
     delete health;
     delete bullet;
     delete bulletTimer;
 }

 void Cannon::decreaseHealth()
 {
     health->reduceHealth();

     if (health->getHealth() <= 0)
     {
         Cannon destroyed logic
     }
}

 void Cannon::upgrade()
 {
  Upgrade cannon logic
 }

 void Cannon::setBulletDirection(int x, int y)
 {
    bulletDirectionX = x;
     bulletDirectionY = y;
 }

 void Cannon::shootBullet()
 {
     if (!bulletFired && !bulletMoving)
     {
         bullet = new Bullet();
         bullet->setPos(x() + width() / 2, y());
         bullet->setDirection(bulletDirectionX, bulletDirectionY);
         scene->addItem(bullet);

         bulletMoving = true;
         bulletFired = true;

         bulletTimer->start(10);     }
 }

 void Cannon::paintEvent(QPaintEvent *event)
 {
     QDialog::paintEvent(event);

     QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
     painter.setBrush(Qt::gray);
     painter.setPen(Qt::black);
     painter.drawRect(rect());
     qreal width = rect().width() * health->getHealth() / 100.0;
     QRectF healthBarRect(rect().topLeft(), QSizeF(width, 10));
     painter.setBrush(Qt::green);
     painter.setPen(Qt::NoPen);
     painter.drawRect(healthBarRect);
 }

 void Cannon::keyPressEvent(QKeyEvent *event)
 {
     if (event->key() == Qt::Key_Left)
     {
         bulletDirectionX = -1;
     }
     else if (event->key() == Qt::Key_Right)
     {
         bulletDirectionX = 1;
     }
     else if (event->key() == Qt::Key_Up)
     {
         bulletDirectionY = -1;
     }
     else if (event->key() == Qt::Key_Down)
     {
         bulletDirectionY = 1;
     }
     else if (event->key() == Qt::Key_Space)
     {
         shootBullet();
     }

     event->accept();
 }

 void Cannon::keyReleaseEvent(QKeyEvent *event)
 {
     if (event->key() == Qt::Key_Left || event->key() == Qt::Key_Right)
     {
         bulletDirectionX = 0;
     }
    else if (event->key() == Qt::Key_Up || event->key() == Qt::Key_Down)
     {
         bulletDirectionY = 0;
     }

     event->accept();
 }

 void Cannon::moveBullet()
 {
     if (bulletMoving)
     {
         bullet->move();

         if (bullet->collidesWithEnemy())
         {
              Bullet hit an enemy logic
             bulletMoving = false;
             bulletTimer->stop();
             delete bullet;
         }
         else if (bullet->x() < 0 || bullet->x() > 800 || bullet->y() < 0 || bullet->y() > 800)
         {
             // Bullet reached the end of the screen logic
             bulletMoving = false;
             bulletTimer->stop();
             delete bullet;
         }
     }
}
*/
