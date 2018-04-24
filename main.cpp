#include <QApplication>
#include <QFontDatabase>
#include <QFile>

#include "engine.h"
#include "mainwidget.h"

int main(int argc, char *argv[])
{
    QApplication minesweeper(argc, argv);

    // 1. Load FontAwesome
    QFontDatabase::addApplicationFont(":/Resources/FontAwesome.otf");

    // 3. Set Stylesheet
    QFile cssFile(":/Styles/default.css");
    cssFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(cssFile.readAll());
    minesweeper.setStyleSheet(styleSheet);

    Engine*      engine = new Engine();
    MainWidget   main_window(NULL, engine);
    main_window.setWindowTitle("MineSweeper by LeonVincii");
    main_window.show();
    return minesweeper.exec();
}
