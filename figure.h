#ifndef FIGURE_H
#define FIGURE_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include "constraints.h"

class Figure : public QWidget{
    Q_OBJECT

private:
    int m_x;
    int m_y;

protected:
    virtual void mousePressEvent(QMouseEvent * event);

public:
    explicit Figure(int x, int y, QWidget *parent = 0);
    ~Figure();

signals:
    void clicked(int x, int y);


};

#endif // FIGURE_H
