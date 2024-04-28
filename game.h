// Game.h
#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGridLayout>
#include <QVector>
#include<QProgressBar>
#include<QTimer>
#include<QLabel>
#include<QPushButton>
#include <QGraphicsTextItem>
#include"cannon.h"
#include"troop.h"
#include "QTimer"
#include"fence1.h"
#include"townhall.h"
#include "health.h"
#include <QMouseEvent>
class QGraphicsScene;
class QGraphicsView;


class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);

  //  void printClanDesign();
    void displayClanDesign();
    void displayClanDesign2();
    void adjustSceneSize();
     void startGame();
    void resetTimer();

     void formTroopsLevel1();
     void formTroopsLevel2();
     QTimer* m_timer;
     QTimer* spawnTimer;
     void handleSoundSettingsButton();
     void handleShopButton();
private:
     bool level1, level2, level3, level4, level5;
    int currentMoney;
    QGridLayout *layout;
    QVector<QVector<int>> clanDesign;
     QVector<QVector<int>> clanDesign2;
   QGraphicsView* view;
   QGraphicsScene* scene;
    int cellSize;
    int sceneWidth;
    int sceneHeight;
    QProgressBar* timerBar;
    QTimer* timer;
    QRectF timerRect;
    QLabel* timerLabel;
    bool gameStarted;
    int elapsedSeconds;
    QGraphicsTextItem* timerText;
    QPushButton* startButton;
    Fence1* fence;
    Cannon* cannon;
    Townhall* townhall;
    QPixmap scalePixmap(const QPixmap& pixmap, int width, int height);
    Health* health;
    Townhall*findNearestTownhall(const QPointF& position);
    bool townHallDestroyed;
    void mousePressEvent(QMouseEvent *event);
    bool cannonDestroyed;
private slots:
    void handleStartButton();
    void updateTimer();

public slots:
      void checkCollisions(Troop* troop);
    void moveTroops();

};

#endif // GAME_H
