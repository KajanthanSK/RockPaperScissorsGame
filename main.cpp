#include "RPSMainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RPSMainWindow w;
    w.show();
    return a.exec();
}
