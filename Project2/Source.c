#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAKSIMALAN_BROJ_LINIJA (128)
#define ZAVRSEN_KOD (0)
#define NEUSPJELA_DINAMICKA_ALOKACIJA (-1)

typedef struct Osoba* Pozicija;

typedef struct Osoba {
	char ime[MAKSIMALAN_BROJ_LINIJA];
	char prezime[MAKSIMALAN_BROJ_LINIJA];
	int godiste;
	Pozicija Next; // Pozicija pokazuje na sljedeci cvor u nizu
}Osoba;

void UnosNaPocetak(Osoba, Pozicija);
void Ispis(Pozicija);
void UnosNaKraj(Osoba, Pozicija);
void TraziPoPrez(Osoba, Pozicija);
void Brisi(Osoba, Pozicija);
Pozicija TraziPrethodnika(Osoba, Pozicija);

int main() {
	Osoba o;
	Osoba Head;
	Head.Next = NULL;
	int n = 0; // Brojac osoba
	int i = 0, godiste = 0;
	char ime[MAKSIMALAN_BROJ_LINIJA] = { 0 };
	char prezime[MAKSIMALAN_BROJ_LINIJA] = { 0 };
	printf("Koliko osoba zelite unijeti: ");
	scanf_s(" %d", &n);
	for (i = 0; i < n; i++) {
		printf("Unesite ime osobe: ");
		scanf(" %s", o.ime);
		printf("Unesite prezime osobe: ");
		scanf(" %s", o.prezime);
		printf("Unesite godiste osobe: ");
		scanf(" %d", &o.godiste);
		UnosNaPocetak(o, &Head);
	}
	Ispis(Head.Next);
	printf("Unesite podatke osobe koja dolazi na kraj liste!\n");
	printf("Unesite ime osobe: ");
	scanf(" %s", o.ime);
	printf("Unesite prezime osobe: ");
	scanf(" %s", o.prezime);
	printf("Unesite godiste osobe: ");
	scanf(" %d", &o.godiste);
	UnosNaKraj(o, &Head);
	Ispis(Head.Next);
	printf("Unesite trazeno prezime: ");
	scanf(" %s", o.prezime);
	TraziPoPrez(o, &Head);
	printf("Unesite prezime osobe koju zelite izbrisati iz liste: ");
	scanf(" %s", o.prezime);
	Brisi(o, &Head);
	printf("Vase osobe su:\n");
	Ispis(Head.Next);
	return ZAVRSEN_KOD;
}

void UnosNaPocetak(Osoba a, Pozicija p) {
	Pozicija q;
	q = (Pozicija)malloc(sizeof(Osoba));
	if (q == NULL) {
		printf("Memorija nije dinamicki alocirana!\n");
		return NEUSPJELA_DINAMICKA_ALOKACIJA;
	}
	else {
		printf("Memorija alocirana!\n");
	}
	*q = a;
	q->Next = p->Next; // Neka Q pokazuje na onoga koga je pokaziva P prije
	p->Next = q; // Neka P pokazuje na Q
}

void UnosNaKraj(Osoba a, Pozicija p) {
	Pozicija q;
	while (p->Next != NULL) {
		p = p->Next;
	}
	q = (Pozicija)malloc(sizeof(Osoba));
	if (q == NULL) {
		printf("Memorija nije dinamicki alocirana!\n");
		return NEUSPJELA_DINAMICKA_ALOKACIJA;
	}
	else {
		printf("Memorija alocirana!\n");
	}
	*q = a;
	p->Next = q;
	q->Next = NULL;
}

void Ispis(Pozicija p) {
	while (p != NULL) { // Vrti sve dok Pozicija ne bude NULL
		printf(" %s\t %s \t %d \n", p->ime, p->prezime, p->godiste);
		p = p->Next; // Neka p bude adresa sljedeceg
	}
}

void TraziPoPrez(Osoba a, Pozicija p) {
	while (p != NULL && strcmp(p->prezime, a.prezime)) { //Dok ne dodje do kraja ili će stati kad nadjemo to trazeno prezime
		p = p->Next;
	}
	if (p == NULL) {
		printf("Osoba s tim prezimenom nije pronadena!\n");
	}
	else {
		printf("Osoba pronadena: ");
		printf(" %s\t %s\t %d \n", p->ime, p->prezime, p->godiste);
	}
}

Pozicija TraziPrethodnika(Osoba a, Pozicija p) {
	Pozicija prev;
	prev = p;
	p = p->Next;
	while (p != NULL && strcmp(p->prezime, a.prezime)) { //Dok ne dodje do kraja ili će stati kad nadjemo to trazeno prezime
		prev = prev->Next;
		p = p->Next;
	}
	if (p == NULL)
		return NULL;
	else
		return prev;
}

void Brisi(Osoba a, Pozicija p) {
	p = TraziPrethodnika(a, p);
	if (p == NULL)
		printf("Nema osobe s tim prezimenom\n");
	else
		p->Next = p->Next->Next; //Pokazivac prethodnika pokazuje na sljedbenika (preskocen 1 element liste)
}