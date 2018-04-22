#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QDebug>

struct Difficulty;

class MineZone;

class Engine : public QObject
{
    Q_OBJECT

public:
    /* ****************************************************************************************
     * Accessors & Mutators
     * ****************************************************************************************/
    static Engine*      instance();

    /* ****************************************************************************************
     * Public Functions
     * ****************************************************************************************/
    void on         ();
//  void off        ();

private:
    /* ****************************************************************************************
     * Constructor & Destructor
     * ****************************************************************************************/
    explicit Engine(QObject *parent = nullptr);
    virtual ~Engine();

    /* ****************************************************************************************
     * Attributes
     * ****************************************************************************************/
    static Engine*      m_instance;
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

public slots:

};

#endif // ENGINE_H
