#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication minesweeper(argc, argv);
    MainWindow main_window;
    main_window.setWindowTitle("MineSweeper by LV");
    main_window.show();

    return minesweeper.exec();
}
