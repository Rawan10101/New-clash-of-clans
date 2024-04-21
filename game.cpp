#include "Game.h"
#include "cannon.h"
#include "fence.h"
#include "townhall.h"
#include "troop.h"
#include "bullet.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QFrame>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QProgressBar>
#include <QGraphicsTextItem>
#include <QPushButton>
#include <QTimer>
#include <QTime>
#include <QGraphicsProxyWidget>
#include<fence1.h>
#include<QRandomGenerator>
#include<QCoreApplication>
using namespace std;
Game::Game(QWidget *parent) : QWidget(parent)
{
    QFile file(":/File.txt"); // Open the file
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::information(this, "Error", "Failed to open file: File.txt");
        return;
    }

    layout = new QGridLayout(this);
    setLayout(layout);
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene);
    view->setStyleSheet("background: transparent; border: 0px");
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    layout->addWidget(view);

    QPixmap backgroundPixmap(":/images/Background.png"); // Set the background image
    if (!backgroundPixmap.isNull())
    {
        view->setBackgroundBrush(backgroundPixmap); // Set the background image as the view's background brush
        sceneWidth = backgroundPixmap.width(); // Set the scene width equal to the background image width
        sceneHeight = backgroundPixmap.height(); // Set the scene height equal to the background image height
    }

    clanDesign.clear(); // Clear the clan design vector

    QTextStream in(&file);

    while (!in.atEnd())
    {
        QString line = in.readLine(); // Read a line from the file
        QStringList values = line.split(',');

        QVector<int> row;
        for (const QString& value : values)
        {
            bool ok;
            int element = value.toInt(&ok); // Convert the value to an int
            if (ok)
                row.append(element);
            else
                row.append(0);
        }
        clanDesign.append(row);
    }

    file.close();

    qDebug() << clanDesign[0][1] << "test";

  //  scene->setSceneRect(0, 0, clanDesign.size() * 50, clanDesign[0].size() * 50);
    view->resize(clanDesign.size() * 50, clanDesign[0].size() * 50);

    //----------------------------------------------//

    // Create the timer label
    timerRect = QRectF(10, 10, 100, 40); // Position and size of the timer rectangle
    timerText = new QGraphicsTextItem();
    timerText->setPos(timerRect.topLeft());
    timerText->setPlainText("0:00");
    timerText->setDefaultTextColor(Qt::white);
    timerText->setFont(QFont("Arial", 20));
    timerText->setOpacity(0.8);
    timerText->setPos(0,0);
    scene->addItem(timerText);

    // Create the start button
    startButton = new QPushButton("Start", this);
    startButton->setStyleSheet("font-size: 20px;"); // Set the font size of the button
    startButton->move(100,100);
    connect(startButton, SIGNAL(clicked()), this, SLOT(handleStartButton()));
    QGraphicsProxyWidget *buttonProxy = scene->addWidget(startButton);
    buttonProxy->setPos(scene->width() - startButton->width() - 10, 10);
    layout->addWidget(startButton);
    layout->setAlignment(startButton, Qt::AlignCenter | Qt::AlignTop); // Align the start button to the center horizontally

    gameStarted = false;
    qDebug()<<"Working";

    // Create the timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));

    m_timer = new QTimer(this);
    connect(m_timer,SIGNAL(timeout()),this,SLOT (moveTroops()));

    m_timer->start(100);
    Fence1* fence;
    Cannon* cannon;
    Townhall* townhall;
    health=new Health();
    townHallDestroyed=false;
}

void Game::displayClanDesign()
{
    const int tileSize = 50; // Adjust this value according to your desired tile size
    const int fenceSize = tileSize ;
    const int castleSize = tileSize; // Double the size of the tile for the castle
    const int cannonSize = tileSize;
    qDebug()<<"Working 2";

    for (int i = 0; i < clanDesign.size(); i++)
    {
        for (int j = 0; j < clanDesign[i].size(); j++)
        {
            int element = clanDesign[i][j]; // Get the element at the current position

            if (element == 0)
            {
            }
            else if (element == 1) // castle
            {
                townhall = new Townhall();
                townhall->setPos(j * castleSize, i * castleSize);
                scene->addItem(townhall);

            }
            else if (element == 2) // cannon
            {
                 cannon = new Cannon();
                cannon->setPos(j * cannonSize, i * cannonSize);
                scene->addItem(cannon);


            }
            else if (element==4){

            }
            else if (element == 3) // fence
            {
              qDebug()<<"Fence1";
               fence = new Fence1();
                 fence->setPos(j * fenceSize, i * fenceSize);
                scene->addItem(fence);
                 qDebug()<<"Fence2";
            }
        }
    }
}


void Game::startGame()
{
    startButton->show();
    startButton->setEnabled(true);
    startButton->hide();
    resetTimer();
    timerText->show();
    timer->start(1000); //(1 second)
    displayClanDesign();
    formTroops();
}
void Game::formTroops()
{
    int count=0;
    if (gameStarted)
    {
        for (int i = 0; i < clanDesign.size(); ++i)
        {
            for (int j = 0; j < clanDesign[i].size(); ++j)
            {
                if (clanDesign[i][j] == 0 && count<=5)
                {
                    Troop* troop = new Troop();
                    int randomX = QRandomGenerator::global()->bounded(scene->width());
                    scene->addItem(troop);
                    troop->setPos(randomX, 0);
                       m_timer->start(20);

                    count++;

                }
            }
        }
    }
}
void Game::moveTroops()
{
    QList<QGraphicsItem*> items = scene->items();
    foreach (QGraphicsItem* item, items) {
        Troop* troop = dynamic_cast<Troop*>(item);
        if (troop && !troop->stopped) {
            Townhall* nearestTownhall = findNearestTownhall(troop->pos());
            if (nearestTownhall) {
                QPointF direction = nearestTownhall->pos() - troop->pos();
                direction /= QVector2D(direction).length();
                qreal dx = direction.x() * troop->speed;
                qreal dy = direction.y() * troop->speed;
                troop->setPos(troop->x() + dx, troop->y() + dy);

                checkCollisions(troop); //will destroy the item that will be collided with on its way to the townhall
            }
        }
    }
}

void Game::checkCollisions(Troop* troop)
{
    QList<QGraphicsItem*> collidingItems = troop->collidingItems();
    foreach (QGraphicsItem* collidingItem, collidingItems)
    {

        if (!scene->items().contains(collidingItem))
            continue;

        if (typeid(*collidingItem) == typeid(Cannon)) {
            Cannon *cannon = dynamic_cast<Cannon*>(collidingItem);
            troop->stopped = true;
            QTimer::singleShot(5000, [=]() {
                troop->stopped = false;
                if (scene->items().contains(cannon)) {
                    scene->removeItem(cannon);
                    delete cannon;
                }
            });
        }
        else if (typeid(*collidingItem) == typeid(Townhall)) {
            Townhall *townhall = dynamic_cast<Townhall*>(collidingItem);

            troop->stopped = true;
            QTimer::singleShot(5000, [=]() {
                troop->stopped = false;
                if (scene->items().contains(townhall)) {
                    scene->removeItem(townhall);
                    delete townhall;
                    townHallDestroyed=true;
                }
            });
        }
        else if (typeid(*collidingItem) == typeid(Fence1)) {
            Fence1 *fence = dynamic_cast<Fence1*>(collidingItem);

            troop->stopped = true;
            QTimer::singleShot(5000, [=]() {  // Pause troop's movement for 5 seconds
                troop->stopped = false;
                if (scene->items().contains(fence)) {
                    scene->removeItem(fence);
                    delete fence;
                }
            });
        }
    }
}


void Game::handleStartButton()
{
    if (!gameStarted)
    {
        startButton->setEnabled(false);
        gameStarted = true;
        startGame();
    }
}


void Game::updateTimer()
{
    QTime currentTime = QTime::fromString(timerText->toPlainText(), "m:ss");

    currentTime = currentTime.addSecs(1);
    timerText->setPlainText(currentTime.toString("m:ss"));

    if (currentTime.minute() == 1 )    {
        timer->stop();
        QMessageBox::information(this, "Game Over", "Time's up!");
    }
    else if(townHallDestroyed==true){
        timer->stop();
        QMessageBox::information(this, "Level 1", "Level 1 Passed");
    }

}

void Game::resetTimer()
{
    timerText->setPlainText("0:00");
}

Townhall* Game::findNearestTownhall(const QPointF& position)
{
    qreal minDistanceSquared = numeric_limits<qreal>::max();
    Townhall* nearestTownhall = nullptr;
    foreach (QGraphicsItem* item, scene->items()) {
        Townhall* townhall = dynamic_cast<Townhall*>(item);
        if (townhall) {
            qreal distanceSquared = QPointF(townhall->x() - position.x(), townhall->y() - position.y()).manhattanLength();
            if (distanceSquared < minDistanceSquared) {
                minDistanceSquared = distanceSquared;
                nearestTownhall = townhall;
            }
        }
    }
    return nearestTownhall;
}

void Game::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        Bullet *bullet = new Bullet();
        bullet->setDirection(event->position().x(), event->position().y());

        bullet->setPos(cannon->pos().x()+50, cannon->pos().y()+50);

        scene->addItem(bullet);
    }
}
