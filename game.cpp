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
    QFile file(":/File.txt");
    QFile file2(":/../../../Desktop/file1/file2.txt");

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::information(this, "Error", "Failed to open file: File.txt");
        return;
    }
    if (!file2.open(QFile::ReadOnly | QFile::Text))
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

    QPixmap backgroundPixmap(":/images/Background.png");
    if (!backgroundPixmap.isNull())
    {
        view->setBackgroundBrush(backgroundPixmap);
      }




    QTextStream in(&file);
    QTextStream in2(&file2);

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

    while (!in2.atEnd())
    {
        QString line = in2.readLine();
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
        clanDesign2.append(row);
    }

    file2.close();


    qDebug() << clanDesign[0][1] << "test";

    scene->setSceneRect(0, 0, clanDesign[0].size() * 50, clanDesign.size() * 50);
    view->setFixedSize(clanDesign[0].size() * 50, clanDesign.size() * 50);

    //----------------------------------------------//


    timerRect = QRectF(10, 10, 100, 40);
    timerText = new QGraphicsTextItem();
    timerText->setPos(timerRect.topLeft());
    timerText->setPlainText("0:00");
    timerText->setDefaultTextColor(Qt::white);
    timerText->setFont(QFont("Arial", 20));
    timerText->setOpacity(0.8);
    timerText->setPos(0,0);
    scene->addItem(timerText);


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

    // Create the timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));

    m_timer = new QTimer(this);
    connect(m_timer,SIGNAL(timeout()),this,SLOT (moveTroops()));

    m_timer->start(100);

    spawnTimer = new QTimer();
    connect(spawnTimer, SIGNAL(timeout()),this, SLOT (formTroops()));

    Fence1* fence;
    Cannon* cannon;
    Townhall* townhall;
    health=new Health();
    townHallDestroyed=false;

    //-----------------------------------------------//

    QPushButton* soundSettingsButton = new QPushButton("Sound Settings", this);
    soundSettingsButton->setGeometry(100, 100, 150, 30);
    layout->addWidget(soundSettingsButton);

    QPushButton* shopButton = new QPushButton("Shop", this);
    shopButton->setGeometry(100, 140, 150, 30);
    layout->addWidget(shopButton);

    connect(soundSettingsButton, &QPushButton::clicked, this, &Game::handleSoundSettingsButton);
    connect(shopButton, &QPushButton::clicked, this, &Game::handleShopButton);
    //MoneyBar will increase by 5 after killing one troop and increase by 20 when a level is completed
    QProgressBar* moneyBar= new QProgressBar(this);
    moneyBar->setMinimum(0);
    moneyBar->setMaximum(1000);
    currentMoney=0;
    moneyBar->setValue(currentMoney);


}

void Game::handleSoundSettingsButton()
{



}

void Game::handleShopButton()
{
    QMessageBox shopMessageBox(this);
    shopMessageBox.setWindowTitle("Shop");
    shopMessageBox.setIcon(QMessageBox::Information);


    QLabel townhallLabel("Townhall", &shopMessageBox);
    QLabel fenceLabel("Fence", &shopMessageBox);
    QLabel cannonLabel("Cannon", &shopMessageBox);


    QPushButton* townhallUpgradeButton = new QPushButton("Upgrade", &shopMessageBox);
    QPushButton* fenceUpgradeButton = new QPushButton("Upgrade", &shopMessageBox);
    QPushButton* cannonUpgradeButton = new QPushButton("Upgrade", &shopMessageBox);


    connect(townhallUpgradeButton, &QPushButton::clicked, this, &Game::handleTownhallUpgradeButton);
    connect(fenceUpgradeButton, &QPushButton::clicked, this, &Game::handleFenceUpgradeButton);
    connect(cannonUpgradeButton, &QPushButton::clicked, this, &Game::handleCannonUpgradeButton);


    QVBoxLayout* layout1 = new QVBoxLayout;
    layout1->addWidget(&townhallLabel);
    layout1->addWidget(townhallUpgradeButton);
    layout1->addWidget(&fenceLabel);
    layout1->addWidget(fenceUpgradeButton);
    layout1->addWidget(&cannonLabel);
    layout1->addWidget(cannonUpgradeButton);

    shopMessageBox.setLayout(layout1);

    int newMoney = currentMoney - 50;

    int result = shopMessageBox.exec();

    if (result == QMessageBox::Ok) {
        //new photo for the item which is upgraded
        if (newMoney >= 0) {
            currentMoney = newMoney;
        } else {
            QMessageBox::critical(this, "Not enough Money", "You don't have enough money for the upgrades.");
        }
    }
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
            int element = clanDesign[i][j];

            if (element == 0)
            {
            }
            else if (element == 1)
            {
                townhall = new Townhall();
                townhall->setPos(j * castleSize, i * castleSize);
                scene->addItem(townhall);

            }
            else if (element == 2)
            {
                 cannon = new Cannon();
                cannon->setPos(j * cannonSize, i * cannonSize);
                scene->addItem(cannon);


            }

            else if (element == 3)
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
void Game::displayClanDesign2()
{
    const int tileSize = 50; // Adjust this value according to your desired tile size
    const int fenceSize = tileSize ;
    const int castleSize = tileSize; // Double the size of the tile for the castle
    const int cannonSize = tileSize;
    qDebug()<<"Working 2";

    for (int i = 0; i < clanDesign2.size(); i++)
    {
        for (int j = 0; j < clanDesign2[i].size(); j++)
        {
            int element = clanDesign2[i][j]; // Get the element at the current position

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
        if (level1)
        {
            startButton->hide();
            resetTimer();
            timerText->show();
            timer->start(1000);
            displayClanDesign();
            spawnTimer->start(4000);
            formTroopsLevel1();
        }
        else if (level2)
        {
            startButton->hide();
            resetTimer();
            timerText->show();
            timer->start(1000);
            displayClanDesign2();
            spawnTimer->start(4000);
            formTroopsLevel2();
        }
        else if (level3)
        {

            startButton->hide();
            resetTimer();
            timerText->show();
            timer->start(1000);
            displayClanDesign2();
            spawnTimer->start(4000);
            formTroopsLevel2();
        }
        else if (level4)
        {

            startButton->hide();
            resetTimer();
            timerText->show();
            timer->start(1000);
            displayClanDesign2();
            spawnTimer->start(4000);
            formTroopsLevel2();
        }
        else if (level5)
        {

            startButton->hide();
            resetTimer();
            timerText->show();
            timer->start(1000);
            displayClanDesign2();
            spawnTimer->start(4000);
            formTroopsLevel2();
        }
}
void Game::formTroopsLevel1()
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
void Game::formTroopsLevel2()
{
    int count=0;
    if (gameStarted)
    {
        for (int i = 0; i < clanDesign.size(); ++i)
        {
            for (int j = 0; j < clanDesign[i].size(); ++j)
            {
                if (clanDesign[i][j] == 0 && count<=10)
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

        //redirect troop if cannon is in their way
        if (typeid(*collidingItem) == typeid(Cannon)) {
            if (troop->x() <= collidingItem->x() + 50 )
                troop->setPos(troop->x()-10, troop->y());
            else
                troop->setPos(troop->x()+10, troop->y()-10);
        }

        else if (typeid(*collidingItem) == typeid(Townhall)) {
            Townhall *townhall = dynamic_cast<Townhall*>(collidingItem);

            qDebug()<<"townhall collision";

            qreal dx = troop->x() - collidingItem->x();
            qreal dy = troop->y() - collidingItem->y();

            if (qAbs(dx) > qAbs(dy))//move left or right
            {
                if (dx < 0) //move left
                    troop->setPos(townhall->x()-80, townhall->y());
                else //move right
                    troop->setPos(townhall->x()+80, townhall->y());
            }
            else //move up or down
            {
                if (dy < 0) //move up
                    troop->setPos(townhall->x(), townhall->y()-80);
                else //move down
                    troop->setPos(townhall->x(), townhall->y()+80);
            }

            townhall->townhallHealth->decrementHealth();
            qDebug()<< townhall->townhallHealth->getHealth();
            if (townhall->townhallHealth->getHealth() <= 0)
            {
                scene->removeItem(townhall);
                delete townhall;
                townHallDestroyed = true;

            }

        }


        else if (typeid(*collidingItem) == typeid(Fence1)) {
            Fence1 *fence = dynamic_cast<Fence1*>(collidingItem);

            qDebug()<<"fence collision";

            qreal dx = troop->x() - collidingItem->x();
            qreal dy = troop->y() - collidingItem->y();

            if (qAbs(dx) >= qAbs(dy))//move left or right
            {
                if (dx <= 0) //move left
                    troop->setPos(fence->x()-50, troop->y());
                else //move right
                    troop->setPos(fence->x()+50, troop->y());
            }
            else //move up or down
            {
                if (dy <= 0) //move up
                    troop->setPos(troop->x(), fence->y()-50);
                else //move down
                    troop->setPos(troop->x(), fence->y()+50);
            }

            fence->reduceHealth();
            qDebug()<< fence->getHealth();
            if (fence->getHealth() <= 0)
            {
                scene->removeItem(fence);
                delete fence;

            }

        }

        if (typeid(*collidingItem) == typeid(Bullet)) {
            Bullet* bullet = dynamic_cast<Bullet*>(collidingItem);
            if (scene->items().contains(bullet)) {
                currentMoney+=5;
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
            gameStarted = true;
            startGame();

        }
        else if (level1 && !townHallDestroyed) // Player completed level 1
        {
            level1 = false;
            level2 = true;
            currentMoney+=100;;
            startGame();
        }
        else if (level2 && !townHallDestroyed) // Player completed level 2
        {
            level1 = false;
            level2 = false;
            level3=true;
            currentMoney+=100;;
            startGame();
        }
        else if (level3 && !townHallDestroyed) // Player completed level 3
        {
            level1 = false;
            level2 = false;
            level3=false;
            level4=true;
            currentMoney+=100;;
            startGame();
        }
        else if (level4 && !townHallDestroyed) // Player completed level 4
        {
            level1 = false;
            level2 = false;
            level3=false;
            level4=false;
            level5=true;
            currentMoney+=100;;
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
        spawnTimer->stop();
        QMessageBox::information(this, "Player wins!", "Level 1 completed succesfully!");

    }
    else if(townHallDestroyed==true){
        timer->stop();
        spawnTimer->stop();
        QMessageBox::information(this, "Game Over", "Game Over");
    }
    else{
        QMessageBox::information(this, "Congrats", "Level 2");
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
}void Game::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (cannonDestroyed==true)
        {


            return;
        }

        QPoint targetPos = QCursor::pos();
        qreal dx = targetPos.x() - cannon->pos().x();
        qreal dy = targetPos.y() - cannon->pos().y();
        qreal length = qSqrt(dx * dx + dy * dy);
        qreal directionX = dx / length;
        qreal directionY = dy / length;

        qDebug() << "Direction X:" << directionX << "Direction Y:" << directionY; // Debug statement

        Bullet *bullet = new Bullet(targetPos.x(), targetPos.y(), cannon->pos().x() , cannon->pos().y());
        bullet->setDirection(directionX, directionY);

        bullet->setPos(cannon->pos().x() + 50, cannon->pos().y() + 50);

        scene->addItem(bullet);
    }
}


