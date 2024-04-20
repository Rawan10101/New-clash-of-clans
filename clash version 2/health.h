#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>

class Health : public QObject
{
    Q_OBJECT

public:
    Health(QGraphicsScene* scene);

    int getHealth() const;
    int getMaxHealth() const;

public slots:
    void setHealth(int newHealth);
    void setMaxHealth(int newMaxHealth);
    void decrementHealth();
    void incrementHealth();
   // void updateHealthBar();

private:
    QGraphicsScene* scene_;
    QGraphicsRectItem* baseRect_;
    QGraphicsRectItem* rect2_;
    int maxHealth_;
    int health_;
};

#endif // HEALTH_H
