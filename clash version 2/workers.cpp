#include "workers.h"

#include <QTimer>
#include <QList>
#include <QGraphicsScene>
#include <QGraphicsPathItem>
#include <QtMath>

Workers::Workers(QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(parent), isDestroyed(false)
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
    // Check if there is a destroyed structure
    if (!isDestroyed)
    {
        // If no structure is destroyed, hide the worker and return
        hideWorker();
        return;
    }

    // Show the worker if there is a destroyed structure
    showWorker();

    targetPosition = targetPoint;

    // Find the shortest path to the target position
    QList<QGraphicsItem*> obstacles = scene()->items();
    qreal shortestPath = std::numeric_limits<qreal>::max();
    qreal currentPath;

    foreach (QGraphicsItem* obstacle, obstacles)
    {
        if (obstacle != this && obstacle->type() == QGraphicsPathItem::Type)
        {
            currentPath = qSqrt(qPow(targetPosition.x() - obstacle->pos().x(), 2) +
                                qPow(targetPosition.y() - obstacle->pos().y(), 2));

            if (currentPath < shortestPath)
            {
                shortestPath = currentPath;
            }
        }
    }

    // Move along the road to the target position
    if (shortestPath != std::numeric_limits<qreal>::max())
    {
        setPos(mapToParent(shortestPath, 0));
    }

    // Check if the workers have reached the target position
    if (pos() == targetPosition)
    {
        // ... Perform the rebuilding process ...

        // Reset the target position
        targetPosition = QPointF();
        isDestroyed = false;
        hideWorker();
    }
}
