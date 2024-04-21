#include "Game.h"
#include "cannon.h"
#include "fence.h"
#include "townhall.h"
#include "troop.h"
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

Game::Game(QWidget *parent) : QWidget(parent)
{
    QFile file("C:/Users/HP/Desktop/file1/File.txt"); // Open the file
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

    QPixmap backgroundPixmap("C:/Users/HP/Desktop/file1/thumb.jpg"); // Set the background image
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
              //  QPixmap pixmap("C:/Users/HP/Desktop/file1/Clan_Castle11.webp");
               // pixmap = pixmap.scaled(10, 10);

                Townhall* townhall = new Townhall();
                townhall->setPos(j * castleSize, i * castleSize);
                scene->addItem(townhall);

            }
            else if (element == 2) // cannon
            {
                Cannon* cannon = new Cannon();
                cannon->setPos(j * cannonSize, i * cannonSize);
                scene->addItem(cannon);


            }
            else if (element==4){

            }
            else if (element == 3) // fence
            {
              //  QPixmap pixmap("C:/Users/HP/Desktop/file1/Wall1.webp");
               // pixmap = pixmap.scaled(50, 50);
                qDebug()<<"Fence1";
                Fence1* fence = new Fence1();
                 fence->setPos(j * fenceSize, i * fenceSize);
                scene->addItem(fence);
                 qDebug()<<"Fence2";
            }
        }
    }
}

void Game::startGame()
{
    // Show the start button before hiding it
    startButton->show();
    startButton->setEnabled(true);

    // Hide the start button after clicking it
    startButton->hide();

    // Reset the timer and show it
    resetTimer();
    timerText->show();

    // Start the timer
    timer->start(1000); // Timer interval: 1000 ms (1 second)

    // Display clan design
    displayClanDesign();

    // Start forming troops
    formTroops();
}
void Game::formTroops()
{
    if (gameStarted)
    {
        for (int i = 0; i < clanDesign.size(); ++i)
        {
            for (int j = 0; j < clanDesign[i].size(); ++j)
            {
                // Check if the element at the current position is zero
                if (clanDesign[i][j] == 0)
                {
                    // Create a new troop and add it to the scene at the current position
                    Troop* troop = new Troop();
                    scene->addItem(troop);
                    // Set the position where enemies will appear (random)
                    int randomX = QRandomGenerator::global()->bounded(scene->width());
                     troop->setPos(randomX, 0);
                }
            }
        }
    }
}


void Game::handleStartButton()
{
    if (!gameStarted)
    {
        // Disable the start button
        startButton->setEnabled(false);

        // Set gameStarted flag to true
        gameStarted = true;

        // Start the game
        startGame();
    }
}


void Game::updateTimer()
{
    QTime currentTime = QTime::fromString(timerText->toPlainText(), "m:ss");

    currentTime = currentTime.addSecs(1);
    timerText->setPlainText(currentTime.toString("m:ss"));

    // Check if the timer has reached 1 minute
    if (currentTime.minute() == 1)
    {
        // Stop the timer
        timer->stop();
        // Show a message box indicating that the game is over
        QMessageBox::information(this, "Game Over", "Time's up!");
        // Start a new game
        startGame();
    }
}

void Game::resetTimer()
{
    // Reset the timer label text to 0:00
    timerText->setPlainText("0:00");
}
