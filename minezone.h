#ifndef MINEZONE_H
#define MINEZONE_H

#include <QObject>
#include <QVector>
#include <QTimer>

struct Difficulty {
    std::string difficulty;
    int         height;
    int         width;
    int         num_of_mines;
};

const Difficulty EASY   = { "easy"  ,  9,  9, 10 };
const Difficulty NORMAL = { "normal", 16, 16, 40 };
const Difficulty HARD   = { "hard"  , 16, 30, 99 };

class MineBlock;

class MineZone : public QObject
{
    Q_OBJECT

    typedef QVector<MineBlock*> MineBlockArr;

public:
    /* ****************************************************************************************
     * Constructor & Destructor
     * ****************************************************************************************/
    explicit MineZone(QObject *parent = nullptr, const Difficulty* difficulty = &EASY);
    ~MineZone();

    /* ****************************************************************************************
     * Accessors & Mutators
     * ****************************************************************************************/
    const Difficulty&   difficulty  () const   { return *m_difficulty;    }
    const MineBlockArr& mineBlocks  () const   { return *m_mine_blocks;   }
    int                 countdown   ()         { return  m_countdown;     }
    int                 flags       ()         { return  m_flagCountdown; }

    void setDifficulty      (const Difficulty* difficulty);

    /* ****************************************************************************************
     * Public Functions
     * ****************************************************************************************/
    void displayDifficulty  ();
    void initMines          ();
    bool revealBlock        (int x, int y);
    void markBlock          (int x, int y);
    void drawBlocks         ();
    void cheat_showMines    ();

private:
    /* ****************************************************************************************
     * Attributes
     * ****************************************************************************************/
    static MineZone*    m_instance;
    const Difficulty*   m_difficulty;
    MineBlockArr*       m_mine_blocks;
    QTimer*             m_timer;
    int                 m_time;
    int                 m_countdown;
    int                 m_flagCountdown;
};

#endif // MINEZONE_H
