#include "spaceinwaders.h"
#include<QScreen>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CSpaceInwaders* pGame = new CSpaceInwaders(qApp->screens()[0]->size());
    pGame->showFullScreen();
    pGame->Run();

    return a.exec();
}
