#include "tabela_dzialania_widget.h"
#include "ui_tabela_dzialania_widget.h"

tabela_dzialania_widget::tabela_dzialania_widget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tabela_dzialania_widget)
{
    ui->setupUi(this);
    setWindowTitle("Operacje na mieliznie");
}

tabela_dzialania_widget::~tabela_dzialania_widget()
{
    delete ui;
}

void tabela_dzialania_widget::on_buttonBox_accepted()
{
    accept();
}

void tabela_dzialania_widget::on_buttonBox_rejected()
{
    reject();
}

QString tabela_dzialania_widget::zwroc_opis() const
{
    return ui->opis_textEdit->toPlainText();
}

QString tabela_dzialania_widget::zwroc_mase() const
{
    return ui->masa_lineEdit->text();
}
QString tabela_dzialania_widget::zwroc_X() const
{
    return ui->X_lineEdit->text();
}
QString tabela_dzialania_widget::zwroc_Y() const
{
    return ui->Y_lineEdit->text();
}
QString tabela_dzialania_widget::zwroc_Z() const
{
    return ui->Z_lineEdit->text();
}
