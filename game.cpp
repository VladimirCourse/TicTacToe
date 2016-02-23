#include "game.h"

Game::Game(QObject *parent) : QObject(parent){
    restart();
}

void Game::restart(){
    m_currentPlayer = false;
    m_moveCount = 0;
    m_winType = 0;
    m_winPoint = 0;
    for (int i = 0; i < FIELD_SIZE; i++){
        for (int k = 0; k < FIELD_SIZE; k++){
            m_field[k][i] = EMPTY;
        }
    }
}

void Game::setBotType(bool type){
    m_bot.setType(type);
    if (type + 1 == CROSS){
        m_bot.move(m_moveCount, m_field);
        move(m_bot.getX(), m_bot.getY());
    }
}

//проверка на конец игры, если конец, задать тип зачеркивания (горизонтальный, вертикальный, диагональный)
bool Game::checkEnd(){
    for (int i = 0; i < FIELD_SIZE; i++){
        if (m_field[i][0] != EMPTY && m_field[i][0] == m_field[i][1] && m_field[i][0] == m_field[i][2]){
            m_winType = HORIZ;
            m_winPoint = i;
            return true;
        }
        if (m_field[0][i] != EMPTY && m_field[0][i] == m_field[1][i] && m_field[0][i] == m_field[2][i]){
            m_winType = VERT;
            m_winPoint = i;
            return true;
        }
    }
    if (m_field[0][0] != EMPTY && m_field[0][0] == m_field[1][1] && m_field[0][0] == m_field[2][2]){
        m_winType = DIAG_L;
        return true;
    }
    if (m_field[2][0] != EMPTY && m_field[2][0] == m_field[1][1] && m_field[2][0] == m_field[0][2]){
        m_winType = DIAG_R;
        return true;
    }
    return false;
}

bool Game::isPlayerWin(){
    return m_currentPlayer == m_bot.getType();
}

bool Game::isEnded(){
    return m_moveCount == MAX_MOVE_COUNT;
}

int Game::getWinType(){
    return m_winType;
}

int Game::getWinPoint(){
    return m_winPoint;
}

void Game::getField(int field[FIELD_SIZE][FIELD_SIZE]){
     memcpy(field, m_field, sizeof(int[FIELD_SIZE][FIELD_SIZE]));
}

//ход игрока или бота
void Game::move(int x, int y){
     m_field[x][y] = m_currentPlayer + 1;
     m_currentPlayer = !m_currentPlayer;
     m_moveCount++;
     if (checkEnd()){
         m_moveCount = MAX_MOVE_COUNT;
     }else if (isEnded()){
         m_winType = DRAW;
     }
}

bool Game::playerMove(int x, int y){
    if (m_field[x][y] == EMPTY && m_moveCount < MAX_MOVE_COUNT){
        move(x, y);
        if (m_moveCount < MAX_MOVE_COUNT){
            m_bot.move(m_moveCount, m_field);
            move(m_bot.getX(), m_bot.getY());
        }
        return true;
    }
    return false;
}

QString Game::getBotAction(){
    return m_bot.getAction();
}

Game::~Game(){

}

