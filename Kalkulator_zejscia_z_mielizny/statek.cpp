#include "statek.h"
#include "Interpolacja.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

double Zanurzenie::B = 24.4;
double Zanurzenie::Lpp = 185;
double Zanurzenie::k = 1.005;
bool Zanurzenie::KG_globalne_zapisane = false;
double D_globalne = 0;
double KG_globalne = 0;
double Fw_D_globalne;
double KM_D_globalne;
double MJ_D_globalne;
double Xf_D_globalne;


double obliczenia_uzytkownika::m = 0;
double obliczenia_uzytkownika::x = 0;
double obliczenia_uzytkownika::y = 0;
double obliczenia_uzytkownika::z = 0;

double suma_mas_uzytkownika = 0;

double Delta_Tp;

bool Delta_Tp_raz_policzona = false;
bool Delta_Tp_po_dzialaniu_uzytkownika = false;

double Delta_D;
bool Delta_D_raz_policzona = false;
bool Delta_D_po_dzialaniu_uzytkownika = false;

std::vector<dane_z_pliku> AKH;

bool wczytaj_dane()
{
    const std::string file_path = "AKH.txt";
    ifstream plik;
    plik.open(file_path);
    if (plik.is_open() == false)
    {
        cout << "Nie mozna bylo otworzyc pliku!" << endl;
        return false;
    }

    while(plik.peek() != EOF)
    {
        dane_z_pliku dane; // to jest pojedyncza linijka
        plik >> dane.T >> dane.D >> dane.XF >> dane.KM >> dane.MJ >> dane.Fw;
        AKH.push_back(dane);
    }

    // Zapisujemy dane do interpolacji
    for (const dane_z_pliku &linijka : AKH)
    {
        xData_dla_T.emplace_back(linijka.T);
    }
    for (const dane_z_pliku &linijka : AKH)
    {
        xData_dla_D.emplace_back(linijka.D);
        yData_dla_D.emplace_back(linijka.D);
    }
    for (const dane_z_pliku &linijka : AKH)
    {
        yData_dla_MJ.emplace_back(linijka.MJ);
    }
    for (const dane_z_pliku &linijka : AKH)
    {
        yData_dla_Fw.emplace_back(linijka.Fw);
    }
    for (const dane_z_pliku &linijka : AKH)
    {
        yData_dla_XF.emplace_back(linijka.XF);
    }
    for (const dane_z_pliku &linijka : AKH)
    {
        yData_dla_KM.emplace_back(linijka.KM);
    }

    return true;
}

void Zanurzenie::oblicz_srednie()
{
    srednia_przod = (lewy_przod + prawy_przod) / 2;
    srednia_srodek = (lewy_srodek + prawy_srodek) / 2;
    srednia_tyl = (lewy_tyl + prawy_tyl) / 2;

    oblicz_srednie_srednich();
    oblicz_trym();
    oblicz_GM();
}


void Zanurzenie::oblicz_srednie_srednich()
{
    srednia_srednich = (srednia_przod + srednia_tyl + (6 * srednia_srodek)) / 8;
}

void Zanurzenie::oblicz_trym()
{
    trym = srednia_przod - srednia_tyl;
}

double Zanurzenie::oblicz_KG_po_operacji()
{
    if (Zanurzenie::KG_globalne_zapisane == false)
    {
        KG_globalne = KG;
        Zanurzenie::KG_globalne_zapisane = true;
    }
    else
    {
        KG_globalne = KG + ((obliczenia_uzytkownika::m * (obliczenia_uzytkownika::z - KG)) / D_globalne);
    }

    return KG_globalne;
}

void Zanurzenie::oblicz_GM()
{
    GM = KM - KG;
}

void Zanurzenie::oblicz_Xp(Zanurzenie &statek_przed_mielizna, Zanurzenie &statek_po_mieliznie)
{
    //double roznica_trymow = oblicz_roznice_trymow(*this, statek_przed_mielizna);
    double roznica_trymow = statek_po_mieliznie.trym - statek_przed_mielizna.trym;
    double roznica_wypornosci = statek_po_mieliznie.wypornosc - statek_przed_mielizna.wypornosc;
    Xp = ((roznica_trymow * statek_po_mieliznie.Mj) / roznica_wypornosci) + Xf_D_globalne;
}

void Zanurzenie::oblicz_Yp(Zanurzenie &statek_przed_mielizna)
{
    double GM_na_mieliznie = oblicz_GM_mielizna(statek_przed_mielizna, *this);
    double Tanges_FI = oblicz_Tanges_fi(*this);
    double roznica_wypornosci = oblicz_roznice_wypornosci(statek_przed_mielizna, *this);
    Yp = (this->wypornosc * GM_na_mieliznie * Tanges_FI) / roznica_wypornosci;
}


void Zanurzenie::oblicz_zanurzenie_nad_punktem_podparcia(Zanurzenie &statek_po_mieliznie)
{
    double Tanges_FI = oblicz_Tanges_fi(*this);
    Tp = srednia_tyl + trym * (statek_po_mieliznie.Xp / Lpp) + statek_po_mieliznie.Yp * Tanges_FI;
}


void Zanurzenie::przypisz_wartosci_z_pliku(bool statek_przed_mielizna)
{
    wypornosc = interpolate(xData_dla_T, yData_dla_D, srednia_srednich, true);
    wypornosc = wypornosc / 1.025;
    wypornosc = wypornosc * gestosc_wody;

    double D_tablicowe = (D_globalne / gestosc_wody) * 1.025;

    Xf_D_globalne = interpolate(xData_dla_D, yData_dla_XF, D_tablicowe, true);
    Fw_D_globalne = interpolate(xData_dla_D, yData_dla_Fw, D_tablicowe, true);
    KM_D_globalne = interpolate(xData_dla_D, yData_dla_KM, D_tablicowe, true);
    MJ_D_globalne = interpolate(xData_dla_D, yData_dla_MJ, D_tablicowe, true);

    Mj = interpolate(xData_dla_T, yData_dla_MJ, srednia_srednich, true);

    if (statek_przed_mielizna == true)
    {
        Fw = interpolate(xData_dla_T, yData_dla_Fw, srednia_srednich, true);
        Xf_przed_mielizna = interpolate(xData_dla_T, yData_dla_XF, srednia_srednich, true);
        KM = interpolate(xData_dla_T, yData_dla_KM, srednia_srednich, true);
    }
}







/* ------------------------------------- WOLNE FUNKCJE ------------------------------------- */


double oblicz_roznice_zanurzen(Zanurzenie &statek_przed_mielizna, Zanurzenie &statek_po_mieliznie)
{
    return statek_po_mieliznie.srednia_srednich - statek_przed_mielizna.srednia_srednich;
}

double oblicz_Tanges_fi(Zanurzenie &statek)
{
    return (statek.prawy_srodek - statek.lewy_srodek) / statek.B;
}

double oblicz_GM_mielizna(Zanurzenie &statek_przed_mielizna, Zanurzenie &statek_po_mieliznie)
{
    double GM_mielizna;
    double roznica_zanurzen = oblicz_roznice_zanurzen(statek_przed_mielizna, statek_po_mieliznie);
    double roznica_wypornosci = oblicz_roznice_wypornosci(statek_przed_mielizna, statek_po_mieliznie);

    GM_mielizna = statek_przed_mielizna.GM + (roznica_wypornosci / statek_po_mieliznie.wypornosc)
        * (statek_przed_mielizna.srednia_srednich + (roznica_zanurzen / 2) - statek_przed_mielizna.GM);

    statek_po_mieliznie.GM = GM_mielizna;

    return GM_mielizna;
}

double oblicz_roznice_trymow(Zanurzenie &statek_przed_mielizna, Zanurzenie &statek_po_mieliznie)
{
    return statek_po_mieliznie.trym - statek_przed_mielizna.trym;
}

double oblicz_roznice_wypornosci(Zanurzenie &statek_przed_mielizna,
    Zanurzenie &statek_po_mieliznie)
{
    if (Delta_D_raz_policzona == true)
    {
        Delta_D = statek_po_mieliznie.wypornosc - statek_przed_mielizna.wypornosc;
        Delta_D_raz_policzona = false;
    }

    if(Delta_D_po_dzialaniu_uzytkownika == true)
    {
        Delta_D = Delta_D - oblicz_zmiane_wypornosci_w_punkcie_podparcia(statek_przed_mielizna, statek_po_mieliznie);
    }

    return statek_po_mieliznie.wypornosc - statek_przed_mielizna.wypornosc;
}

double oblicz_zmiane_zanurzenia_w_punkcie_podparcia(Zanurzenie &statek_przed_mieliznia,
    Zanurzenie &statek_po_mieliznie)
{
    if (Delta_Tp_raz_policzona == true)
    {
        Delta_Tp = statek_po_mieliznie.Tp - statek_przed_mieliznia.Tp;
        Delta_Tp_raz_policzona = false;
    }

    suma_mas_uzytkownika += obliczenia_uzytkownika::m;
    D_globalne = statek_po_mieliznie.wypornosc + suma_mas_uzytkownika;
    statek_po_mieliznie.przypisz_wartosci_z_pliku(false);
    double Xf = pobierz_Xf_z_pliku_na_podstawie_D_globalne(statek_przed_mieliznia);
    double Mj = pobierz_Mj_z_pliku_na_podstawie_D_globalne(statek_po_mieliznie);
    statek_przed_mieliznia.oblicz_KG_po_operacji();
    double GM = oblicz_GM_na_podstawie_Km_i_KG_globalne();

    if (Delta_Tp_po_dzialaniu_uzytkownika == true)
    {
        double pierwszy_wynik = 1 / (statek_przed_mieliznia.Fw * statek_po_mieliznie.gestosc_wody * Zanurzenie::k);
        double drugi_wynik = ((obliczenia_uzytkownika::x - Xf) * (statek_po_mieliznie.Xp - Xf)) / (Mj * Zanurzenie::Lpp);
        double trzeci_wynik = (obliczenia_uzytkownika::y * statek_po_mieliznie.Yp) / (D_globalne * GM);

        double wynik =  obliczenia_uzytkownika::m * (pierwszy_wynik + drugi_wynik + trzeci_wynik);
        return wynik;
    }
    return -1;
}

double pobierz_Xf_z_pliku_na_podstawie_D_globalne(Zanurzenie &statek_przed_mieliznia)
{
    return Xf_D_globalne;
}

double pobierz_Fw_z_pliku_na_podstawie_D_globalne(Zanurzenie &statek_przed_mieliznia)
{
    return Fw_D_globalne;
}

double pobierz_Mj_z_pliku_na_podstawie_D_globalne(Zanurzenie &statek_po_mieliznie)
{
    MJ_D_globalne = (MJ_D_globalne / 1.025)  * statek_po_mieliznie.gestosc_wody;
    return MJ_D_globalne;
}

double oblicz_GM_na_podstawie_Km_i_KG_globalne()
{
    return KM_D_globalne - KG_globalne;
}

double oblicz_zmiane_wypornosci_w_punkcie_podparcia(Zanurzenie &statek_przed_mieliznia, Zanurzenie &statek_po_mieliznie)
{
    double Tp = oblicz_zmiane_zanurzenia_w_punkcie_podparcia(statek_przed_mieliznia, statek_po_mieliznie);
    double Xf = pobierz_Xf_z_pliku_na_podstawie_D_globalne(statek_przed_mieliznia);
    double Mj = pobierz_Mj_z_pliku_na_podstawie_D_globalne(statek_po_mieliznie);
    double GM = oblicz_GM_na_podstawie_Km_i_KG_globalne();

    double pierwszy_wynik = 1 / (statek_przed_mieliznia.Fw * statek_po_mieliznie.gestosc_wody * Zanurzenie::k);

    double licznik = pow((statek_po_mieliznie.Xp - Xf), 2);
    double drugi_wynik = licznik / (Mj * Zanurzenie::Lpp);

    licznik = pow((statek_po_mieliznie.Yp), 2);
    double trzeci_wynik = licznik / (D_globalne * GM);

    Delta_Tp = Delta_Tp - Tp;

    double wynik = Tp / (pierwszy_wynik + drugi_wynik + trzeci_wynik);
    return wynik;
}
