#ifndef OPTIONDIALOG_H
#define OPTIONDIALOG_H

#include <QDialog>
#include "constraints.h"

namespace Ui {
class OptionDialog;
}

class OptionDialog : public QDialog{
    Q_OBJECT

public:
    explicit OptionDialog(QWidget *parent = 0);
    int getType();
    ~OptionDialog();

private slots:
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_radioButton_3_clicked();
    void on_pushButton_clicked();

private:
    Ui::OptionDialog *ui;
    int m_type;
};

#endif // OPTIONDIALOG_H
