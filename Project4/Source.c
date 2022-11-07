#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE (128)
#define FILE_DIDNT_OPEN_ERROR (-1)
#define EMPTY_LIST (-1)

typedef struct polinom* pozicija;

typedef struct polinom {
	int koef; //koeficijent
	int pot; //potencija
	pozicija next;
}polinom;

int sortiraniUnos(pozicija, pozicija);
int sortiraniUnosIzDatoteke(char*, pozicija[], int);
int ispisPolinoma(pozicija);
int zbrajanje(pozicija[], int, pozicija);
int umnozak(pozicija, pozicija, pozicija);


int main() {
	int i = 0;
	char buffer[MAX_LINE] = {0};
	pozicija p[MAX_LINE] = {0};
	int br = 0;
	polinom HeadZbroj = {
		.koef = 0,
		.pot = 0,
		.next = NULL
	};

	polinom HeadProdukt = {
		.koef = 0,
		.pot = 0,
		.next = NULL
	};

	FILE* fp = NULL;
	fp = fopen("polinomi.txt", "r");
	if (fp == NULL){
		printf("Greska u otvaranju datoteke!\n");
		return FILE_DIDNT_OPEN_ERROR;
	}
	while (!feof(fp)){
		fgets(buffer, MAX_LINE, fp);
		if (strcmp("\n", buffer) != 0) {
			br++;
		}
	}
	sortiraniUnosIzDatoteke("polinomi.txt", p, br);
	printf("a");
	for(i=0; i<br; i++)
	ispisPolinoma(p[i]);
	return EXIT_SUCCESS;
}

int sortiraniUnosIzDatoteke(char* imedatoteke, pozicija p[], int br) {
	int i = 0;
	int n = 0; // brojac ucitanih znakova koristeci sscanf
	int a = 0; // broj indeksa u nizu p(headova)
	int b = 0; // broj pomaka kod ucitavanja polinoma u sscanfu
	int check = 0;
	char buffer[MAX_LINE] = {0};
	pozicija temp=NULL;
	temp = (pozicija)malloc(sizeof(polinom));
	if (temp == NULL)
	{
		printf("Neuspjesna alokacija memorije!\n");
		return 1;
	}
	FILE* fp = NULL;
	fp = fopen(imedatoteke, "r");
	if (fp == NULL) {
		printf("Greska u otvaranju datoteke!\n");
		return FILE_DIDNT_OPEN_ERROR;
	}
	for (i = 0; i < br; i++) {
		fgets(buffer, MAX_LINE, fp);
		if (strcmp("\n", buffer) != 0) 
		{
			check=sscanf(buffer, "%d %d %n", temp->koef, temp->pot, &n);
			sortiraniUnos(temp, p[a]);
			b = b + n;
			
			while (check == 2) 
			{
				check = sscanf(buffer+b, "%d %d %n", temp->koef, temp->pot, &n);
				if(check==2)
				sortiraniUnos(temp, p[a]);
				b = b + n;
			}
		}
		b = 0;
		a++;
	}
	return EXIT_SUCCESS;
}

int sortiraniUnos(pozicija temp, pozicija p) {
	while (p->next != NULL && temp->pot > p->next->pot) {
		p = p->next;
	}
	temp->next = p->next;
	p->next = temp;
	return EXIT_SUCCESS;
}

int ispisPolinoma(pozicija p) {
	while (p != NULL) {
		if (p->koef == 1)
			printf("x");
		else
			printf("%dx", p->koef);
		if (p->pot != 1)
			printf("^%d", p->pot);
		if(p->next!=NULL)
		printf(" + ");
		p = p->next;
	}
	return EXIT_SUCCESS;
}

int zbrajanje(pozicija p[], int br, pozicija q) {
	int i = 0;
	int j = 0;
	int x = 0;
	pozicija s=NULL;
	pozicija d=NULL;
	d = (pozicija)malloc(sizeof(polinom));
	if (d == NULL)
	{
		printf("Neuspjesna alokacija memorije!\n");
		return 1;
	}
	s = (pozicija)malloc(sizeof(polinom));
	if (s == NULL)
	{
		printf("Neuspjesna alokacija memorije!\n");
		return 1;
	}
	for (i = 0; i < 10; i++) {
		x = 0;
		for (j = 0; j < br; j++) {
			s = p[j];
			while (s->next != NULL) {
				if (s->pot == i)
					x = x + s->koef;
				s = s->next;
			}
		}
		if (x != 0) {
			d->koef = x;
			d->pot = i;
			sortiraniUnos(d, q);
		}
	}
}

int umnozak(pozicija p, pozicija q, pozicija r) {
	int a=0;
	int b=0;
	pozicija e = NULL;
	e = (pozicija)malloc(sizeof(polinom));
	if (e == NULL)
	{
		printf("Neuspjesna alokacija memorije!\n");
		return 1;
	}
	while (p->next != NULL) {
		while (q->next != NULL) {
			a = p->next->koef * q->next->koef;
			b = p->next->pot + q->next->pot;
			e->koef = a;
			e->pot = b;
			sortiraniUnos(e, q);
		}
	}
}