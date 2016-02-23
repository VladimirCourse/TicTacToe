#include "bot.h"

#include <QDebug>

Bot::Bot(QObject *parent) : QObject(parent){

}
//проверить, конец ли игры
bool Bot::checkEnd(){
    for (int i = 0; i < FIELD_SIZE; i++){
        if (m_field[i][0] != EMPTY && m_field[i][0] == m_field[i][1] && m_field[i][0] == m_field[i][2]) return true;
        if (m_field[0][i] != EMPTY && m_field[0][i] == m_field[1][i] && m_field[0][i] == m_field[2][i]) return true;
    }
    if (m_field[0][0] != EMPTY && m_field[0][0] == m_field[1][1] && m_field[0][0] == m_field[2][2]) return true;
    if (m_field[2][0] != EMPTY && m_field[2][0] == m_field[1][1] && m_field[2][0] == m_field[0][2]) return true;
    return false;
}
//поиск лучшего возможного хода, рекурсивно проходим по всем возможным состояниям и
//и находим то, которое приведет к выигрышу с наименьшим кол-вом ходов
int Bot::findMove(int move){
    if (checkEnd()){
        if (move%2 == !m_type) return move;
        else return MAX_MOVE_COUNT;
    }
    if (move >= MAX_MOVE_COUNT) return MAX_MOVE_COUNT;
    int min = MAX_MOVE_COUNT;
    for (int i = 0; i < FIELD_SIZE; i++){
        for (int k = 0; k < FIELD_SIZE; k++){
            //если на поле ничего не стоит
            if (m_field[k][i] == EMPTY){
                int prev = m_field[k][i];
                //ставим туда крестик или нолик
                m_field[k][i] = move%2 + 1;
                //идем дальше, меняем игрока
                int moveCount = findMove(move + 1);
                //возвращаем состояние поля
                m_field[k][i] = prev;
                //ищем минимальный возможный ход
                if (moveCount <= min){
                    min = moveCount;
                    //если это первый ход, тогда задаем глобальные координаты
                    if (move == 1 || move == 0){
                        m_x = k;
                        m_y = i;
                    }
                }
            }
        }
    }
    return min;
}

void Bot::placeXY(int x, int y){
    m_x = x;
    m_y = y;
}
//найти первый попавшийся крестик
void Bot::findCross(){
    bool found = false;
    for (int i = 0; i < FIELD_SIZE; i++){
        for (int k = 0; k < FIELD_SIZE; k++){
            if (m_field[k][i] == !m_type + 1){
                m_x = k;
                m_y = i;
                found = true;
                break;
            }
        }
        if (found) break;
    }
}
//поставить рядом с клеткой врага
void Bot::placeNearEnemy(){
    if (m_x == FIELD_SIZE - 1) m_y++;
    else if (m_y == FIELD_SIZE - 1) m_x++;
    else m_x++;
}
//посчитать кол-во фигур в углах
int Bot::countFigInCorner(){
    int corner = 0;
    for (int i = 0; i < FIELD_SIZE; i+=2){
        for (int k = 0; k < FIELD_SIZE; k+=2){
            if (m_field[k][i] == !m_type + 1){
                corner++;
            }
        }
    }
    return corner;
}
//поиск возможной клетки, которая приведет к победе
bool Bot::tryWin(int player){
    for (int i = 0; i < FIELD_SIZE; i++){
        for (int k = 0; k < FIELD_SIZE; k++){
            if (m_field[k][i] == EMPTY){
                m_field[k][i] = player;
                if (checkEnd()){
                    m_x = k;
                    m_y = i;
                    return true;
                }
                m_field[k][i] = EMPTY;
            }
        }
    }
    return false;
}

void Bot::formAction(QString reason){
    m_action = "Я хожу в позицию (" + QString::number(m_y) + "," + QString::number(m_x) + ") т.к. " + reason;
}

QString Bot::getAction(){
    return m_action;
}

void Bot::strategy(){
    //начало игры
    if (m_moveCount == 1){
        findCross();
        //если пртивник поставил Х в центр, ставим 0 в угол
        if (m_x == 1 && m_y == 1){
            placeXY(0, 0);
            formAction("Вы поставили крестик в центр.");
            return;
        //если пртивник поставил Х в угол, ставим 0 в центр
        }else if ((m_x == 0 || m_x == 2) && (m_y == 0 || m_y == 2)){
            placeXY(1, 1);
            formAction("Вы поставили крестик в угол.");
            return;
        //иначе ставим 0 рядом с Х
        }else{
            placeNearEnemy();
            formAction("мне хочется поставить ноль рядом с Вашим крестиком.");
            return;
        }
    }
    /*else if (m_moveCount == 3){
        if (countFigInCorner() == 2){
            tryWin(CROSS);
            return;
        }
    }*/
    //пытаемся выиграть
    if (tryWin(m_type + 1)){
        formAction("я выиграю после этого хода.");
        return;
    }
    //пытаемся помешать противнику
    if (tryWin(!m_type + 1)){
        formAction("я хочу помешать тебе выиграть!");
        return;
    }
    //ищем возможный выгодный ход
    findMove(m_type);
    formAction("я просчитываю все ходы наперед и считаю, что мне надо ходить именно сюда.");
}

bool Bot::getType(){
    return m_type;
}

void Bot::setType(bool type){
    m_type = type;
}

void Bot::move(int moveCount, int field[FIELD_SIZE][FIELD_SIZE]){
    m_moveCount = moveCount;
    memcpy(m_field, field, sizeof(int[FIELD_SIZE][FIELD_SIZE]));
    strategy();
}

int Bot::getX(){
    return m_x;
}

int Bot::getY(){
    return m_y;
}

Bot::~Bot(){

}

