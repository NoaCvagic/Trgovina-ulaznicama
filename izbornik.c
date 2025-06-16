#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "izbornik.h"
#include "funkcije.h"

void izbornik() {
    int izbor;
    do {
        printf("\n%s\n", aktivnaVrsta == KONCERT ? "KONCERT" : "NOGOMET");
        printf("%d. Dodaj ulaznicu\n", MENU_DODAJ);
        printf("%d. Prikazi sve ulaznice\n", MENU_PRIKAZI);
        printf("%d. Azuriraj ulaznicu\n", MENU_AZURIRAJ);
        printf("%d. Obrisi ulaznicu\n", MENU_OBRISI);
        printf("%d. Dodaj u kosaricu\n", MENU_DODAJ_KOSARICA);
        printf("%d. Ukloni iz kosarice\n", MENU_UKLONI_KOSARICA);
        printf("%d. Prikazi kosaricu\n", MENU_PRIKAZI_KOSARICA);
        printf("%d. Promijeni kategoriju\n", MENU_PROMIJENI_KATEGORIJU);
        printf("%d. Sekvencijalna pretraga\n", MENU_SEKVENCIJALNA_PRETRAGA);
        printf("%d. Binarna pretraga\n", MENU_BINARNA_PRETRAGA);
        printf("%d. Sortiraj ulaznice abecedno\n", MENU_SORTIRAJ_ABECEDNO);
        printf("%d. Sortiraj ulaznice po kodu ulaznice\n", MENU_SORTIRAJ_KOD);
        printf("%d. Prikazi zbroj dostupnih ulaznica\n", MENU_ZBROJ_DOSTUPNIH);
        printf("%d. Obrisi bazu\n", MENU_OBRISI_BAZU);
        printf("%d. Preimenuj bazu\n", MENU_PREIMENUJ_BAZU);
        printf("%d. Izlaz\nOdabir: ", MENU_IZLAZ);
        while (scanf("%d", &izbor) != 1) {
            printf("Neispravan unos. Pokusajte ponovo: ");
            while (getchar() != '\n');
        }
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (izbor) {
        case MENU_DODAJ: dodajUlaznicu(); break;
        case MENU_PRIKAZI: prikaziSveUlaznice(); break;
        case MENU_AZURIRAJ: azurirajUlaznicu(); break;
        case MENU_OBRISI: obrisiUlaznicu(); break;
        case MENU_DODAJ_KOSARICA: dodajUKosaricu(); break;
        case MENU_UKLONI_KOSARICA: ukloniIzKosarice(); break;
        case MENU_PRIKAZI_KOSARICA: prikaziKosaricu(); break;
        case MENU_PROMIJENI_KATEGORIJU:
            aktivnaVrsta = (aktivnaVrsta == KONCERT) ? NOGOMET : KONCERT;
            break;
        case MENU_SEKVENCIJALNA_PRETRAGA: pretraziUlazniceSekvencijalno(); break;
        case MENU_BINARNA_PRETRAGA: pretraziUlazniceBinarno(); break;
        case MENU_SORTIRAJ_ABECEDNO: selectionSortUlaznice(); break;
        case MENU_SORTIRAJ_KOD: sortiranjePoKodu(); break;
        case MENU_ZBROJ_DOSTUPNIH: prikaziZbrojDostupnih(); break;
        case MENU_OBRISI_BAZU: obrisiBazu(); break;
        case MENU_PREIMENUJ_BAZU: preimenujBazu(); break;
        case MENU_IZLAZ:
            spremiUBazu();
            printf("Izlaz.\n");
            break;
        default: printf("Nepoznata opcija.\n");
        }
    } while (izbor != MENU_IZLAZ);
}
