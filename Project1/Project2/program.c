#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE (20)
#define FILE_DIDNT_OPEN_ERROR (-1)
#define KRIVI_BROJ_BODOVA (-1)

typedef struct student {
    char ime[MAX_LINE];
    char prezime[MAX_LINE];
    int bodovi;
}student;

int brojStudenata(char* imedatoteke);
void unosStudenata(int, student*, char*);
int maxBodovi(int n, student* nizStudenata);
void ispisStudenata(int, student*, char*, int);

int main() {
    student* nizStudenata;
    char imedatoteke[MAX_LINE];
    int n = 0; //Broj studenata
    int maxBrBodova = 0;
    printf("Unesite ime datoteke: ");
    scanf(" %s", imedatoteke);
    n = brojStudenata(imedatoteke);
    nizStudenata = (student*)malloc(n * sizeof(student));
    if (nizStudenata == NULL) {
        printf("Memorija nije dinamicki alocirana!\n");
    }
    else {
        printf("Memorija alocirana!\n");
    }
    unosStudenata(n, nizStudenata, imedatoteke);
    maxBrBodova = maxBodovi(n, nizStudenata);
    if (maxBrBodova == KRIVI_BROJ_BODOVA) {
        printf("Problem pri trazenju najveceg broja bodova\n");
    }
    else {
        printf("Najveci broj bodova je: %d\n", maxBrBodova);
    }
    ispisStudenata(n, nizStudenata, imedatoteke, maxBrBodova);
    return 0;
}

int brojStudenata(char* imedatoteke) {
    FILE* fp = NULL;
    int brojac = 0;
    char redak[MAX_LINE] = { 0 };
    fp = fopen(imedatoteke, "r");
    if (fp == NULL) {
        printf("Datoteka se nije otvorila.");
        return FILE_DIDNT_OPEN_ERROR;
    }
    while (!feof(fp)) {
        fgets(redak, MAX_LINE, fp);
        if (strcmp("\n", redak) != 0) {
            brojac++;
        }
    }
    fclose(fp);
    return brojac;
}

void unosStudenata(int n, student* nizStudenata, char* imedatoteke) {
    FILE* fp = NULL;
    fp = fopen(imedatoteke, "r");
    int i = 0;
    for (i = 0; i < n; i++) {
        fscanf(fp, " %s %s %d", nizStudenata[i].ime, nizStudenata[i].prezime, &nizStudenata[i].bodovi);
    }
    fclose(fp);
}

int maxBodovi(int n, student* nizStudenata) {
    int maxBodova = KRIVI_BROJ_BODOVA;
    int i = 0;
    for (i = 0; i < n; i++) {
        if (nizStudenata[i].bodovi > maxBodova) {
            maxBodova = nizStudenata[i].bodovi;
        }
    }
    return maxBodova;
}

void ispisStudenata(int n, student* nizStudenata, char* imedatoteke, int maxBrBodova) {
    int i = 0;
    double relativanBrBodova;
    printf("IME \t PREZIME \t APSOLUTNI BROJ BODOVA \t RELATIVAN BROJ BODOVA\n");
    for (i = 0; i < n; i++) {
        relativanBrBodova = (double)nizStudenata[i].bodovi / maxBrBodova * 100;
        printf("%s\t %s\t %10d\t %26lf\n", nizStudenata[i].ime, nizStudenata[i].prezime, nizStudenata[i].bodovi, relativanBrBodova);
    }
}