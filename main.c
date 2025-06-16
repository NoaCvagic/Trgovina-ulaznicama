#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "funkcije.h"
#include "izbornik.h"


int main() {
    koncertKosarica = (Kosarica*)malloc(sizeof(Kosarica));
    if (!koncertKosarica) {
        printf("Greska pri alokaciji koncert kosarice.\n");
        return EXIT_FAILURE;
    }
    koncertKosarica->brojArtikala = 0;

    nogometKosarica = (Kosarica*)malloc(sizeof(Kosarica));
    if (!nogometKosarica) {
        printf("Greska pri alokaciji nogomet kosarice.\n");
        free(koncertKosarica);
        return EXIT_FAILURE;
    }
    nogometKosarica->brojArtikala = 0;

    ucitajIzBaze();

    int izbor;
    do {
        printf("Odaberite kategoriju:\n1. Koncert\n2. Nogomet\nOdabir: ");
        if (scanf("%d", &izbor) != 1) {
            printf("Neispravan unos. Treba unijeti broj 1 ili 2.\n");

            while (getchar() != '\n');
            izbor = 0;
        }
    } while (izbor != 1 && izbor != 2);

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    aktivnaVrsta = (izbor == 1) ? KONCERT : NOGOMET;

    izbornik();
    oslobodiMemoriju();
    return EXIT_SUCCESS;
}
