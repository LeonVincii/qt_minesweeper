#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QDebug>

struct Difficulty {
    std::string difficulty;
    int     dimension;
    int     num_of_mines;
};

const Difficulty EASY   = { "easy"  ,    9, 10 };
const Difficulty NORMAL = { "normal",   16, 40 };
const Difficulty HARD   = { "hard"  ,   22, 99 };

class MineZone;

class Engine : public QObject
{
    Q_OBJECT

public:
    /* ****************************************************************************************
     * Constructor
     * ****************************************************************************************/
    explicit Engine(QObject *parent = nullptr);

    /* ****************************************************************************************
     * Accessors & Mutators
     * ****************************************************************************************/
    static Engine*      instance();
    const Difficulty&   difficulty() const { return m_current_difficulty; }
    void                setDifficulty(const Difficulty& difficulty);

    /* ****************************************************************************************
     * Public Functions
     * ****************************************************************************************/
    void start      ();
    void gameOver   ();
    void restart    ();

private:
    /* ****************************************************************************************
     * Attributes
     * ****************************************************************************************/
    static Engine*  m_instance;
    Difficulty      m_current_difficulty;
    const MineZone* m_minezone;

    /* ****************************************************************************************
     * Member Functions
     * ****************************************************************************************/
    void initMineZone(int dimension);

signals:

public slots:

};

#endif // ENGINE_H
