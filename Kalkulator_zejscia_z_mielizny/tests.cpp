#include "statek.h"
#include <cassert>
#include <iostream>


void wykonaj_testy()
{
    /* DANE KONFIGURACYJNE */
    Zanurzenie statek_przed_mielizna;
    Zanurzenie statek_po_mieliznie;

    statek_przed_mielizna.lewy_przod = 8;
    statek_przed_mielizna.prawy_przod = 8;
    statek_przed_mielizna.lewy_srodek = 8.5;
    statek_przed_mielizna.prawy_srodek = 8.5;
    statek_przed_mielizna.lewy_tyl = 9;
    statek_przed_mielizna.prawy_tyl = 9;

    statek_po_mieliznie.lewy_przod = 8;
    statek_po_mieliznie.prawy_przod = 8;
    statek_po_mieliznie.lewy_srodek = 8;
    statek_po_mieliznie.prawy_srodek = 10;
    statek_po_mieliznie.lewy_tyl = 10;
    statek_po_mieliznie.prawy_tyl = 10;

    statek_przed_mielizna.wypornosc = 3000;
    statek_po_mieliznie.wypornosc = 2000;

    statek_przed_mielizna.GM = 0;
    statek_przed_mielizna.Mj = 1000;

    statek_po_mieliznie.Xf_przed_mielizna = 10;

    statek_po_mieliznie.Fw = 1;
    statek_przed_mielizna.Fw = 1;
    //statek_po_mieliznie.gestosc_wody = 1;

    /* -------------------------------------- */

    /* Testujemy:
    oblicz_srednie()
    oblicz_trym()
    oblicz_roznice_trymow()
    oblicz_srednie_srednich()*/

    statek_przed_mielizna.oblicz_srednie();
    assert(statek_przed_mielizna.srednia_przod == 8);
    assert(statek_przed_mielizna.srednia_srodek == 8.5);
    assert(statek_przed_mielizna.srednia_tyl == 9);

    statek_po_mieliznie.oblicz_srednie();
    assert(statek_po_mieliznie.srednia_przod == 8);
    assert(statek_po_mieliznie.srednia_srodek == 9);
    assert(statek_po_mieliznie.srednia_tyl == 10);


//    statek_przed_mielizna.oblicz_trym();
//    assert(statek_przed_mielizna.trym == 1);

//    statek_po_mieliznie.oblicz_trym();
//    assert(statek_po_mieliznie.trym == 2);

//    double roznica_trymow = oblicz_roznice_trymow(statek_przed_mielizna, statek_po_mieliznie);
//    assert(roznica_trymow == 1);

//    statek_przed_mielizna.oblicz_srednie_srednich();
//    assert(statek_przed_mielizna.srednia_srednich == 8.5);

//    statek_po_mieliznie.oblicz_srednie_srednich();
//    assert(statek_po_mieliznie.srednia_srednich == 9);

//    double roznica_wypornosci = oblicz_roznice_wypornosci(statek_przed_mielizna, statek_po_mieliznie);
//    assert(roznica_wypornosci == -1000);

//    double roznica_zanurzen = oblicz_roznice_zanurzen(statek_przed_mielizna, statek_po_mieliznie);
//    assert(roznica_zanurzen == 0.5);

//    double Tanges_FI = oblicz_Tanges_fi(statek_po_mieliznie);
//    assert(Tanges_FI == 0.081967213114754106);

//    double GM_mielizna = oblicz_GM_mielizna(statek_przed_mielizna, statek_po_mieliznie);
//    assert(GM_mielizna == -4.375);

//    statek_po_mieliznie.oblicz_Xp(statek_przed_mielizna);
//    assert(statek_po_mieliznie.Xp == -2.0000000000000000);

//    statek_po_mieliznie.oblicz_Yp(statek_przed_mielizna);
//    assert(statek_po_mieliznie.Yp == 0.71721311475409844);


//    statek_po_mieliznie.oblicz_zanurzenie_nad_punktem_podparcia(statek_po_mieliznie);
//    assert(statek_po_mieliznie.Tp == 10.037166338604123);

//    statek_przed_mielizna.oblicz_zanurzenie_nad_punktem_podparcia(statek_po_mieliznie);
//    assert(statek_przed_mielizna.Tp == 8.9891891891891884);

//    oblicz_zmiane_zanurzenia_w_punkcie_podparcia(statek_przed_mielizna, statek_po_mieliznie);
//    assert(Delta_Tp == 100.48559984673913);

//    double n = oblicz_zmiane_wypornosci_w_punkcie_podparcia(statek_przed_mielizna, statek_po_mieliznie);
//    assert(n == 200.76254472618487);
}
