#ifndef WORKERS_H
#define WORKERS_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPointF>

class Workers : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Workers();

public slots:
    void showWorker();
    void hideWorker();
    void rebuildStructure(QPointF targetPoint);

private:
    bool isDestroyed;
    QPointF targetPosition;
};

#endif // WORKERS_H
