#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tabela_dzialania_widget.h"
#include <QDebug>
#include <QMessageBox>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Kalkulator zejscia z mielizny");

    // Tabela
    ui->tableWidget->setColumnCount(5);
    QStringList nazwy_kolumn;
    nazwy_kolumn << "Opis" << "Masa" << "X" << "Y" << "Z";
    ui->tableWidget->setHorizontalHeaderLabels(nazwy_kolumn);
    ui->tableWidget->horizontalHeader()->resizeSection(Kolumny::opis, 300);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    ui->Xp_wynik->setReadOnly(true);
    ui->Yp_wynik->setReadOnly(true);

    ui->srednia_srednich->setReadOnly(true);
    ui->srednia_srednich_po->setReadOnly(true);
    ui->Tp_wynik->setReadOnly(true);
    ui->Zmiana_Tp_wynik->setReadOnly(true);
    ui->GM_wynik->setReadOnly(true);
    ui->Sila_podparcia_wynik->setReadOnly(true);


    ui->lewy_przod_przed->setText("0");
    ui->lewy_srodek_przed->setText("0");
    ui->lewy_tyl_przed->setText("0");
    ui->prawy_przod_przed->setText("0");
    ui->prawy_srodek_przed->setText("0");
    ui->prawy_tyl_przed->setText("0");

    ui->lewy_przod_po->setText("0");
    ui->lewy_srodek_po->setText("0");
    ui->lewy_tyl_po->setText("0");
    ui->prawy_przod_po->setText("0");
    ui->prawy_srodek_po->setText("0");
    ui->prawy_tyl_po->setText("0");

    ui->gestosc_wody_po->setText(QString::number(statek_po_mieliznie.gestosc_wody));
    ui->gestosc_wody_przed->setText(QString::number(statek_przed_mielizna.gestosc_wody));

    ui->KG_przed->setText(QString::number(statek_przed_mielizna.KG, 'f', 2));


    bool plik_wczytany = wczytaj_dane();
    if(plik_wczytany == false)
    {
        QMessageBox message_box;
        message_box.critical(0, "Blad z plikiem", "Nie udalo sie wczytac krzywych hydrostatycznych z pliku. Upewnij sie ze plik jest w dobrym folderze i nazywa sie AKH.txt");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::oblicz_przed_mielizna()
{
    statek_przed_mielizna.oblicz_srednie();
    statek_przed_mielizna.przypisz_wartosci_z_pliku(true);
    D_globalne = statek_po_mieliznie.wypornosc;
    statek_po_mieliznie.oblicz_Xp(statek_przed_mielizna, statek_po_mieliznie);
    statek_po_mieliznie.oblicz_Yp(statek_przed_mielizna);
    statek_przed_mielizna.oblicz_zanurzenie_nad_punktem_podparcia(statek_po_mieliznie);
    statek_po_mieliznie.oblicz_zanurzenie_nad_punktem_podparcia(statek_po_mieliznie);

    QString srednia_srednich_qstr = QString::number(statek_przed_mielizna.srednia_srednich, 'f', 2);
    ui->srednia_srednich->setText(srednia_srednich_qstr);
    ui->Xp_wynik->setText(QString::number(statek_po_mieliznie.Xp, 'f', 2));
    ui->Yp_wynik->setText(QString::number(statek_po_mieliznie.Yp, 'f', 2));
    ui->Tp_wynik->setText(QString::number(statek_przed_mielizna.Tp, 'f', 2));
}

void MainWindow::oblicz_po_mieliznie()
{
    statek_po_mieliznie.oblicz_srednie();
    statek_po_mieliznie.przypisz_wartosci_z_pliku(false);
    D_globalne = statek_po_mieliznie.wypornosc;
    statek_po_mieliznie.oblicz_Xp(statek_przed_mielizna, statek_po_mieliznie);
    statek_po_mieliznie.oblicz_Yp(statek_przed_mielizna);
    statek_przed_mielizna.oblicz_zanurzenie_nad_punktem_podparcia(statek_po_mieliznie);
    statek_po_mieliznie.oblicz_zanurzenie_nad_punktem_podparcia(statek_po_mieliznie);

    QString srednia_srednich_qstr = QString::number(statek_po_mieliznie.srednia_srednich, 'f', 2);
    ui->srednia_srednich_po->setText(srednia_srednich_qstr);
    ui->Xp_wynik->setText(QString::number(statek_po_mieliznie.Xp, 'f', 2));
    ui->Yp_wynik->setText(QString::number(statek_po_mieliznie.Yp, 'f', 2));
    ui->Tp_wynik->setText(QString::number(statek_przed_mielizna.Tp, 'f', 2));
}

void MainWindow::on_lewy_przod_przed_editingFinished()
{
    QString liczba_qstr = ui->lewy_przod_przed->text();
    bool success;

    double liczba = liczba_qstr.toDouble(&success);
    if(liczba > max_range_GUI || success == false)
    {
        ui->lewy_przod_przed->setText(QString::number(statek_przed_mielizna.lewy_przod));
        return;
    }

    statek_przed_mielizna.lewy_przod = liczba;

    oblicz_przed_mielizna();
}

void MainWindow::on_lewy_srodek_przed_editingFinished()
{
    QString liczba_qstr = ui->lewy_srodek_przed->text();
    bool success;

    double liczba = liczba_qstr.toDouble(&success);
    if(liczba > max_range_GUI || success == false)
    {
        ui->lewy_srodek_przed->setText(QString::number(statek_przed_mielizna.lewy_srodek));
        return;
    }

    statek_przed_mielizna.lewy_srodek = liczba;
    oblicz_przed_mielizna();
}

void MainWindow::on_lewy_tyl_przed_editingFinished()
{
    QString liczba_qstr = ui->lewy_tyl_przed->text();
    bool success;

    double liczba = liczba_qstr.toDouble(&success);
    if(liczba > max_range_GUI || success == false)
    {
        ui->lewy_tyl_przed->setText(QString::number(statek_przed_mielizna.lewy_tyl));
        return;
    }

    statek_przed_mielizna.lewy_tyl = liczba;
    oblicz_przed_mielizna();
}

void MainWindow::on_prawy_przod_przed_editingFinished()
{
    QString liczba_qstr = ui->prawy_przod_przed->text();
    bool success;

    double liczba = liczba_qstr.toDouble(&success);
    if(liczba > max_range_GUI || success == false)
    {
        ui->prawy_przod_przed->setText(QString::number(statek_przed_mielizna.lewy_przod));
        return;
    }

    statek_przed_mielizna.prawy_przod = liczba;
    oblicz_przed_mielizna();
}

void MainWindow::on_prawy_srodek_przed_editingFinished()
{
    QString liczba_qstr = ui->prawy_srodek_przed->text();
    bool success;

    double liczba = liczba_qstr.toDouble(&success);
    if(liczba > max_range_GUI || success == false)
    {
        ui->prawy_srodek_przed->setText(QString::number(statek_przed_mielizna.lewy_przod));
        return;
    }

    statek_przed_mielizna.prawy_srodek = liczba;
    oblicz_przed_mielizna();
}

void MainWindow::on_prawy_tyl_przed_editingFinished()
{
    QString liczba_qstr = ui->prawy_tyl_przed->text();
    bool success;

    double liczba = liczba_qstr.toDouble(&success);
    if(liczba > max_range_GUI || success == false)
    {
        ui->prawy_tyl_przed->setText(QString::number(statek_przed_mielizna.prawy_tyl));
        return;
    }

    statek_przed_mielizna.prawy_tyl = liczba;
    oblicz_przed_mielizna();
}

void MainWindow::on_lewy_przod_po_editingFinished()
{
    QString liczba_qstr = ui->lewy_przod_po->text();
    bool success;

    double liczba = liczba_qstr.toDouble(&success);
    if(liczba > max_range_GUI || success == false)
    {
        ui->lewy_przod_po->setText(QString::number(statek_po_mieliznie.lewy_przod));
        return;
    }

   statek_po_mieliznie.lewy_przod = liczba;
   oblicz_po_mieliznie();
}

void MainWindow::on_lewy_srodek_po_editingFinished()
{
    QString liczba_qstr = ui->lewy_srodek_po->text();
    bool success;

    double liczba = liczba_qstr.toDouble(&success);
    if(liczba > max_range_GUI || success == false)
    {
        ui->lewy_srodek_po->setText(QString::number(statek_po_mieliznie.lewy_srodek));
        return;
    }

    statek_po_mieliznie.lewy_srodek = liczba;
    oblicz_po_mieliznie();
}

void MainWindow::on_lewy_tyl_po_editingFinished()
{
    QString liczba_qstr = ui->lewy_tyl_po->text();
    bool success;

    double liczba = liczba_qstr.toDouble(&success);
    if(liczba > max_range_GUI || success == false)
    {
        ui->lewy_tyl_po->setText(QString::number(statek_po_mieliznie.lewy_tyl));
        return;
    }

    statek_po_mieliznie.lewy_tyl = liczba;
    oblicz_po_mieliznie();
}

void MainWindow::on_prawy_przod_po_editingFinished()
{
    QString liczba_qstr = ui->prawy_przod_po->text();
    bool success;

    double liczba = liczba_qstr.toDouble(&success);
    if(liczba > max_range_GUI || success == false)
    {
        ui->prawy_przod_po->setText(QString::number(statek_po_mieliznie.prawy_przod));
        return;
    }

    statek_po_mieliznie.prawy_przod = liczba;
    oblicz_po_mieliznie();
}

void MainWindow::on_prawy_srodek_po_editingFinished()
{
    QString liczba_qstr = ui->prawy_srodek_po->text();
    bool success;

    double liczba = liczba_qstr.toDouble(&success);
    if(liczba > max_range_GUI || success == false)
    {
        ui->prawy_srodek_po->setText(QString::number(statek_po_mieliznie.prawy_srodek));
        return;
    }

    statek_po_mieliznie.prawy_srodek = liczba;
    oblicz_po_mieliznie();
}

void MainWindow::on_prawy_tyl_po_editingFinished()
{
    QString liczba_qstr = ui->prawy_tyl_po->text();
    bool success;

    double liczba = liczba_qstr.toDouble(&success);
    if(liczba > max_range_GUI || success == false)
    {
        ui->prawy_tyl_po->setText(QString::number(statek_po_mieliznie.prawy_tyl));
        return;
    }

    statek_po_mieliznie.prawy_tyl = liczba;
    oblicz_po_mieliznie();
}

void MainWindow::on_Oblicz_zmiane_clicked()
{
    Delta_Tp_raz_policzona = true;
    Delta_D_raz_policzona = true;

    oblicz_zmiane_zanurzenia_w_punkcie_podparcia(statek_przed_mielizna, statek_po_mieliznie);
    oblicz_roznice_wypornosci(statek_przed_mielizna, statek_po_mieliznie);
    ui->Zmiana_Tp_wynik->setText(QString::number(Delta_Tp, 'f', 2));
    ui->Sila_podparcia_wynik->setText(QString::number(Delta_D, 'f', 2));
    ui->GM_wynik->setText(QString::number(statek_po_mieliznie.GM, 'f', 2));

    ui->Oblicz_zmiane->setEnabled(false);
}

void MainWindow::on_gestosc_wody_przed_editingFinished()
{
    QString liczba_qstr = ui->gestosc_wody_przed->text();
    bool success;

    double liczba = liczba_qstr.toDouble(&success);
    if(liczba > max_range_GUI || success == false)
    {
        ui->gestosc_wody_przed->setText(QString::number(statek_przed_mielizna.gestosc_wody));
        return;
    }

    statek_przed_mielizna.gestosc_wody = liczba;
    oblicz_przed_mielizna();
}

void MainWindow::on_gestosc_wody_po_editingFinished()
{
    QString liczba_qstr = ui->gestosc_wody_po->text();
    bool success;

    double liczba = liczba_qstr.toDouble(&success);
    if(liczba > max_range_GUI || success == false)
    {
        ui->gestosc_wody_po->setText(QString::number(statek_po_mieliznie.gestosc_wody));
        return;
    }

    statek_po_mieliznie.gestosc_wody = liczba;
    oblicz_po_mieliznie();
}

void MainWindow::on_KG_przed_editingFinished()
{
    QString liczba_qstr = ui->KG_przed->text();
    bool success;

    double liczba = liczba_qstr.toDouble(&success);
    if(liczba > max_range_GUI || success == false)
    {
        ui->KG_przed->setText(QString::number(statek_przed_mielizna.KG, 'f', 2));
        return;
    }

    statek_przed_mielizna.KG = liczba;
    oblicz_przed_mielizna();
}

// https://www.youtube.com/watch?v=XintqJlSY1U - TUTORIAL
void MainWindow::on_dodaj_do_tabeli_clicked()
{
    int wynik;
    int rzad;

    // Wlacza nowe okno
    tabela_dzialania_widget tabelka(this);
    wynik = tabelka.exec();

    // Jesli uzytkownik wcisnal Cancel
    if(wynik == QDialog::Rejected)
    {
        return;
    }

    QString opis = tabelka.zwroc_opis();
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    rzad = ui->tableWidget->rowCount() -1;
    ui->tableWidget->setItem(rzad, Kolumny::opis, new QTableWidgetItem(opis));

    QString masa_qstr = tabelka.zwroc_mase();
    ui->tableWidget->setItem(rzad, Kolumny::masa, new QTableWidgetItem(masa_qstr));

    QString X_qstr = tabelka.zwroc_X();
    ui->tableWidget->setItem(rzad, Kolumny::X, new QTableWidgetItem(X_qstr));

    QString Y_qstr = tabelka.zwroc_Y();
    ui->tableWidget->setItem(rzad, Kolumny::Y, new QTableWidgetItem(Y_qstr));

    QString Z_qstr = tabelka.zwroc_Z();
    ui->tableWidget->setItem(rzad, Kolumny::Z, new QTableWidgetItem(Z_qstr));

    obliczenia_uzytkownika::m = masa_qstr.toDouble();
    obliczenia_uzytkownika::x = X_qstr.toDouble();
    obliczenia_uzytkownika::y = Y_qstr.toDouble();
    obliczenia_uzytkownika::z = Z_qstr.toDouble();

    Delta_D_po_dzialaniu_uzytkownika = true;
    Delta_Tp_po_dzialaniu_uzytkownika = true;

    oblicz_roznice_wypornosci(statek_przed_mielizna, statek_po_mieliznie);
    statek_po_mieliznie.GM = oblicz_GM_na_podstawie_Km_i_KG_globalne();

    ui->Zmiana_Tp_wynik->setText(QString::number(Delta_Tp, 'f', 2));
    ui->Sila_podparcia_wynik->setText(QString::number(Delta_D, 'f', 2));
    ui->GM_wynik->setText(QString::number(statek_po_mieliznie.GM, 'f', 2));


    Delta_D_po_dzialaniu_uzytkownika = false;
    Delta_Tp_po_dzialaniu_uzytkownika = false;
}


