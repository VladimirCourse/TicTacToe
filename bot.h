#ifndef BOT_H
#define BOT_H

#include <QObject>
#include "constraints.h"

class Bot : public QObject{
    Q_OBJECT

private:
    int m_x;
    int m_y;
    int m_moveCount;
    int m_field[FIELD_SIZE][FIELD_SIZE];
    bool m_type;

    bool checkEnd();
    bool tryWin(int player);

    QString m_action;

    int countFigInCorner();
    int findMove(int move);

    void formAction(QString reason);
    void placeXY(int x, int y);
    void findCross();
    void placeNearEnemy();
    void strategy();

public:
    explicit Bot(QObject *parent = 0);
    bool getType();
    void setType(bool type);
    void move(int moveCount, int field[FIELD_SIZE][FIELD_SIZE]);
    int getX();
    int getY();
    QString getAction();
    ~Bot();

signals:

public slots:

};

#endif // BOT_H
