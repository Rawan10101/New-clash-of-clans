 #ifndef PLAYER_H
 #define PLAYER_H

#include <QDialog>
#include "cannon.h"
#include <QWidget>
#include <QGraphicsScene>

class Player : public QWidget
{
    Q_OBJECT
public:
    explicit Player(QWidget *parent = nullptr);
    ~Player();

    void setScene(QGraphicsScene *gameScene);

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    bool isCannonSelected;
    QGraphicsScene *scene;
     Cannon *cannon;

    void selectCannon(const QPoint &position);
    void shootCannon(const QPoint &targetPosition);
};

#endif // PLAYER_H
