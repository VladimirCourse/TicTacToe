#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QMessageBox>
#include "figure.h"
#include "game.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    Game *m_game;
    Figure *m_figures[FIELD_SIZE][FIELD_SIZE];

    void drawField(QPainter &painter);
    void drawWin(QPainter &painter);
    void showOptionDialog();

protected:
    virtual void paintEvent(QPaintEvent * event);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onCellClick(int x, int y);

};

#endif // MAINWINDOW_H
