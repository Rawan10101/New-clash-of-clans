#include "Game.h"
#include "cannon.h"
#include "fence1.h"
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

    cannonDestroyed=false;
    layout = new QGridLayout(this);
    setLayout(layout);

    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
    view->setStyleSheet("background: transparent; border: 0px");
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    layout->addWidget(view);

    QPixmap backgroundPixmap(":/images/Background.png"); // background image empty field
    if (!backgroundPixmap.isNull())
    {
        view->setBackgroundBrush(backgroundPixmap);
    }

    // clanDesign.clear();

    QTextStream in(&file);

    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList values = line.split(',');

        QVector<int> row;
        for (const QString& value : values)
        {
            bool ok;
            int element = value.toInt(&ok);
            if (ok)
                row.append(element);
            else
                row.append(0);
        }
        clanDesign.append(row);
    }

    file.close();

    qDebug() << clanDesign[0][1] << "test";

    scene->setSceneRect(0, 0, clanDesign[0].size() * 50, clanDesign.size() * 50);
    view->setFixedSize(clanDesign[0].size() * 50, clanDesign.size() * 50);

    //----------------------------------------------//

    //timer label
    timerRect = QRectF(10, 10, 100, 40); // Position and size of the timer rectangle
    timerText = new QGraphicsTextItem();
    timerText->setPos(timerRect.topLeft());
    timerText->setPlainText("0:00");
    timerText->setDefaultTextColor(Qt::white);
    timerText->setFont(QFont("Arial", 20));
    timerText->setOpacity(0.8);
    timerText->setPos(0,0);
    scene->addItem(timerText);

    //start button
    startButton = new QPushButton("Start", this);
    startButton->setStyleSheet("font-size: 20px;");
    startButton->move(100,100);
    connect(startButton, SIGNAL(clicked()), this, SLOT(handleStartButton()));
    QGraphicsProxyWidget *buttonProxy = scene->addWidget(startButton);
    buttonProxy->setPos(scene->width() - startButton->width() - 10, 10);
    layout->addWidget(startButton);
    layout->setAlignment(startButton, Qt::AlignCenter | Qt::AlignTop);

    gameStarted = false;
    qDebug()<<"Working";

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer())); //game timer

    m_timer = new QTimer(this);
    connect(m_timer,SIGNAL(timeout()),this,SLOT (moveTroops())); //to move troops

    m_timer->start(100);

    Fence1* fence;
    Cannon* cannon;
    Townhall* townhall;
    health=new Health();
    townHallDestroyed=false;
}

void Game::displayClanDesign()
{
    const int tileSize = 50;
    const int fenceSize = tileSize ;
    const int castleSize = tileSize;
    const int cannonSize = tileSize;

    qDebug()<<"Working 2";

    for (int i = 0; i < clanDesign.size(); i++)
    {
        for (int j = 0; j < clanDesign[i].size(); j++)
        {
            int element = clanDesign[i][j]; //element at the current position

            // if (element == 0)
            // {
            // }
            if (element == 1) // castle
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
            // else if (element==4){

            // }
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
    timer->start(1000);

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
            Townhall* nearestTownhall = findNearestTownhall(troop->pos()); //troops move towards the castle/townhall
            if (nearestTownhall) {
                QPointF direction = nearestTownhall->pos() - troop->pos();
                direction /= QVector2D(direction).length();
                qreal dx = direction.x() * troop->speed;
                qreal dy = direction.y() * troop->speed;
                troop->setPos(troop->x() + dx, troop->y() + dy);

                checkCollisions(troop); //to destroy obstacles between troop and the castle/townhall
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
            cannonDestroyed=true;
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
            QTimer::singleShot(5000, [=]() {
                troop->stopped = false;
                if (scene->items().contains(fence)) {
                    scene->removeItem(fence);
                    delete fence;
                }
            });
        }
        if (typeid(*collidingItem) == typeid(Bullet)) {
            Bullet* bullet = dynamic_cast<Bullet*>(collidingItem);
                if (scene->items().contains(bullet)) {
                    scene->removeItem(collidingItem);

                    delete bullet;
                scene->removeItem(troop);
                    delete troop;
                     // disconnect(m_timer,SIGNAL(timeout()),this,SLOT (moveTroops()));
                    scene->removeItem(bullet);
                }
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
        QMessageBox::information(this, "Player wins!", "Level completed succesfully!");
    }
    else if(townHallDestroyed==true){
        timer->stop();
        QMessageBox::information(this, "Game Over", "Game Over");
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

}void Game::mousePressEvent(QMouseEvent *event) //release bullet when player clicks left
{
    if (event->button() == Qt::LeftButton)
    {
        if (cannonDestroyed==true)
        {
            return;
        }

        // QPointF targetPos = event->pos();
        QPoint targetPos = QCursor::pos();
        qreal dx = targetPos.x() - cannon->pos().x();
        qreal dy = targetPos.y() - cannon->pos().y();
        qreal length = qSqrt(dx * dx + dy * dy);
        qreal directionX = dx / length;
        qreal directionY = dy / length;

        qDebug() << "Direction X:" << directionX << "Direction Y:" << directionY;

        Bullet *bullet = new Bullet(targetPos.x(), targetPos.y(), cannon->pos().x() , cannon->pos().y());
        bullet->setDirection(directionX, directionY);

        bullet->setPos(cannon->pos().x() + 50, cannon->pos().y() + 50); //bullet comes out of cannon

        scene->addItem(bullet);
    }
}

