#include "health.h"

Health::Health(QGraphicsScene* scene) :scene_(scene)
{

    maxHealth_= 10;
    baseRect_ = new QGraphicsRectItem(4, 4, maxHealth_/10, 20);
    rect2_ = new QGraphicsRectItem(5,5, maxHealth_/10, 20);

    // Set up the base rectangle
    QPen blackPen(Qt::black);
    blackPen.setWidth(3);
    QBrush grayBrush(Qt::gray);
    baseRect_->setPen(blackPen);
    baseRect_->setBrush(grayBrush);
    scene_->addItem(baseRect_);

    // Set up the health bar rectangle
    QBrush greenBrush(Qt::green);
    rect2_->setBrush(greenBrush);
    scene_->addItem(rect2_);

    //updateHealthBar();
}

int Health::getHealth() const {
    return health_;
}

int Health::getMaxHealth() const {
    return maxHealth_;
}

void Health::setHealth(int newHealth) {
    health_ = std::max(0, std::min(newHealth, maxHealth_));
    //updateHealthBar();
}

void Health::setMaxHealth(int newMaxHealth) {
    maxHealth_ = std::max(1, newMaxHealth);
    health_ = std::min(health_, maxHealth_);
    //updateHealthBar();
}

void Health::decrementHealth() {
    setHealth(health_ - 1);
}

void Health::incrementHealth() {
    setHealth(health_ + 1);
}
/*
void Health::updateHealthBar() {
    // Update the size and color of the health bar
    rect2_->setRect(rect2_->x(), rect2_->y(), health_/10, 20);

    QBrush brush;
    if (health_ <= maxHealth_/4) {
        brush = QBrush(Qt::red);
    } else if (health_ <= maxHealth_/2) {
        brush = QBrush(Qt::darkYellow);
    } else {
        brush = QBrush(Qt::green);
    }
    rect2_->setBrush(brush);
}
*/

