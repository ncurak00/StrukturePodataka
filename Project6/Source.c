#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define USPJEH (1)

typedef struct cvor* pozicija;
typedef struct cvor
{
	int el;
	pozicija l;
	pozicija d;
}stablo;

pozicija alokacija_memorije(int);
pozicija unos(int, pozicija);
int ispis_inorder(pozicija);
int ispis_preorder(pozicija);
int ispis_postorder(pozicija);
pozicija brisi(int, pozicija);
pozicija TraziMin(pozicija);
pozicija TraziMax(pozicija);
pozicija trazi(int, pozicija);

int main() {
	pozicija p = NULL;
	p = unos(2, p);
	p = unos(3, p);
	p = unos(4, p);
	p = unos(1, p);
	int izbor = 0, el;
	pozicija temp = NULL;

	do {
		printf("Odaberi:\n");
		printf("1 - Unos\n");
		printf("2 - Ispis inorder\n");
		printf("3 - Ispis postorder\n");
		printf("4 - Ispis preorder \n");
		printf("5 - Trazenje elementa\n");
		printf("6 - Brisanje elementa\n");
		printf("7 - Izlaz\n");
		scanf("%d", &izbor);
		switch (izbor) {
		case 1:
			printf("Unesi element koji zelis unijeti:\n");
			scanf("%d", &el);
			p = unos(el, p);
			break;
		case 2:
			ispis_inorder(p);
			break;
		case 3:
			ispis_postorder(p);
			break;
		case 4:
			ispis_preorder(p);
			break;
		case 5:
			printf("Unesi element koji trazis:\n");
			scanf("%d", &el);
			temp = trazi(el, p);
			if (temp)
				printf("Element %d se nalazi na adresi %d\n", temp->el, temp);
			break;
		case 6:
			printf("Unesi element koji brises:\n");
			scanf("%d", &el);
			p = brisi(el, p);
		case 7:
			break;
		default:
			printf("Pogresan unos!\n");
		}
	} while (izbor != '7');
	return 0;
}

pozicija alokacija_memorije(int el) {
	pozicija nova = (pozicija)malloc(sizeof(stablo));
	if (!nova)
	{
		printf("Problem s alokacijom memorije!\n");
		return nova;
	}
	nova->el = el;
	nova->lijevo = NULL;
	nova->desno = NULL;
	return nova;
}

pozicija unos(int el, pozicija p) {
	if (!p)
		return alokacija_memorije(el);
	else if (el < p->el)
		p->lijevo = unos(el, p->lijevo);
	else if (el > p->el)
		p->desno = unos(el, p->desno);
	return p;
}

/*int ispis_inorder(pozicija p) {
	if(p){
		print(p->lijevo);
		printf("%d", p->el);
		print(p->desno);
	}
	return USPJEH;
}*/

int ispis_preorder(pozicija p) {
	if (p){
		printf("%d", p->el);
		print(p->lijevo);
		print(p->desno);
	}
	return USPJEH;
}

int ispis_postorder(pozicija p) {
	if (p){
		print(p->lijevo);
		print(p->desno);
		printf("%d", p->el);	
	}
	return USPJEH;
}

pozicija brisi(int el, pozicija p) {
	pozicija temp = NULL;
	if (!p)
		return p;
	else if (el < p->el)
		p->lijevo = brisi(el, p->lijevo);
	else if (el > p-el)
		p->desno = brisi(el, p->desno);
	else {
		if (p->lijevo && p->desno) {
			temp = TraziMin(p->desno);
			p->el = temp->el;
			p->desno = brisi(temp->el, p->desno);
		}
		else {
			temp = p;
			if (!p->lijevo)
				p = p->desno;
			else if (!p->desno)
				p = p->lijevo;
			free(temp);
		}
	}
	return p;
}

pozicija TraziMin(pozicija p) {
	while (p->lijevo != NULL)
		p = p->lijevo;
	return p;
}

pozicija TraziMax(pozicija p) {
	while (p->desno != NULL)
		p = p->desno;
	return p;
}

pozicija trazi(int el, pozicija p) {
	if (!p)
		return p;
	else if (el < p->el)
		return trazi(el, p->el);
	else if (el > p->el)
		return trazi(el, p->el);
	else
		return p;
}