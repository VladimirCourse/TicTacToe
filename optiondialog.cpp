#include "optiondialog.h"
#include "ui_optiondialog.h"

OptionDialog::OptionDialog(QWidget *parent) : QDialog(parent), ui(new Ui::OptionDialog){
    ui->setupUi(this);
    m_type = EMPTY;
}

OptionDialog::~OptionDialog(){
    delete ui;
}

int OptionDialog::getType(){
    return m_type;
}

void OptionDialog::on_radioButton_clicked(){
    m_type = CROSS;
}

void OptionDialog::on_radioButton_2_clicked(){
    m_type = CIRCLE;
}

void OptionDialog::on_radioButton_3_clicked(){
    m_type = EMPTY;
}

void OptionDialog::on_pushButton_clicked(){
    close();
}
