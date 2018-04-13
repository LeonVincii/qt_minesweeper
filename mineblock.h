#ifndef MINEBLOCK_H
#define MINEBLOCK_H

#include <QObject>

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
    int     id      ()  { return m_id; }
    bool    isMine  ()  { return m_is_mine; }
    int     value   ()  { return m_value; }

    void    setNeighbors(MineBlock* top_left,
                         MineBlock* top,
                         MineBlock* top_right,
                         MineBlock* left,
                         MineBlock* right,
                         MineBlock* btm_left,
                         MineBlock* btm,
                         MineBlock* btm_right);
    void    setMine (bool is_mine);
    void    setValue();

    /* ****************************************************************************************
     * Public Functions
     * ****************************************************************************************/
    int     reveal  ();

private:
    /* ****************************************************************************************
     * Attributes
     * ****************************************************************************************/
    MineBlock*  m_top_left_block;
    MineBlock*  m_top_block;
    MineBlock*  m_top_right_block;
    MineBlock*  m_left_block;
    MineBlock*  m_right_block;
    MineBlock*  m_btm_left_block;
    MineBlock*  m_btm_block;
    MineBlock*  m_btm_right_block;

    int     m_id;
    int     m_value;
    bool    m_is_mine;

signals:

public slots:

};

#endif // MINEBLOCK_H
