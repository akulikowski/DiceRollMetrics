#include "dicerollmetrics.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DiceRollMetrics w;
    w.show();
    return a.exec();
}
