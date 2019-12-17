#ifndef TABELA_DZIALANIA_WIDGET_H
#define TABELA_DZIALANIA_WIDGET_H

#include <QDialog>

namespace Ui {
class tabela_dzialania_widget;
}

class tabela_dzialania_widget : public QDialog
{
    Q_OBJECT

public:
    explicit tabela_dzialania_widget(QWidget *parent = 0);
    ~tabela_dzialania_widget();

    QString zwroc_opis() const;

    QString zwroc_mase() const;
    QString zwroc_X() const;
    QString zwroc_Y() const;
    QString zwroc_Z() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::tabela_dzialania_widget *ui;
};

#endif // TABELA_DZIALANIA_WIDGET_H
