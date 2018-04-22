#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QTimer>

#include "minezone.h"

class Engine : public QObject
{
    Q_OBJECT

public:
    /* ****************************************************************************************
     * Constructor & Destructor
     * ****************************************************************************************/
    explicit Engine (QObject *parent = nullptr);
    ~Engine         ();

    /* ****************************************************************************************
     * Accessors & Mutators
     * ****************************************************************************************/
    int time        () const { return m_time; }

    /* ****************************************************************************************
     * Public Functions
     * ****************************************************************************************/
    void startGame  ();
    void restartGame();

private:
    /* ****************************************************************************************
     * Attributes
     * ****************************************************************************************/
    MineZone*           m_minezone;
    const Difficulty*   m_difficulty;
    QTimer*             m_timer;
    int                 m_time;

signals:
    void timeout    ();

private slots:
    void on_timeout ();

};

#endif // ENGINE_H
