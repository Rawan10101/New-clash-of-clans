#ifndef STARTGAME_H
#define STARTGAME_H

#include <QDialog>
#include <QMediaPlayer>

// Include the generated header file for the UI class
#include "ui_startgame.h"

class StartGame : public QDialog
{
    Q_OBJECT

public:
    StartGame(QWidget *parent = nullptr);
    ~StartGame();

public slots:
    void start_loading();

private slots:
    void on_pushButton_clicked();
    void on_groupBox_Background_clicked();
    void on_label_value_linkActivated(const QString &link);

private:
    Ui::StartGame *ui;


};

#endif // STARTGAME_H
