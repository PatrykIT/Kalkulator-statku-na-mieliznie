#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "statek.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum Kolumny
    {
        opis, masa, X, Y, Z
    };

    void oblicz_przed_mielizna();
    void oblicz_po_mieliznie();


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Zanurzenie statek_przed_mielizna, statek_po_mieliznie;

private slots:
    void on_lewy_przod_przed_editingFinished();

    void on_lewy_srodek_przed_editingFinished();

    void on_lewy_tyl_przed_editingFinished();

    void on_prawy_przod_przed_editingFinished();

    void on_prawy_srodek_przed_editingFinished();

    void on_prawy_tyl_przed_editingFinished();

    void on_lewy_przod_po_editingFinished();

    void on_lewy_srodek_po_editingFinished();

    void on_lewy_tyl_po_editingFinished();

    void on_prawy_przod_po_editingFinished();

    void on_prawy_srodek_po_editingFinished();

    void on_prawy_tyl_po_editingFinished();

    void on_Oblicz_zmiane_clicked();

    void on_gestosc_wody_przed_editingFinished();

    void on_gestosc_wody_po_editingFinished();

    void on_KG_przed_editingFinished();

    void on_dodaj_do_tabeli_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
