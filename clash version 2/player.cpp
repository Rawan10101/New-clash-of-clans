#include "player.h"
#include <QGraphicsScene>
#include "cannon.h"
Player::Player(QWidget *parent) : QWidget(parent), isCannonSelected(false), cannon(nullptr), scene(nullptr)
{

}

Player::~Player()
{
    delete cannon;
}


void Player::mousePressEvent(QMouseEvent *event)
{
  cannon->mousePressEvent(event);
}

void Player::selectCannon(const QPoint &position)
{
    if (cannon) {
        delete cannon;
        cannon = nullptr;
    }

    cannon = new Cannon();
    cannon->setPos(position.x(), position.y());
    scene->addItem(cannon);
}

void Player::shootCannon(const QPoint &targetPosition)
{
    if (cannon) {
        cannon->setBulletDirection(targetPosition.x(), targetPosition.y());
        cannon->shootBullet();
    }
}
