#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAKSIMALAN_BROJ_ZNAKOVA (11)
#define NEPRONADEN_ELEMENT (-1)
#define MEMORIJA_NIJE_ALOCIRANA (-1)
#define NAZIVNIK_JE_0 (-1)

typedef struct El* pozicija;
typedef struct El {
	float broj;
	pozicija next;
} El;

int IzracunajPostfiks(char*);
int Push(float, pozicija);
int Pop(float* , pozicija);
int BrisiSve(pozicija);

int main() {
	char* postfiks = "postfiks.txt";
	IzracunajPostfiks(postfiks);

	return EXIT_SUCCESS;
}

int IzracunajPostfiks(char* imedatoteke) {
	El head = {
	.broj = 0.0f,
	.next = NULL
	};
	FILE* fp = NULL;
	int rezultat = 0;
	char buffer[MAKSIMALAN_BROJ_ZNAKOVA] = { 0 };
	float broj1 = 0.0f;
	float broj2 = 0.0f;

	fp = fopen(imedatoteke, "r");
	if (fp == NULL)
	{
		printf("Greska u otvaranju datoteke!\n");
		return NEPRONADEN_ELEMENT;
	}

	while (!feof(fp)) {
		fscanf(fp, " %s", buffer);
		int broj = 0;
		rezultat = sscanf(buffer, " %d", &broj);// sscanf ima dodatnu vrijednost koja kaze jesmo li primili taj broj ili nismo, ako jesmo
												// sacuvaj broj 1 u varijablu rezultat, ako nismo u varijablu rezultat ide 0
												// Ako rezultat nije 1, gledaj buffer?
		if (rezultat == 1) {
			// push "number" to stack
			Push(broj, &head);
		}
		else {
			if (strcmp(buffer, "+") == 0) {
				Pop(&broj2, &head); // pop second from stack
				Pop(&broj1, &head); // pop first from stack
				Push(broj1 + broj2, &head); // push first + second to stack
			}
			else if (strcmp(buffer, "-") == 0) {
				Pop(&broj2, &head); // pop second from stack
				Pop(&broj1, &head); // pop first from stack
				Push(broj1 - broj2, &head); // push first - second to stack
			}
			else if (strcmp(buffer, "*") == 0) {
				Pop(&broj2, &head); // pop second from stack
				Pop(&broj1, &head); // pop first from stack
				Push(broj1 * broj2, &head); // push first * second to stack
			}
			else if (strcmp(buffer, "/") == 0) {
				Pop(&broj2, &head); // pop second from stack
				Pop(&broj1, &head); // pop first from stack
				if (broj2 == 0) {
					printf("Nazivnik ne smije biti 0!");
					return NAZIVNIK_JE_0;
				}
				Push(broj1 / broj2, &head); // push first / second to stack
			}
		}
	}
	if (head.next->next == NULL){
		Pop(&broj1, &head);
		printf("Rezultat postfiksa je: %lf", broj1);
	}
	else {
		printf("Falili smo nesto!");
	}
	BrisiSve(&head);
	return EXIT_SUCCESS;
}

int Push(float novi_element, pozicija p) {
	pozicija q = NULL;
	q = (pozicija)malloc(sizeof(El));
	if (q == NULL)
	{
		printf("Memorija nije alocirana!\n");
		return MEMORIJA_NIJE_ALOCIRANA;
	}
	q->broj = novi_element;
	q->next = p->next;
	p->next = q;

	return EXIT_SUCCESS;
}

int Pop(float* element_out, pozicija p) {
	pozicija q = NULL;
	q = (pozicija)malloc(sizeof(El));
	if (q == NULL)
	{
		printf("Memorija nije alocirana!\n");
		return MEMORIJA_NIJE_ALOCIRANA;
	}
	q = p->next;
	*element_out = q->broj;
	p->next = q->next;
	
	free(q);
	return EXIT_SUCCESS;
}

int BrisiSve(pozicija p) {
	pozicija temp;
	while (p->next != NULL) {
		temp = p->next;
		p->next = p->next->next;
		free(temp);
	}
	return EXIT_SUCCESS;
}