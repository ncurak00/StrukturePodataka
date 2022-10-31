#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAKSIMALAN_BROJ_ZNAKOVA (128)
#define ZAVRSEN_KOD (EXIT_SUCCESS)
#define NEUSPJELA_DINAMICKA_ALOKACIJA (-1)
#define NEPRONADEN_ELEMENT (-1)

typedef struct Osoba* Pozicija;

typedef struct Osoba {
	char ime[MAKSIMALAN_BROJ_ZNAKOVA];
	char prezime[MAKSIMALAN_BROJ_ZNAKOVA];
	int godiste;
	Pozicija Next; // Pozicija pokazuje na sljedeci cvor u nizu
}Osoba;

int UnosNaPocetak(Osoba, Pozicija);
void Ispis(Pozicija);
int UnosNaKraj(Osoba, Pozicija);
Pozicija TraziPoPrez(Osoba, Pozicija);
void Brisi(Osoba, Pozicija);
Pozicija TraziPrethodnika(Osoba, Pozicija);
int UnosIza(Osoba , Osoba , Pozicija );
int UnosIspred(Osoba, Osoba, Pozicija);
int SortirajListu(Pozicija);
int IspisUDatoteku(Pozicija, char*);
int IspisIzDatoteke(char*);

int main() {
	Osoba o; 
	Osoba o_nova; // Nova osoba
	Osoba Head;
	Head.Next = NULL;
	Pozicija p;
	int n = 0; // Brojac osoba
	int i = 0;
	int godiste = 0;
	char ime[MAKSIMALAN_BROJ_ZNAKOVA] = { 0 };
	char prezime[MAKSIMALAN_BROJ_ZNAKOVA] = { 0 };
	char imedatoteke[MAKSIMALAN_BROJ_ZNAKOVA] = { 0 };
	char izbor;

	while (1) {
		printf("Unesi A - Unos na pocetak\nUnesi B - Unos na kraj\nUnesi C - Trazenje po prezimenu\n");
		printf("Unesi D - Unos iza elementa\nUnesi E - Unos ispred elementa\nUnesi F - Sortiranje liste\nUnesi G - Ispisivanje u datoteku\n");
		printf("Unesi H - Ispisivanje iz datoteke\nUnesi I - Ispis\nUnesi J - Brisanje\nUnesi X - Izlaz iz programa\n");
		printf("\nUnesite naredbu: ");
		scanf(" %c", &izbor);
		izbor = toupper(izbor);
		if (izbor == 'A') {
			printf("Koliko osoba zelite unijeti: ");
			scanf(" %d", &n);
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
		}
		else if (izbor == 'B') {
			printf("Unesite podatke osobe koja dolazi na kraj liste!\n");
			printf("Unesite ime osobe: ");
			scanf(" %s", o.ime);
			printf("Unesite prezime osobe: ");
			scanf(" %s", o.prezime);
			printf("Unesite godiste osobe: ");
			scanf(" %d", &o.godiste);
			UnosNaKraj(o, &Head);
			Ispis(Head.Next);
		}
		else if (izbor == 'C') {
			printf("Unesite trazeno prezime: ");
			scanf(" %s", o.prezime);
			p = TraziPoPrez(o, &Head);
			if (p != NULL) {
				printf("Osoba pronadena: ");
				printf(" %s\t %s\t %d \n", p->ime, p->prezime, p->godiste);
			}
			else {
				printf("Osoba s tim prezimenom nije pronadena!\n");
			}
		}
		else if (izbor == 'D') {
			printf("Unesi prezime osobe iza koje zelis dodati novu osobu: ");
			scanf(" %s", o.prezime);
			p = TraziPoPrez(o, &Head);
			if (p != NULL) {
				printf("Unesite ime nove osobe: ");
				scanf(" %s", o_nova.ime);
				printf("Unesite prezime nove osobe: ");
				scanf(" %s", o_nova.prezime);
				printf("Unesite godiste nove osobe: ");
				scanf(" %d", &o_nova.godiste);
				UnosIza(o_nova, o, Head.Next);
				printf("Vase osobe su:\n");
				Ispis(Head.Next);
			}
			else {
				printf("Osoba s tim prezimenom nije pronadena!\n");
			}
		}
		else if (izbor == 'E') {
			printf("Unesi prezime osobe ispred koje zelis dodati novu osobu: ");
			scanf(" %s", o.prezime);
			p = TraziPoPrez(o, &Head);
			if (p != NULL) {
				printf("Unesite ime nove osobe: ");
				scanf(" %s", o_nova.ime);
				printf("Unesite prezime nove osobe: ");
				scanf(" %s", o_nova.prezime);
				printf("Unesite godiste nove osobe: ");
				scanf(" %d", &o_nova.godiste);
				UnosIspred(o_nova, o, Head.Next);
				printf("Vase osobe su:\n");
				Ispis(Head.Next);
			}
			else {
				printf("Osoba s tim prezimenom nije pronadena!\n");
			}
		}
		else if (izbor == 'F') {
			SortirajListu(&Head);
			printf("Sortirana lista je:\n");
			Ispis(Head.Next);
		}
		else if (izbor == 'G') {
			printf("Unesite ime datoteke: ");
			scanf(" %s", imedatoteke);
			IspisUDatoteku(Head.Next, imedatoteke);
		}
		else if (izbor == 'H') {
			IspisIzDatoteke(imedatoteke);
		}
		else if (izbor == 'I') {
			Ispis(Head.Next);
		}
		else if (izbor == 'J') {
			printf("Unesite prezime osobe koju zelite izbrisati iz liste: ");
			scanf(" %s", o.prezime);
			Brisi(o, &Head);
			printf("Vase osobe su:\n");
			Ispis(Head.Next);
		}
		else if (izbor == 'X') {
			break;
		}
		else
		printf("Nisi unio ispravno slovo!\n");
	}
	
	return ZAVRSEN_KOD;
}

int UnosNaPocetak(Osoba a, Pozicija p){
	Pozicija q;
	q = (Pozicija)malloc(sizeof(Osoba));
	if (q == NULL) {
		printf("Memorija nije dinamicki alocirana!\n");
		return NEUSPJELA_DINAMICKA_ALOKACIJA;
	}
	else {
		printf("Memorija alocirana!\n");
	}
	strcpy(q->ime, a.ime);
	strcpy(q->prezime, a.prezime);
	q->godiste = a.godiste;
	q->Next = p->Next; // Neka Q pokazuje na onoga koga je pokaziva P prije
	p->Next = q; // Neka P pokazuje na Q

	return ZAVRSEN_KOD;
}

int UnosNaKraj(Osoba a, Pozicija p) {
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
	strcpy(q->ime, a.ime);
	strcpy(q->prezime, a.prezime);
	q->godiste = a.godiste;
	p->Next = q;
	q->Next = NULL;

	return ZAVRSEN_KOD;
}

void Ispis(Pozicija p) {
	while (p != NULL) { // Vrti sve dok Pozicija ne bude NULL
		printf(" %s\t %s \t %d \n", p->ime, p->prezime, p->godiste);
		p = p->Next; // Neka p bude adresa sljedeceg
	}
}

Pozicija TraziPoPrez(Osoba a, Pozicija p) {
	while (p != NULL && strcmp(p->prezime, a.prezime)) { //Dok ne dodje do kraja ili će stati kad nadjemo to trazeno prezime
		p = p->Next;
	}
	return p;
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

int UnosIza(Osoba a, Osoba b, Pozicija p) {
	p = TraziPoPrez(b, p);
	Pozicija q;
	if (p == NULL) {
		printf("Nema osobe s tim prezimenom\n");
		return NEPRONADEN_ELEMENT;
	}
	q = (Pozicija)malloc(sizeof(Osoba));
	if (q == NULL) {
		printf("Memorija nije dinamicki alocirana!\n");
		return NEUSPJELA_DINAMICKA_ALOKACIJA;
	}
	else {
		printf("Memorija alocirana!\n");
	}
	strcpy(q->ime, a.ime);
	strcpy(q->prezime, a.prezime);
	q->godiste = a.godiste;
	q->Next = p->Next;
	p->Next = q;

	return ZAVRSEN_KOD;
}

int UnosIspred(Osoba a, Osoba b, Pozicija p) {
	p = TraziPrethodnika(b, p);
	Pozicija q;
	q = (Pozicija)malloc(sizeof(Osoba));
	if (q == NULL) {
		printf("Memorija nije dinamicki alocirana!\n");
		return NEUSPJELA_DINAMICKA_ALOKACIJA;
	}
	else {
		printf("Memorija alocirana!\n");
	}
	strcpy(q->ime, a.ime);
	strcpy(q->prezime, a.prezime);
	q->godiste = a.godiste;
	q->Next = p->Next;
	p->Next = q;

	return ZAVRSEN_KOD;
}

int SortirajListu(Pozicija p) {  
	Pozicija q = NULL;
	Pozicija prev_q = NULL;
	Pozicija temp = NULL;
	Pozicija end = NULL;
	while (p->Next != end) {
		prev_q = p;
		q = p->Next;
		while (q->Next != end) {
			if (strcmp(q->prezime, q->Next->prezime) > 0) {
				temp = q->Next;
				prev_q->Next = temp;
				q->Next = temp->Next;
				temp->Next = q;

				q = temp;
			}
			prev_q = q;
			q = q->Next;
		}
		end = q;
	}
	return ZAVRSEN_KOD;
}

int IspisUDatoteku(Pozicija p, char* imedatoteke) {
	FILE* fp = NULL;
	fp = fopen(imedatoteke, "w");
	if (fp == NULL)
	{
		printf("Greska u otvaranju datoteke!\n");
		return NEPRONADEN_ELEMENT;
	}
	while (p != NULL) {
		fprintf(fp, "%s\t %s\t %10d\n", p->ime, p->prezime, p->godiste);
		p = p->Next;
	}
	fclose(fp);

	return ZAVRSEN_KOD;
}

int IspisIzDatoteke(char* imedatoteke) {
	char niz[MAKSIMALAN_BROJ_ZNAKOVA];
	FILE* fp = NULL;
	fp = fopen(imedatoteke, "r");
	if (fp == NULL)
	{
		printf("Greska u otvaranju datoteke!\n");
		return NEPRONADEN_ELEMENT;
	}
	while (fgets(niz, MAKSIMALAN_BROJ_ZNAKOVA, fp) != NULL) {
		printf(" %s", niz);
	}
	fclose(fp);

	return ZAVRSEN_KOD;
}
