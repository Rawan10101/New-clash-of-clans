#include "globalvariables.h"
#include "ui_globalvariables.h"

Globalvariables::Globalvariables(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Globalvariables)
{
    ui->setupUi(this);
}

Globalvariables::~Globalvariables()
{
    delete ui;
}
