#define _CRT_SECURE_NO_WARNINGS
#define EXIT_SUCCESS (1)

#include<stdlib.h>
#include<stdio.h>

typedef struct cvor* pozicija;
typedef struct cvor {
	int broj;
	pozicija l;
	pozicija d;
}cvor;

pozicija Unos(pozicija p, pozicija q);
void IspisInorder(pozicija p);
void IspisPreorder(pozicija p);
void IspisPostorder(pozicija p);
pozicija Brisi(pozicija p, int br);
pozicija TraziMax(pozicija p);
pozicija TraziMin(pozicija p);
pozicija Trazi(pozicija p, int br);

int main() {
	pozicija root = NULL;
	int izbor;
	do {
		printf("\nOdaberi:\n");
		printf("1 - Unos\n");
		printf("2 - Ispis preorder\n");
		printf("3 - Ispis inorder\n");
		printf("4 - Ispis postorder \n");
		printf("5 - Brisanje elementa\n");
		printf("6 - Trazenje elementa\n");
		printf("7 - Izlaz\n");
		scanf(" %d", &izbor);
		switch (izbor) {
		case 1:
			printf("\nUnesite novi element:");
			int novi_broj;
			scanf(" %d", &novi_broj);
			pozicija novi = (pozicija)malloc(sizeof(cvor));
			novi->broj = novi_broj;
			novi->l = NULL;
			novi->d = NULL;
			root = Unos(root, novi);
			break;
		case 2:
			IspisPreorder(root);
			break;
		case 3:
			IspisInorder(root);
			break;
		case 4:
			IspisPostorder(root);
			break;
		case 5:
			printf("Unesite element koji zelite izbrisati\n");
			int brisi_broj;
			scanf(" %d", &brisi_broj);
			root = Brisi(root, brisi_broj);
			break;
		case 6:
			printf("Unesite element koji zelite pronaci\n");
			int trazeni_broj; pozicija temp;
			scanf(" %d", &trazeni_broj);
			temp = Trazi(root, trazeni_broj);
			if (temp) {
				printf("Element %d nalazi se u stablu na adresi %d\n", temp->broj, temp);
			}
			else {
				printf("Element koji ste unijeli nepostoji u stablu");
			}
			break;
		case 7:
			break;
		default:
			printf("Pogresan unos!");
		}
	} while (izbor != 7);

	return 0;
}

pozicija Unos(pozicija p, pozicija q) {
	if (p == NULL)
		return q;
	if (p->broj < q->broj){
		p->d = Unos(p->d, q);
	}
	else if (p->broj > q->broj){
		p->l = Unos(p->l, q);
	}
	else
		free(q);
	return p;
}

void IspisInorder(pozicija p){
	if (p == NULL)
		return NULL;
	else {
		IspisInorder(p->l);
		printf(" %d", p->broj);
		IspisInorder(p->d);
	}
}

void IspisPreorder(pozicija p){
	if (p == NULL)
		return NULL;
	else {
		printf(" %d", p->broj);
		IspisPreorder(p->l);
		IspisPreorder(p->d);
	}
}

void IspisPostorder(pozicija p){
	if (p == NULL)
		return NULL;
	else {
		IspisPostorder(p->l);
		IspisPostorder(p->d);
		printf(" %d", p->broj);
	}
}

pozicija Brisi(pozicija p, int br){
	if (p == NULL)
		return NULL;
	if (p->broj < br)
		p->d = Brisi(p->d, br);
	else if (p->broj > br)
		p->l = Brisi(p->l, br);
	else {
		if (p->l){
			pozicija temp = TraziMax(p->l);
			p->broj = temp->broj;
			p->l = Brisi(p->l, temp->broj);
		}
		else if (p->d){
			pozicija temp = TraziMin(p->d);
			p->broj = temp->broj;
			p->d = Brisi(p->d, temp->broj);
		}
		else{
			free(p);
			return NULL;
		}
	}
	return p;
}

pozicija TraziMax(pozicija p){
	while (p->d)
		p = p->d;
	return p;
}

pozicija TraziMin(pozicija p){
	while (p->l)
		p = p->l;
	return p;
}

pozicija Trazi(pozicija p, int br) {
	while (p != NULL && p->broj != br){
		if (p->broj < br)
			p = p->d;
		else
			p = p->l;
	}
	return p;
}
