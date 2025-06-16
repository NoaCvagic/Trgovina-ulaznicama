#pragma once
#ifndef FUNKCIJE_H
#define FUNKCIJE_H

#define MAX 100

typedef enum {
    KONCERT,
    NOGOMET
} VrstaDogadjaja;

typedef enum {
    MENU_DODAJ = 1,
    MENU_PRIKAZI,
    MENU_AZURIRAJ,
    MENU_OBRISI,
    MENU_DODAJ_KOSARICA,
    MENU_UKLONI_KOSARICA,
    MENU_PRIKAZI_KOSARICA,
    MENU_PROMIJENI_KATEGORIJU,
    MENU_SEKVENCIJALNA_PRETRAGA,
    MENU_BINARNA_PRETRAGA,
    MENU_SORTIRAJ_ABECEDNO,
    MENU_SORTIRAJ_KOD,
    MENU_SORTIRAJ_QSRT,
    MENU_ZBROJ_DOSTUPNIH,
    MENU_OBRISI_BAZU,
    MENU_PREIMENUJ_BAZU,
    MENU_IZLAZ = 0
} MenuOpcije;

typedef struct {
    int kodUlaznice;
    char* naziv;
    float cijena;
    int dostupno;
} Ulaznica;
typedef struct {
    Ulaznica* artikli[MAX];
    int brojArtikala;
} Kosarica;

extern VrstaDogadjaja aktivnaVrsta;

static Ulaznica* koncertBaza[MAX];
static int brojKoncertUlaznica = 0;
extern Kosarica* koncertKosarica;

static Ulaznica* nogometBaza[MAX];
static int brojNogometUlaznica = 0;
extern Kosarica* nogometKosarica;

Ulaznica* kreirajUlaznicu();
void dodajUlaznicu();
void prikaziSveUlaznice();
void azurirajUlaznicu();
void obrisiUlaznicu();
Ulaznica* pronadiUlaznicuPoKodu(int kodUlaznice);
void oslobodiMemoriju();
void spremiUBazu();
void ucitajIzBaze();
void pretraziUlazniceSekvencijalno();
void pretraziUlazniceBinarno();
void sortiranjePoKodu();
void prikaziZbrojDostupnih();
void obrisiBazu();
void preimenujBazu();


#endif
