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
	char ime[MAX_LINE];
	pozicija dijete;
	pozicija_stoga next;
}stog;

pozicija Push(pozicija_stoga, pozicija);
pozicija Pop(pozicija_stoga);
int DodajNovog(pozicija, pozicija);
int IspisDirektorija(pozicija, int);
int MaliIspisDirektorija(pozicija, int);
int OtidiUDirektorij(pozicija_stoga, pozicija, char*);


int main() {
	pozicija root = (pozicija)malloc(sizeof(cvor));
	root->brat = NULL;
	root->dijete = NULL;
	stog head;
	head.next = NULL;
	head.dijete = NULL;
	strcpy(root->ime, "C:");

	pozicija trenutni = Push(&head, &root);
	strcpy(trenutni->ime, root->ime);
	int cmd = 0;
	do {
		printf("\nOdaberite naredbu: \n");
		printf("Unesi 1 - md\nUnesi 2 - cd dir\nUnesi 3 - cd..\n");
		printf("Unesi 4 - dir\nUnesi 5 - izlaz\n");
		scanf("%d", &cmd);
		switch (cmd)
		{
		case 1:
			printf("Unesite ime novog direktorija: ");
			char ime_novog[MAX_LINE];
			scanf(" %s", ime_novog);
			DodajNovog(ime_novog, trenutni);
			break;

		case 2://Nesto ne stima
			if (!trenutni->dijete)
			{
				printf("Trenutni direktorij je prazan! \n");
				break;
			}
			printf("Ovaj direktorij sadrzi sljedeæe direktorije: \n");
			MaliIspisDirektorija(trenutni->dijete,0);
			printf("Unesite ime direktorija u koji zelite uci: ");
			char ime[MAX_LINE];
			scanf(" %s", ime);
			OtidiUDirektorij(&head,trenutni->dijete, ime);
			break;
		case 3:
			if (!strcmp(trenutni->ime, "C:"))
			{
				printf("Vec ste u glavnom direktoriju! \n");
				break;
			}
			trenutni = Pop(&head);
			break;
		case 4:
			if (trenutni->dijete) {
				printf("\n %s\n", trenutni->ime);
				IspisDirektorija(trenutni->dijete, 0);
			}
			else
				printf("Trenutni direktoriji je prazan! \n");
			break;
		case 5:
			break;
		default:
			printf("Krivi unos!\n");
			break;
		}

	} while (cmd != 5);
	return 0;
}

pozicija Push(pozicija_stoga head, pozicija novi) {
	novi->dijete = head->next;
	head->next = novi;
	return novi;
}

pozicija Pop(pozicija_stoga p) {
	pozicija_stoga q = p->next;
	p = p->next->next;
	free(q);
	return  p;

}
int DodajNovog(char* ime, pozicija trenutni)//abecedno
{
	pozicija novi = (pozicija)malloc(sizeof(cvor));
	if (novi == NULL) {
		printf("Memorija nije dinamicki alocirana!\n");
		return NULL;
	}
	strcpy(novi->ime, ime);
	if (trenutni->dijete == NULL)
	{
		novi->brat = NULL;
		novi->dijete = NULL;
		trenutni->dijete = novi;
		return EXIT_SUCCES;
	}
	pozicija p = trenutni->dijete;
	if (strcmp(p, novi) > 0)
	{
		novi->brat = p;
		novi->dijete = NULL;
		trenutni->dijete = novi;
		return EXIT_SUCCES;
	}
	while (p->brat && strcmp(p->brat->ime, novi->ime) < 0)
		p = p->brat;
	novi->brat = p->brat;
	p->brat = novi;
	p->dijete = NULL;


	return EXIT_SUCCES;
}
int IspisDirektorija(pozicija p, int uvlaka) {
	uvlaka += 2;
	int i = 0;
	while (p) {
		for (i = 0; i < uvlaka; i++)
			printf(" ");
		printf("%s\n", p->ime);
		if (p->dijete)
			IspisDirektorija(p->dijete, uvlaka + 2);
		p = p->brat;
	}
	return EXIT_SUCCESS;
}
int MaliIspisDirektorija(pozicija p, int uvlaka) {
	uvlaka += 2;
	int i = 0;
	while (p) {
		for (i = 0; i < uvlaka; i++)
			printf(" ");
		printf("%s\n", p->ime);
		p = p->brat;
	}
	return EXIT_SUCCESS;
}
int OtidiUDirektorij(pozicija_stoga head, pozicija trenutni, char* ime) {
	pozicija p = trenutni->dijete;
	while (p)
	{
		if (!strcmp(p->ime, ime))
		{
			trenutni=Push(head, p);
			strcpy(trenutni->ime, ime);
			break;
		}
		p = p ->brat;
	}
	printf("Nije pronaden direktorij s tim imeneom! \n");
	return EXIT_SUCCES;

}
