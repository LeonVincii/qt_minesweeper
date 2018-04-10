#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>

struct Difficulty {
    int dimension;
    int num_of_mines;
};

const Difficulty EASY   = {  9, 10 };
const Difficulty NORMAL = { 16, 40 };
const Difficulty HARD   = { 22, 99 };

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
    const Difficulty& customDifficulty() const { return m_custom_difficulty; }

    void setCustomDifficulty(const Difficulty& difficulty);

    /* ****************************************************************************************
     * Public Functions
     * ****************************************************************************************/
    void start      (const Difficulty& difficulty);
    void gameOver   ();
    void restart    ();

private:
    /* ****************************************************************************************
     * Attributes
     * ****************************************************************************************/
    Difficulty m_custom_difficulty;

signals:

public slots:

};

#endif // ENGINE_H
