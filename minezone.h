#ifndef MINEZONE_H
#define MINEZONE_H

#include <QObject>
#include <QVector>

class MineBlock;

class MineZone : public QObject
{
    Q_OBJECT

    typedef QVector<MineBlock*> MineBlockArr;

public:
    /* ****************************************************************************************
     * Constructor
     * ****************************************************************************************/
    explicit MineZone(QObject *parent = nullptr, int dimension = 1);

    /* ****************************************************************************************
     * Accessors & Mutators
     * ****************************************************************************************/
    static MineZone*    instance(int dimension);
    int                 dimension()     const   { return m_dimension; }
    const MineBlockArr* mineBlocks()    const   { return m_mine_blocks; }

private:
    /* ****************************************************************************************
     * Attributes
     * ****************************************************************************************/
    static MineZone*    m_instance;
    int                 m_dimension;
    MineBlockArr*       m_mine_blocks;

signals:

public slots:

};

#endif // MINEZONE_H
