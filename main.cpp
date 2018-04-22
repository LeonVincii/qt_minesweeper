#include "engine.h"
#include "mainwidget.h"

#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication minesweeper(argc, argv);
    MainWidget main_window;
    main_window.setWindowTitle("MineSweeper by LeonVincii");
    main_window.show();
    return minesweeper.exec();
}
