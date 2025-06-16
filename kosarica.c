#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kosarica.h"
#include "funkcije.h"

void dodajUKosaricu() {
    
    printf("Broj koncert ulaznica: %d\n", brojKoncertUlaznica);
    printf("Broj nogomet ulaznica: %d\n", brojNogometUlaznica);
    printf("Aktivna vrsta: %d\n", aktivnaVrsta);

    prikaziSveUlaznice();

    int kodUlaznice;
    printf("\nUnesite kod ulaznice za dodavanje u kosaricu: ");
    while (scanf("%d", &kodUlaznice) != 1) {
        printf("Neispravan unos, treba unijeti broj.\n");
        while (getchar() != '\n'); 
        printf("Pokusajte ponovno: ");
    }

    Ulaznica* u = pronadiUlaznicuPoKodu(kodUlaznice);
    if (u == NULL) {
        printf("Ulaznica s kodom %d nije pronadena.\n", kodUlaznice);
        return;
    }

    Kosarica* k = (aktivnaVrsta == KONCERT) ? koncertKosarica : nogometKosarica;

    if (k == NULL) {
        printf("Kosarica nije inicijalizirana!\n");
        return;
    }

    if (u->dostupno <= 0) {
        printf("Nema dostupnih ulaznica ovog tipa.\n");
        return;
    }

    if (k->brojArtikala >= MAX) {
        printf("Kosarica je puna!\n");
        return;
    }

    for (int i = 0; i < k->brojArtikala; i++) {
        if (k->artikli[i]->kodUlaznice == kodUlaznice) {
            printf("Ova ulaznica je vec u kosarici.\n");
            return;
        }
    }

    k->artikli[k->brojArtikala] = u;
    k->brojArtikala++;
    u->dostupno--;
    printf("Ulaznica %s je dodana u kosaricu.\n", u->naziv);
}

void ukloniIzKosarice() {
    Kosarica* k = (aktivnaVrsta == KONCERT) ? koncertKosarica : nogometKosarica;

    if (k->brojArtikala == 0) {
        printf("Kosarica je prazna.\n");
        return;
    }

    prikaziKosaricu();
    int kodUlaznice;
    printf("\nUnesite kod ulaznice za uklanjanje iz kosarice: ");
    while (scanf("%d", &kodUlaznice) != 1) {
        printf("Neispravan unos, treba unijeti broj.\n");
        while (getchar() != '\n'); 
        printf("Pokusajte ponovno: ");
    }

    for (int i = 0; i < k->brojArtikala; i++) {
        if (k->artikli[i]->kodUlaznice == kodUlaznice) {
            k->artikli[i]->dostupno++;

            for (int j = i; j < k->brojArtikala - 1; j++) {
                k->artikli[j] = k->artikli[j + 1];
            }

            k->brojArtikala--;
            printf("Ulaznica je uklonjena iz kosarice.\n");
            return;
        }
    }

    printf("Ulaznica s kodom %d nije pronadena u kosarici.\n", kodUlaznice);
}

void prikaziKosaricu() {

    Kosarica* k = (aktivnaVrsta == KONCERT) ? koncertKosarica : nogometKosarica;

   
    if (k == NULL) {
        printf("\nGRESKA: Kosarica nije inicijalizirana!\n");
        return;
    }

    printf("\Kosarica\n");
    printf("Kategorija: %s\n", aktivnaVrsta == KONCERT ? "KONCERT" : "NOGOMET");

    if (k->brojArtikala == 0) {
        printf("Kosarica je prazna.\n");
    }
    else {
        float ukupnaCijena = 0.0f;

        for (int i = 0; i < k->brojArtikala; i++) {

            if (k->artikli[i] != NULL) {
                printf("%2d. ", i + 1);
                prikaziJednuUlaznicu(k->artikli[i]);
                ukupnaCijena += k->artikli[i]->cijena;
            }
        }

        printf("\nUKUPNO: %d ulaznica, %.2f EUR\n", k->brojArtikala, ukupnaCijena);
    }

}
