#include <QApplication>

#include "engine.h"
#include "mainwidget.h"

int main(int argc, char *argv[])
{
    QApplication minesweeper(argc, argv);
    Engine*      engine = new Engine();
    MainWidget   main_window;
    main_window.setEngine(engine);
    main_window.setWindowTitle("MineSweeper by LeonVincii");
    main_window.show();
    return minesweeper.exec();
}
