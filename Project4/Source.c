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

int sortiraniUnos(int,int, pozicija);
int sortiraniUnosIzDatoteke(char*, pozicija[], int);
int ispisPolinoma(pozicija);
pozicija zbrajanje(pozicija*, int);
pozicija umnozak(pozicija*,int);
pozicija ZbrajanjeDvaPolinoma(pozicija, pozicija);
pozicija mnozenjeDvaPolinoma(pozicija, pozicija);

int main() {
	int i = 0;
	char buffer[MAX_LINE] = {0};
	pozicija* p=NULL;
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
	pozicija pricuva = malloc(sizeof(polinom));
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
	p = malloc(br * sizeof(struct polinom));
	for (i = 0; i < br; i++) {
		p[i] = (pozicija)malloc(sizeof(polinom));
		if (p[i] == NULL) {
			printf("Greska u alokaciji memorije\n");
			return -1;
		}
		p[i]->next = NULL;
	}
	sortiraniUnosIzDatoteke("polinomi.txt", p, br);
	for(i=0; i<br; i++){
		printf("\npolinom %d: ", i + 1);
		ispisPolinoma(p[i]);}
	pricuva = p;
	printf("\npolinom zbroja: ");
	HeadZbroj.next = zbrajanje(p, br);
	ispisPolinoma(HeadZbroj.next);
	p = pricuva;
	printf("\npolinom umnoska: ");
	HeadProdukt.next = umnozak(p, br);
	
	/*pricuva = HeadProdukt.next;
	while (HeadProdukt.next->next != NULL)
	{
		printf("a");
		if (HeadProdukt.next->pot == HeadProdukt.next->next->pot){
			HeadProdukt.next->koef = HeadProdukt.next->koef + HeadProdukt.next->next->koef;
			HeadProdukt.next = HeadProdukt.next->next->next;}
		else
		HeadProdukt.next = HeadProdukt.next->next;
	}
	HeadProdukt.next = pricuva;*/

	ispisPolinoma(HeadProdukt.next);
	/*HeadProdukt.next = ZbrajanjeDvaPolinoma(HeadProdukt.next, HeadProdukt.next);
	printf("a");
	while (HeadProdukt.next != 0) {
		HeadProdukt.next->koef = HeadProdukt.next->koef / 2;
		HeadProdukt.next = HeadProdukt.next->next;
	}
	ispisPolinoma(HeadProdukt.next);*/
	
	return EXIT_SUCCESS;
}

int sortiraniUnosIzDatoteke(char* imedatoteke, pozicija p[], int br) {
	int i = 0;
	int n = 0; // brojac ucitanih znakova koristeci sscanf
	int a = 0; // broj indeksa u nizu p(headova)
	int b = 0; // broj pomaka kod ucitavanja polinoma u sscanfu
	int koef=0,pot=0;
	int check = 0;
	char buffer[MAX_LINE] = {0};
	pozicija temp;
	FILE* fp = NULL;
	fp = fopen(imedatoteke, "r");
	if (fp == NULL) {
		printf("Greska u otvaranju datoteke!\n");
		return FILE_DIDNT_OPEN_ERROR;
	}
	for (i = 0; i < br; i++) {
		temp = (pozicija)malloc(sizeof(polinom));
		fgets(buffer, MAX_LINE, fp);
		if (strcmp("\n", buffer) != 0) 
		{
			check=sscanf(buffer, "%d %d %n", &koef, &pot, &n);
			sortiraniUnos(koef,pot, p[a]);
			b = b + n;
			
			while (check == 2) 
			{
				check = sscanf(buffer+b, "%d %d %n", &koef, &pot, &n);
				if(check==2)
				sortiraniUnos(koef,pot, p[a]);
				b = b + n;
			}
		}
		b = 0;
		a++;
	}
	return EXIT_SUCCESS;
}

int sortiraniUnos(int koef,int pot, pozicija p) {
	pozicija temp= (pozicija)malloc(sizeof(polinom));
	temp->koef = koef;
	temp->pot = pot;
	while (p->next != NULL && pot < p->next->pot) {
		p = p->next;
	}
	temp->next = p->next;
	p->next = temp;
	return EXIT_SUCCESS;
}

int ispisPolinoma(pozicija p) {
	p = p->next;
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

pozicija zbrajanje(pozicija *p, int br) {
	int i = 0;
	pozicija ZbrojDvaPolinoma = malloc(sizeof(polinom));
	pozicija q = malloc(sizeof(polinom));
	ZbrojDvaPolinoma->next = NULL;
	for (i = 0; i < br; i++)
		p[i] = p[i]->next;
	
	if (br == 1)
		return p[1];
	ZbrojDvaPolinoma=ZbrajanjeDvaPolinoma(p[0], p[1]);
	q = ZbrojDvaPolinoma;
	for (i = 2; i < br; i++) {
		ZbrojDvaPolinoma = ZbrajanjeDvaPolinoma(q, p[i]);
		q = ZbrojDvaPolinoma;
	}
	return ZbrojDvaPolinoma;
}
pozicija ZbrajanjeDvaPolinoma(pozicija pol1, pozicija pol2) {
	pozicija ZbrojDvaPolinoma = malloc(sizeof(polinom));
	ZbrojDvaPolinoma->next = NULL;
	int pot = 0, koef = 0;
	while (pol1 != NULL && pol2 != NULL)
	{
		if (pol1->pot == pol2->pot) {
			pot = pol1->pot;
			koef = pol1->koef + pol2->koef;
			sortiraniUnos(koef,pot,ZbrojDvaPolinoma);
			pol1 = pol1->next;
			pol2 = pol2->next;
		}
		else if (pol1->pot > pol2->pot) {
			pot = pol1->pot;
			koef = pol1->koef;
			sortiraniUnos(koef,pot, ZbrojDvaPolinoma);
			pol1 = pol1->next;
		}
		else {
			pot = pol2->pot;
			koef = pol2->koef;
			sortiraniUnos(koef,pot, ZbrojDvaPolinoma);
			pol2 = pol2->next;
		}
	}
	while (pol1 != NULL) {
		pot = pol1->pot;
		koef = pol1->koef;
		sortiraniUnos(koef,pot, ZbrojDvaPolinoma);
		pol1 = pol1->next;
	}
	while (pol2 != NULL) {
		pot = pol2->pot;
		koef = pol2->koef;
		sortiraniUnos(koef,pot, ZbrojDvaPolinoma);
		pol2 = pol2->next;
	}
	return ZbrojDvaPolinoma;
}



pozicija umnozak(pozicija* p, int br) {
	int i = 0;
	pozicija umnozakDvaPolinoma = malloc(sizeof(polinom));
	pozicija q = malloc(sizeof(polinom));
	umnozakDvaPolinoma->next = NULL;
	if (br == 1)
		return p[0];
	umnozakDvaPolinoma = mnozenjeDvaPolinoma(p[0], p[1]);
	q = umnozakDvaPolinoma;
	for (i = 2; i < br; i++) {
		umnozakDvaPolinoma = mnozenjeDvaPolinoma(q, p[i]);
		q = umnozakDvaPolinoma;
	}
	return umnozakDvaPolinoma;
}
pozicija mnozenjeDvaPolinoma(pozicija pol1, pozicija pol2) {
	pozicija UmnozakDvaPolinoma = malloc(sizeof(polinom));
	pozicija pricuva = malloc(sizeof(polinom));
	UmnozakDvaPolinoma->next = NULL;
	int pot = 0, koef = 0;
	while (pol1 != NULL){
		pricuva = pol2;
		while (pol2 != NULL) {
			pot = pol1->pot + pol2->pot;
			koef = pol1->koef * pol2->koef;
			sortiraniUnos(koef, pot, UmnozakDvaPolinoma);
			pol2 = pol2->next;
		}
		pol1 = pol1->next;
		pol2 = pricuva;
	}
	
	return UmnozakDvaPolinoma;
}