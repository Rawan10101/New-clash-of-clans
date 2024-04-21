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
class QGraphicsScene;
class QGraphicsView;

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);

  //  void printClanDesign();
    void displayClanDesign();
    void adjustSceneSize();
     void startGame();
    void resetTimer();

     void formTroops();
private:

    QGridLayout *layout;
    QVector<QVector<int>> clanDesign;
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

    QPixmap scalePixmap(const QPixmap& pixmap, int width, int height);
private slots:
    void handleStartButton();
    void updateTimer();


};

#endif // GAME_H
