#include "workers.h"

#include <QTimer>
#include <QList>
#include <QGraphicsScene>
#include <QGraphicsPathItem>
#include <QtMath>

Workers::Workers(): isDestroyed(false)
{
    QPixmap workerImage(":/images/Worker.png");
    setPixmap(workerImage.scaled(30, 30));

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(rebuildStructure()));
    timer->start(100);
}


void Workers::showWorker()
{
    setVisible(true);
}

void Workers::hideWorker()
{
    setVisible(false);
}

void Workers::rebuildStructure(QPointF targetPoint)
{
    if (!isDestroyed)// Check if there is something destroyed

    {
        hideWorker();
        return;
    }

    showWorker();

    // targetPosition = targetPoint;

    // QList<QGraphicsItem*> obstacles = scene()->items(); //path to the destroyed object
    // qreal shortestPath = std::numeric_limits<qreal>::max();
    // qreal currentPath;

    // foreach (QGraphicsItem* obstacle, obstacles)
    // {
    //     if (obstacle != this && obstacle->type() == QGraphicsPathItem::Type)
    //     {
    //         currentPath = qSqrt(qPow(targetPosition.x() - obstacle->pos().x(), 2) +
    //                             qPow(targetPosition.y() - obstacle->pos().y(), 2));

    //         if (currentPath < shortestPath)
    //         {
    //             shortestPath = currentPath;
    //         }
    //     }
    // }

    // if (shortestPath != std::numeric_limits<qreal>::max())
    // {
    //     setPos(mapToParent(shortestPath, 0));
    // }

    // if (pos() == targetPosition)
    // {
    //     //stuff

    //     targetPosition = QPointF();
    //     isDestroyed = false;
    //     hideWorker();
    // }
}
