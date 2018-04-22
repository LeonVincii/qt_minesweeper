#ifndef MINEBLOCK_H
#define MINEBLOCK_H

#include <QObject>

enum BlockState { NONE, REVEALED, MARKED };

class MineBlock : public QObject
{
    Q_OBJECT

public:
    /* ****************************************************************************************
     * Constructor & Destructor
     * ****************************************************************************************/
    explicit MineBlock(QObject *parent = nullptr, int id = 0);
    ~MineBlock();

    /* ****************************************************************************************
     * Accessors & Mutators
     * ****************************************************************************************/
    int         id       ()  { return m_id;        }
    int         value    ()  { return m_value;     }
    bool        isMine   ()  { return m_is_mine;   }
    BlockState  state    ()  { return m_state;     }

    typedef     MineBlock*   (*Neighbors)[8];
    Neighbors   neighbors()  { return &m_neighbors; }

    void    setNeighbors( MineBlock* top_left,
                          MineBlock* top,
                          MineBlock* top_right,
                          MineBlock* left,
                          MineBlock* right,
                          MineBlock* btm_left,
                          MineBlock* btm,
                          MineBlock* btm_right );
    void    setMine (bool is_mine);
    void    setValue();

    /* ****************************************************************************************
     * Public Functions
     * ****************************************************************************************/
    int     reveal  ();
    int     mark    ();
    void    draw    ();

private:
    /* ****************************************************************************************
     * Attributes
     * ****************************************************************************************/
    int         m_id;
    int         m_value;
    bool        m_is_mine;
    MineBlock*  m_neighbors[8];
    BlockState  m_state;

signals:

public slots:

};

#endif // MINEBLOCK_H
