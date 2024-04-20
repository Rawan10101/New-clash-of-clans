#include "startgame1.h"
#include "ui_startgame1.h"

#include <QMediaPlayer>
#include <QPixmap>
#include <QThread>
#include <QEventLoop>

StartGame1::StartGame1(QWidget *parent) : QDialog(parent), ui(new Ui::StartGame1)
{
    ui->setupUi(this);

    QPixmap backgroundImage("C:/Users/HP/Desktop/file1/clash-of-clans-f88iyeweabo3r6kz.jpg");
    QPixmap scaledBackground = backgroundImage.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, scaledBackground);
    this->setPalette(palette);

    QMediaPlayer *startgamemusic = new QMediaPlayer();
 //   startgamemusic->setMedia(QUrl::fromLocalFile("qrc:/sounds/mixkit-bonus-extra-in-a-video-game-2064.wav"));
    // startgamemusic->setVolume(0.25f);  // Set the volume (0-100)
    startgamemusic->play();
}

StartGame1::~StartGame1()
{
    delete ui;
}

void StartGame1::start_loading()
{
    for (int value = ui->progressBar->minimum(); value < ui->progressBar->maximum(); value++)
    {
        QThread::msleep(30);
        ui->progressBar->setValue(value);
        ui->label_value->setText(QString::number(value));
        qApp->processEvents(QEventLoop::AllEvents);
    }
}

void StartGame1::on_pushButton_clicked()
{
    // Handle push button click event
}

void StartGame1::on_groupBox_Background_clicked()
{
    // Handle group box background click event
}

void StartGame1::on_label_value_linkActivated(const QString &link)
{
    // Handle link activation event for label_value
}
