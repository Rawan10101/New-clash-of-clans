#ifndef ARCHTOWER_H
#define ARCHTOWER_H

#include <QDialog>

namespace Ui {
class ArchTower;
}

class ArchTower : public QDialog
{
    Q_OBJECT

public:
    explicit ArchTower(QWidget *parent = nullptr);
    ~ArchTower();

private:
    Ui::ArchTower *ui;
};

#endif // ARCHTOWER_H
