#ifndef STATEK_H
#define STATEK_H

#include <vector>

const int max_range_GUI = 20;

extern bool Delta_Tp_raz_policzona;
extern bool Delta_Tp_po_dzialaniu_uzytkownika;

extern bool Delta_D_raz_policzona;
extern bool Delta_D_po_dzialaniu_uzytkownika;

extern double D_globalne;

namespace obliczenia_uzytkownika
{

extern double m;
extern double x;
extern double y;
extern double z;
}


struct dane_z_pliku
{
    double T;
    double D;
    double XF;
    double KM;
    double MJ;
    double Fw;
};

extern std::vector<dane_z_pliku> AKH;
extern double Delta_Tp;
extern double Delta_D;

class Zanurzenie
{
    void oblicz_srednie_srednich();
    void oblicz_trym();
    void oblicz_GM();

public:
    /* DANE OD UZYTKOWNIKA */
    static double B; // szerokosc statku
    static double Lpp; // dlugosc miedzy pionami
    static double k;
    double KG = 0;
    double lewy_przod = 0, prawy_przod = 0;
    double lewy_srodek = 0, prawy_srodek = 0;
    double lewy_tyl = 0, prawy_tyl = 0;
    double gestosc_wody = 1.025;

    /* DANE Z PLIKU */
    double wypornosc = 0;
    double Mj = 0;
    double Xf_przed_mielizna = 0;
    //double Xf_D_globalne = 0; // po przyjeciu masy
    double Fw = 0;
    double KM = 0;
    void przypisz_wartosci_z_pliku(bool statek_przed_mielizna);

    /* My liczymy */
    double trym = 0;
    double GM = 0; // poprzeczna wysokosc metacentryczna
    double srednia_przod = 0, srednia_srodek = 0, srednia_tyl = 0;
    double srednia_srednich = 0;

    void oblicz_srednie();
    double oblicz_KG_po_operacji();

    static bool KG_globalne_zapisane;


    double Xp, Yp;

    void oblicz_Xp(Zanurzenie &statek_przed_mielizna, Zanurzenie &statek_po_mieliznie);
    void oblicz_Yp(Zanurzenie &statek_przed_mielizna);

    void oblicz_zanurzenie_nad_punktem_podparcia(Zanurzenie &statek_po_mieliznie);
    double Tp;
};

bool wczytaj_dane();

double oblicz_roznice_trymow(Zanurzenie &statek_przed_mielizna,
    Zanurzenie &statek_po_mieliznie);
double oblicz_roznice_wypornosci(Zanurzenie &statek_przed_mielizna,
    Zanurzenie &statek_po_mieliznie);
double pobierz_Xf_z_pliku_na_podstawie_D_globalne(Zanurzenie &statek_przed_mieliznia);
double pobierz_Fw_z_pliku_na_podstawie_D_globalne(Zanurzenie &statek_przed_mieliznia);
double oblicz_roznice_zanurzen(Zanurzenie &statek_przed_mielizna, Zanurzenie &statek_po_mieliznie);
double oblicz_Tanges_fi(Zanurzenie &statek);
double oblicz_GM_mielizna(Zanurzenie &statek_przed_mielizna, Zanurzenie &statek_po_mieliznie);
double oblicz_zmiane_zanurzenia_w_punkcie_podparcia(Zanurzenie &statek_przed_mieliznia,
    Zanurzenie &statek_po_mieliznie);
double pobierz_Mj_z_pliku_na_podstawie_D_globalne(Zanurzenie &statek_po_mieliznie);
double oblicz_GM_na_podstawie_Km_i_KG_globalne();
double oblicz_zmiane_wypornosci_w_punkcie_podparcia(Zanurzenie &statek_przed_mieliznia,
    Zanurzenie &statek_po_mieliznie);


#endif // STATEK_H
