#define _CRT_SECURE_NO_WARNINGS

#define NEUSPJELA_DINAMICKA_ALOKACIJA (-1)
#define MAX_LINE (50)
#define EXIT_SUCCES (1)

#include<stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct cvor* pozicija;
typedef struct cvor {
	char ime[MAX_LINE];
	pozicija dijete;
	pozicija brat;
}cvor;

typedef struct stog* pozicija_stoga;
typedef struct stog {
	pozicija dijete;
	pozicija_stoga next;
}stog;

pozicija md(pozicija, char*);
int Push(float, pozicija);
int Pop(float*, pozicija);


int main() {
	pozicija root = NULL;
	root = (pozicija)malloc(sizeof(cvor));
	if (root == NULL) {
		printf("Memorija nije dinamicki alocirana!\n");
		return NULL;
	}
	stog head;
	head.next = NULL;
	head.dijete = NULL;
	strcpy(root->ime, "C:");
	pozicija trenutno = NULL;
	int cmd=0;
	do {
		printf("Odaberite naredbu: \n ");
		printf("Unesi 1 - md\nUnesi 2 - cd dir\nUnesi 3 - cd..\n");
		printf("Unesi 4 - dir\nUnesi 5 - izlaz\n");
		scanf("%d", &cmd);
		switch (cmd)
		{
			case 1:
				printf("Unesite ime novog direktorija: ");
				char ime_novog[MAX_LINE];
				scanf("%s", ime_novog);
				if (trenutno == root)
					Push(trenutno);
				break;

			case 2:
				
				break;
			case 3:
				
				break;
			case 4:
				
				break;
			default:
				break;
		}

	} while (cmd != 5);
	return 0;
}

pozicija md(pozicija trenutno, char* ime) {
	pozicija q;
	q = (pozicija)malloc(sizeof(cvor));
	if (q == NULL) {
		printf("Memorija nije dinamicki alocirana!\n");
		return NULL;
	}
	strcpy(q->ime, ime);
	if (!trenutno->dijete) {
		trenutno->dijete = q;
	}
	else {
		pozicija tempDijete = trenutno->dijete;
		while (tempDijete->brat)
			tempDijete = tempDijete->brat;
		q->brat = NULL;
		tempDijete->brat = q;
	}
	return trenutno;
}

int Push(pozicija p) {
	pozicija q = NULL;
	q = (pozicija)malloc(sizeof(cvor));
	if (q == NULL)
	{
		printf("Memorija nije alocirana!\n");
		return NULL;
	}
	q->brat = p->brat;
	p->brat = q;

	return EXIT_SUCCESS;
}

int Pop(float* element_out, pozicija p) {
	pozicija q = NULL;
	q = (pozicija)malloc(sizeof(cvor));
	if (q == NULL)
	{
		printf("Memorija nije alocirana!\n");
		return NULL;
	}
	q = p->next;
	*element_out = q->broj;
	p->next = q->next;

	free(q);
	return EXIT_SUCCESS;
}
