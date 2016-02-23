#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QDebug>
#include "constraints.h"
#include "bot.h"

class Game : public QObject{
    Q_OBJECT

private:
    Bot m_bot;
    bool m_currentPlayer;
    int m_field[FIELD_SIZE][FIELD_SIZE];
    int m_moveCount;
    int m_winType;
    int m_winPoint;

    bool checkEnd();
    void move(int x, int y);

public:
    explicit Game(QObject *parent = 0);
    bool isEnded();
    bool isPlayerWin();
    bool playerMove(int x, int y);
    int getWinType();
    int getWinPoint();
    QString getBotAction();
    void getField(int field[FIELD_SIZE][FIELD_SIZE]);
    void restart();
    void setBotType(bool type);
    ~Game();
};

#endif // GAME_H
