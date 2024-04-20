#include "startgame.h"
#include "ui_startgame.h"
#include <QMediaPlayer>
#include <QPixmap>

StartGame::StartGame(QWidget *parent) : QDialog(parent), ui(new Ui::StartGame)
{
    ui->setupUi(this);

    QPixmap backgroundImage("C:/Users/HP/Desktop/file1/clash-of-clans-f88iyeweabo3r6kz.jpg");
    QPixmap scaledBackground = backgroundImage.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, scaledBackground);
    this->setPalette(palette);

    QMediaPlayer *startgamemusic = new QMediaPlayer();
    startgamemusic->setSource(QUrl::fromLocalFile("qrc:/sounds/mixkit-bonus-extra-in-a-video-game-2064.wav"));
    // startgamemusic->setVolume(0.25f);  // Set the volume (0-100)
    startgamemusic->play();
}

StartGame::~StartGame()
{
    delete ui;
}

void StartGame::start_loading()
{
    for (int value = ui->progressBar->minimum(); value < ui->progressBar->maximum(); value++)
    {
        QThread::msleep(30);
        ui->progressBar->setValue(value);
        ui->label_value->setText(QString::number(value));
        qApp->processEvents(QEventLoop::AllEvents);
    }
}

void StartGame::on_pushButton_clicked() {}

void StartGame::on_groupBox_Background_clicked() {}

void StartGame::on_label_value_linkActivated(const QString &link) {}
