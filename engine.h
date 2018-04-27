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
    ~Engine();

    /* ****************************************************************************************
     * Accessors & Mutators
     * ****************************************************************************************/
    int time      () const { return m_time;                     }
    int row       () const { return m_difficulty->height;       }
    int col       () const { return m_difficulty->width;        }
    int numOfMines() const { return m_difficulty->num_of_mines; }

    /* ****************************************************************************************
     * Public Functions
     * ****************************************************************************************/
    void startGame       ();
    void restartGame     ();
    void changeDifficulty(const Difficulty* difficulty);
    void revealBlock     (int id);
    void markBlock       (int id);
    int  valueAtId       (int id) const;
    int  flagsLeft       ()       const { return m_minezone->flags(); }

private:
    /* ****************************************************************************************
     * Attributes
     * ****************************************************************************************/
    MineZone*           m_minezone;
    const Difficulty*   m_difficulty;
    QTimer*             m_timer;
    int                 m_time;

    /* ****************************************************************************************
     * Member Functions
     * ****************************************************************************************/
    int coord2Id(int x, int y);

signals:
    void timeout            ();
    void updateMineZoneView (Qt::MouseButton btn, QVector<int> ids);
    void win                (Qt::MouseButton btn, QVector<int> ids);
    void gameOver           ();

private slots:
    void on_timeout ();

};

#endif // ENGINE_H
