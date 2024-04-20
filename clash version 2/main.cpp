#include "Game.h"

#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game w;

 //  w.displayClanDesign();
    w.show();

    return a.exec();
}



