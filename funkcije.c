#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funkcije.h"

#define SIGURNO_FREE(ptr) do { if (ptr) { free(ptr); (ptr) = NULL; } } while(0)

Kosarica* koncertKosarica = NULL;
Kosarica* nogometKosarica = NULL;
int aktivnaVrsta = 0;

Ulaznica* kreirajUlaznicu() {
    Ulaznica* nova = (Ulaznica*)malloc(sizeof(Ulaznica));
    if (!nova) return NULL;

    nova->kodUlaznice = (aktivnaVrsta == 0) ? brojKoncertUlaznica + 1 : brojNogometUlaznica + 1;

    char buffer[100];
    printf("Unesi naziv dogadjaja: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("Greska pri unosu naziva dogadjaja.\n");
        free(nova);
        return NULL;
    }

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    nova->naziv = (char*)malloc(strlen(buffer) + 1);
    if (!nova->naziv) {
        printf("Greska pri alokaciji memorije za naziv.\n");
        free(nova);
        return NULL;
    }
    strcpy(nova->naziv, buffer);

    printf("Unesi cijenu: ");
    if (scanf("%f", &nova->cijena) != 1) {
        printf("Greska pri unosu cijene.\n");
        free(nova->naziv);
        free(nova);
        return NULL;
    }

    printf("Unesi broj dostupnih ulaznica: ");
    if (scanf("%d", &nova->dostupno) != 1) {
        printf("Greska pri unosu broja ulaznica.\n");
        free(nova->naziv);
        free(nova);
        return NULL;
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    return nova;
}

void dodajUlaznicu() {
    Ulaznica* nova = kreirajUlaznicu();
    if (!nova) return;

    if (aktivnaVrsta == 0)
        koncertBaza[brojKoncertUlaznica++] = nova;
    else
        nogometBaza[brojNogometUlaznica++] = nova;

    printf("Ulaznica dodana!\n");
}

void prikaziJednuUlaznicu(Ulaznica* u) {
    if (u == NULL) {
        printf("(prazno)\n");
        return;
    }
    printf("Kod ulaznice: %d // Naziv: %s // Cijena: %.2f // Dostupno: %d\n",
        u->kodUlaznice, u->naziv, u->cijena, u->dostupno);
}

void prikaziSveUlaznice() {
    Ulaznica** baza = (aktivnaVrsta == 0) ? koncertBaza : nogometBaza;
    int broj = (aktivnaVrsta == 0) ? brojKoncertUlaznica : brojNogometUlaznica;

    printf("Dostupne ulaznice\n");
    for (int i = 0; i < broj; i++)
        prikaziJednuUlaznicu(baza[i]);
}

void azurirajUlaznicu() {
    int kodUlaznice;
    printf("Unesi kod ulaznice za azuriranje: ");
    if (scanf("%d", &kodUlaznice) != 1) {
        printf("Neispravan unos koda ulaznice.\n");
      
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }

    Ulaznica* u = pronadiUlaznicuPoKodu(kodUlaznice);
    if (u) {
        printf("Nova cijena: ");
        if (scanf("%f", &u->cijena) != 1) {
            printf("Neispravan unos cijene.\n");
            while ((getchar()) != '\n' && !feof(stdin));
            return;
        }

        printf("Novi broj dostupnih ulaznica: ");
        if (scanf("%d", &u->dostupno) != 1) {
            printf("Neispravan unos broja dostupnih ulaznica.\n");
            while ((getchar()) != '\n' && !feof(stdin));
            return;
        }

        printf("Ulaznica je azurirana.\n");
    }
    else {
        printf("Ulaznica nije pronadena.\n");
    }

}

void obrisiUlaznicu() {
    int kodUlaznice;
    printf("Unesi kod ulaznice za brisanje: ");
    if (scanf("%d", &kodUlaznice) != 1) {
        printf("Neispravan unos koda ulaznice.\n");
    }

    Ulaznica** baza = (aktivnaVrsta == 0) ? koncertBaza : nogometBaza;
    int* broj = (aktivnaVrsta == 0) ? &brojKoncertUlaznica : &brojNogometUlaznica;

    for (int i = 0; i < *broj; i++) {
        if (baza[i]->kodUlaznice == kodUlaznice) {
            free(baza[i]->naziv);
            free(baza[i]);
            for (int j = i; j < *broj - 1; j++)
                baza[j] = baza[j + 1];
            (*broj)--;
            printf("Ulaznica obrisana.\n");
            return;
        }
    }
    printf("Ulaznica nije pronadena.\n");
}

Ulaznica* pronadiUlaznicuPoKodu(int kodUlaznice) {
    Ulaznica** baza = (aktivnaVrsta == 0) ? koncertBaza : nogometBaza;
    int broj = (aktivnaVrsta == 0) ? brojKoncertUlaznica : brojNogometUlaznica;

    for (int i = 0; i < broj; i++) {
        if (baza[i]->kodUlaznice == kodUlaznice) return baza[i];
    }
    return NULL;
}


void oslobodiMemoriju() {
   
    for (int i = 0; i < brojKoncertUlaznica; i++) {
        SIGURNO_FREE(koncertBaza[i]->naziv);
        SIGURNO_FREE(koncertBaza[i]);
    }

    for (int i = 0; i < brojNogometUlaznica; i++) {
        SIGURNO_FREE(nogometBaza[i]->naziv);
        SIGURNO_FREE(nogometBaza[i]);
    }

    SIGURNO_FREE(koncertKosarica);
    SIGURNO_FREE(nogometKosarica);
}


void ucitajIzBaze() {
    FILE* f = fopen("ulaznice.txt", "r");
    if (!f) {
        
        f = fopen("ulaznice.txt", "w");
        if (!f) {
            perror("Greska pri kreiranju datoteke.");
            return;
        }
        fprintf(f, "0\n0\n");  
        fclose(f);
        
        f = fopen("ulaznice.txt", "r");
        if (!f) {
            perror("Greska pri otvaranju datoteke za citanje.");
            return;
        }
    }

    fseek(f, 0, SEEK_END);
    long velicina = ftell(f);

    if (velicina == 0) {
        printf("Datoteka je prazna.\n");
        fclose(f);
        return;
    }

    rewind(f);

    if (fscanf(f, "%d\n", &brojKoncertUlaznica) != 1) {
        printf("Greska pri citanju broja koncert ulaznica.\n");
        fclose(f);
        return;
    }

    for (int i = 0; i < brojKoncertUlaznica; i++) {
        Ulaznica* u = (Ulaznica*)malloc(sizeof(Ulaznica));
        if (!u) continue;
        char buffer[101];
        if (fscanf(f, "%d//%100[^|]|%f|%d\n", &u->kodUlaznice, buffer, &u->cijena, &u->dostupno) != 4) {
            free(u);
            continue;
        }
        buffer[100] = '\0';


        u->naziv = (char*)malloc(strlen(buffer) + 1);
        strcpy(u->naziv, buffer);
        koncertBaza[i] = u;
    }

    if (fscanf(f, "%d\n", &brojNogometUlaznica) != 1) {
        printf("Greska pri citanju broja nogometnih ulaznica.\n");
        fclose(f);
        return;
    }

    for (int i = 0; i < brojNogometUlaznica; i++) {
        Ulaznica* u = (Ulaznica*)malloc(sizeof(Ulaznica));
        if (!u) continue;
        char buffer[100] = { 0 };  

        if (fscanf(f, "%d//%99[^|]|%f|%d\n", &u->kodUlaznice, buffer, &u->cijena, &u->dostupno) != 4) {
            free(u);
            continue;
        }
        buffer[99] = '\0'; 

        u->naziv = malloc(strlen(buffer) + 1);
        if (!u->naziv) {
            free(u);
            continue;
        }
        strcpy(u->naziv, buffer);
        nogometBaza[i] = u;
    }

    fclose(f);
}

extern int brojacKoraka = 0;

int linearnoPretrazivanje(Ulaznica** baza, int broj, const char* naziv) {
    brojacKoraka = 0;
    for (int i = 0; i < broj; i++) {
        brojacKoraka++;
        if (strcmp(baza[i]->naziv, naziv) == 0)
            return i;
    }
    return -1;
}

void pretraziUlazniceSekvencijalno() {
    char pojam[100];
    printf("Unesi naziv za sekvencijalnu (linearnu) pretragu: ");
    if (scanf(" %99s", pojam) != 1) {
        printf("Neispravan unos naziva.\n");
    }

    Ulaznica** baza = (aktivnaVrsta == 0) ? koncertBaza : nogometBaza;
    int broj = (aktivnaVrsta == 0) ? brojKoncertUlaznica : brojNogometUlaznica;

    int indeks = linearnoPretrazivanje(baza, broj, pojam);
    if (indeks != -1) {
        printf("Ulaznica je pronadjena nakon %d koraka na indeksu %d.\n", brojacKoraka, indeks);
        prikaziJednuUlaznicu(baza[indeks]);
    }
    else {
        printf("Ulaznica nije pronadjena.\n");
    }
}

int binarnoPretrazivanje(Ulaznica** baza, int broj, const char* naziv) {
    int dg = 0, gg = broj - 1;
    int sredina;
    brojacKoraka = 0;

    while (dg <= gg) {
        sredina = (dg + gg) / 2;
        brojacKoraka++;
        int usp = strcmp(baza[sredina]->naziv, naziv);
        if (usp == 0)
            return sredina;
        else if (usp > 0)
            gg = sredina - 1;
        else
            dg = sredina + 1;
    }
    return -1;
}

void pretraziUlazniceBinarno() {
    char pojam[100];
    printf("Unesi naziv za binarnu pretragu: ");
    if (scanf(" %99s", pojam) != 1) {
        printf("Neispravan unos naziva.\n");
    }

    Ulaznica** baza = (aktivnaVrsta == 0) ? koncertBaza : nogometBaza;
    int broj = (aktivnaVrsta == 0) ? brojKoncertUlaznica : brojNogometUlaznica;

    int indeks = binarnoPretrazivanje(baza, broj, pojam);
    if (indeks != -1) {
        printf("Ulaznica je pronadjena nakon %d koraka na indeksu %d.\n", brojacKoraka, indeks);
        prikaziJednuUlaznicu(baza[indeks]);
    }
    else {
        printf("Ulaznica nije pronadjena.\n");
    }
}

void zamjenaUlaznica(Ulaznica** a, Ulaznica** b) {
    Ulaznica* zamjena = *a;
    *a = *b;
    *b = zamjena;
}

void selectionSortUlaznice() {
    Ulaznica** baza = (aktivnaVrsta == 0) ? koncertBaza : nogometBaza;
    int broj = (aktivnaVrsta == 0) ? brojKoncertUlaznica : brojNogometUlaznica;

    for (int i = 0; i < broj - 1; i++) {
        int min = i;
        for (int j = i + 1; j < broj; j++) {
            if (strcmp(baza[j]->naziv, baza[min]->naziv) < 0) {
                min = j;
            }
        }
        if (min != i)
            zamjenaUlaznica(&baza[i], &baza[min]);
    }
    printf("Ulaznice sortirane biranjem (selection sort).\n");
}
void sortiranjePoKodu() {
    Ulaznica** baza = (aktivnaVrsta == 0) ? koncertBaza : nogometBaza;
    int broj = (aktivnaVrsta == 0) ? brojKoncertUlaznica : brojNogometUlaznica;

    for (int i = 0; i < broj - 1; i++) {
        int min = i;
        for (int j = i + 1; j < broj; j++) {
            if (baza[j]->kodUlaznice < baza[min]->kodUlaznice) {
                min = j;
            }
        }
        if (min != i)
            zamjenaUlaznica(&baza[i], &baza[min]);
    }
    printf("Ulaznice sortirane po kodu ulaznice.\n");
}

int usporediUlaznicePoNazivu(const void* a, const void* b) {
    Ulaznica* u1 = *(Ulaznica**)a;
    Ulaznica* u2 = *(Ulaznica**)b;
    return strcmp(u1->naziv, u2->naziv);
}

int rekurzivniZbroj(Ulaznica** baza, int n) {
    if (n == 0) return 0;
    return baza[n - 1]->dostupno + rekurzivniZbroj(baza, n - 1);
}

void prikaziZbrojDostupnih() {
    Ulaznica** baza = (aktivnaVrsta == 0) ? koncertBaza : nogometBaza;
    int broj = (aktivnaVrsta == 0) ? brojKoncertUlaznica : brojNogometUlaznica;
    int zbroj = rekurzivniZbroj(baza, broj);
    printf("Ukupan broj dostupnih ulaznica: %d\n", zbroj);
}


void obrisiBazu() {
    if (remove("ulaznice.txt") == 0) {
        printf("Datoteka uspjesno obrisana.\n");
    }
    else {
        perror("Ne moze se obrisati datoteka.");
    }
}


void preimenujBazu() {
    if (rename("ulaznice.txt", "backup_ulaznice.txt") == 0) {
        printf("Datoteka uspjesno preimenovana.\n");
    }
    else {
        perror("Greska pri preimenovanju datoteke.");
    }
}

void spremiUBazu() {
    FILE* f = fopen("ulaznice.txt", "w");
    if (!f) {
        perror("Greska pri otvaranju datoteke za pisanje.");
        return;
    }

    fprintf(f, "Broj koncert ulaznica: %d\n", brojKoncertUlaznica);
    for (int i = 0; i < brojKoncertUlaznica; i++) {
        fprintf(f, "Kod ulaznice: %d//Ime dogadjaja: %s//Cijena: %.2f//Dostupno: %d\n", koncertBaza[i]->kodUlaznice, koncertBaza[i]->naziv, koncertBaza[i]->cijena, koncertBaza[i]->dostupno);
    }

    fprintf(f, "Broj nogometnih ulaznica: %d\n", brojNogometUlaznica);
    for (int i = 0; i < brojNogometUlaznica; i++) {
        fprintf(f, "Kod ulaznice: %d//Ime dogadjaja: %s//Cijena: %.2f//Dostupno: %d\n", nogometBaza[i]->kodUlaznice, nogometBaza[i]->naziv, nogometBaza[i]->cijena, nogometBaza[i]->dostupno);
    }

    fclose(f);
}

