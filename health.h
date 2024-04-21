#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QObject>

class Health : public QObject
{
    Q_OBJECT

public:
    Health();

    int getHealth() const;
    int getMaxHealth() const;

public slots:
    void setMaxHealth(int newMaxHealth);
    void decrementHealth();
    void incrementHealth();


private:
    int maxHealth_;
    int health_;
};

#endif // HEALTH_H
