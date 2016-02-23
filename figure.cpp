#include "figure.h"

Figure::Figure(int x, int y, QWidget *parent) : m_x(x), m_y(y), QWidget(parent){

}


void Figure::mousePressEvent(QMouseEvent *event){
    clicked(m_x, m_y);
}

Figure::~Figure(){

}

