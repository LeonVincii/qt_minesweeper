#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QDebug>

#include "minezone.h"

struct Difficulty;
class MineZone;

class Engine : public QObject
{
    Q_OBJECT

public:
    /* ****************************************************************************************
     * Constructor & Destructor
     * ****************************************************************************************/
    explicit Engine(QObject *parent = nullptr);
    ~Engine();

    /* ****************************************************************************************
     * Accessors & Mutators
     * ****************************************************************************************/
    const Difficulty&   difficulty()    { return *m_difficulty; }

    /* ****************************************************************************************
     * Public Functions
     * ****************************************************************************************/
    void on         ();
//  void off        ();

private:
    /* ****************************************************************************************
     * Attributes
     * ****************************************************************************************/
    MineZone*           m_minezone;
    const Difficulty*   m_difficulty;

    /* ****************************************************************************************
     * Member Functions
     * ****************************************************************************************/
    void startGame  ();
    void win        ();
    void gameOver   ();
    void restart    ();

signals:
    void difficulty_changed(Difficulty& difficulty);

public slots:

};

#endif // ENGINE_H
