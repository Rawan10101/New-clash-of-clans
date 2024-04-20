#ifndef STARTGAME1_H
#define STARTGAME1_H

#include <QDialog>

namespace Ui {
class StartGame1;
}

class StartGame1 : public QDialog
{
    Q_OBJECT

public:
    explicit StartGame1(QWidget *parent = nullptr);
    ~StartGame1();

public slots:
    void start_loading();

private slots:
    void on_pushButton_clicked();
    void on_groupBox_Background_clicked();
    void on_label_value_linkActivated(const QString &link);

private:
    Ui::StartGame1 *ui;
};

#endif // STARTGAME1_H
