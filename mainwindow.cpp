#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "optiondialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);

    m_game = new Game(this);
    for (int i = 0; i < FIELD_SIZE; i++){
        for (int k = 0; k < FIELD_SIZE; k++){
            Figure *fig = new Figure(k, i, this);
            fig->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
            ui->gridLayout_4->addWidget(fig, k, i);
            m_figures[k][i] = fig;
            QObject::connect(fig, SIGNAL(clicked(int, int)), this, SLOT(onCellClick(int,int)));
        }
    }
    showOptionDialog();
}

void MainWindow::showOptionDialog(){
    OptionDialog *dlg = new OptionDialog(this);
    dlg->exec();
    int type = dlg->getType();
    //задаем рандомно крестик или нолик
    if (type == EMPTY){
        QTime midnight(0,0,0);
        qsrand(midnight.secsTo(QTime::currentTime()));
        type = qrand()%2 + 1;
    }
    if (type == CIRCLE){
        m_game->setBotType(CROSS - 1);
        ui->listWidget->addItem(m_game->getBotAction());
    }else m_game->setBotType(CIRCLE - 1);
}

void MainWindow::drawField(QPainter &painter){
    int w = (this->width() - BOT_WND_W)/FIELD_SIZE;
    int h = this->height()/FIELD_SIZE;
    //рисуем сетку поля
    painter.setPen(QPen(Qt::black, 3));
    for (int i = 1; i < FIELD_SIZE; i++){
        painter.drawLine(i*w , FIELD_BORDER, i*w, this->height() - FIELD_BORDER);
        painter.drawLine(FIELD_BORDER, i*h, this->width() - BOT_WND_W - FIELD_BORDER, i*h);
    }
    //рисуем крестики-нолики
    int field[FIELD_SIZE][FIELD_SIZE];
    m_game->getField(field);
    for (int i = 0; i < FIELD_SIZE; i++){
        for (int k = 0; k < FIELD_SIZE; k++){
            int toW = w*i + w/2;
            int toH = h*k + h/2;
            if (field[k][i] == CROSS){
                painter.setPen(QPen(Qt::red, 7));
                painter.drawLine(toW - FIG_SIZE, toH - FIG_SIZE, toW + FIG_SIZE, toH + FIG_SIZE);
                painter.drawLine(toW - FIG_SIZE, toH + FIG_SIZE, toW + FIG_SIZE, toH - FIG_SIZE);
            }else if (field[k][i] == CIRCLE){
                painter.setPen(QPen(Qt::blue, 7));
                painter.drawEllipse(QPoint(toW, toH), FIG_SIZE,  FIG_SIZE);
            }
        }
    }
}

void MainWindow::drawWin(QPainter &painter){
    int crossType = m_game->getWinType();
    int point = m_game->getWinPoint() - 1;
    int w = (this->width() - BOT_WND_W);
    int h = this->height();
    int toW = w/FIELD_SIZE * point + w/2;
    int toH = h/FIELD_SIZE * point + h/2;
    painter.setPen(QPen(Qt::black, 5));
    switch(crossType){
    //рисуем вертикальную линию
    case VERT:
        painter.drawLine(toW, FIELD_BORDER, toW, h - FIELD_BORDER);
        break;
        //рисуем горизонтальную линию
    case HORIZ:
        painter.drawLine(FIELD_BORDER, toH, w - FIELD_BORDER, toH);
        break;
        //рисуем диагональную линию слева направо
    case DIAG_L:
        painter.drawLine(FIELD_BORDER, FIELD_BORDER, w - FIELD_BORDER, h - FIELD_BORDER);
        break;
        //рисуем диагональную линию справа налево
    case DIAG_R:
        painter.drawLine(w - FIELD_BORDER, FIELD_BORDER, FIELD_BORDER, h - FIELD_BORDER);
        break;
    }
}

void MainWindow::onCellClick(int x, int y){
    if (m_game->playerMove(x, y)){
        if (!m_game->isEnded()){
            ui->listWidget->addItem(m_game->getBotAction());
        }else{
            if (m_game->getWinType() != DRAW){
                if (m_game->isPlayerWin()) ui->listWidget->addItem("Вы выиграли :(");
                else ui->listWidget->addItem("Я выиграл :)");
            }else{
                ui->listWidget->addItem("Ничья :|");
            }
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Сыграем еще раз?", "Сыграем еще раз?", QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                ui->listWidget->clear();
                m_game->restart();
                showOptionDialog();
            } else {
                QApplication::quit();
            }
        }
        this->repaint();
    }
}

void MainWindow::paintEvent(QPaintEvent * event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    drawField(painter);
    if (m_game->isEnded()){
        drawWin(painter);
    }
}


MainWindow::~MainWindow(){
    delete ui;
    delete m_game;
}

