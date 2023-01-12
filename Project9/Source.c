#define _CRT_SECURE_NO_WARNINGS
#define FILE_ERROR (-1)

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct stablo* pozicijaNaStablo;
typedef struct stablo {
    int broj;
    pozicijaNaStablo left;
    pozicijaNaStablo right;
}stablo;

typedef struct lista* pozicijaNaListu;
typedef struct lista {
    int broj;
    pozicijaNaListu next;
}lista;

stablo* stvaranjeStablo();
lista* stvaranjeLista();
int randomBroj(int min, int max);
int izbrisiStablo(pozicijaNaStablo);
int izbrisiListu(pozicijaNaListu);
pozicijaNaStablo unesi(pozicijaNaStablo, pozicijaNaStablo);
int zamijeni(pozicijaNaStablo);
pozicijaNaStablo inorderLista(pozicijaNaStablo, pozicijaNaListu);
int ispisUFile(char* ime, pozicijaNaListu root);

int main()
{
    srand(time(NULL));
    int niz[10] = { 2,5,7,8,11,1,4,2,3,7 };
    for (int i = 0; i < 10; i++) {
        niz[i] = randomBroj(10, 90);
    }
    pozicijaNaStablo root = NULL;
    root = stvaranjeStablo();
    for (int i = 0; i < 10; i++)
        if (!root->broj)
            root->broj = niz[i];
        else {
            pozicijaNaStablo q = NULL;
            q = stvaranjeStablo();
            q->broj = niz[i];
            root = unesi(root, q);
        }

    pozicijaNaListu head = NULL;
    head = stvaranjeLista();
    root = inorderLista(root, head);
    ispisUFile("stari.txt", head->next);
    //mijenjamo stablo iz slike 1 tako da bude kao na slici 2:
    int temp = root->broj;
    root->broj = zamijeni(root);
    root->broj -= temp;
    pozicijaNaListu head2 = NULL;
    head2 = stvaranjeLista();
    root = inorderLista(root, head2); //elemente stabla stavljamo u listu
    ispisUFile("novi.txt", head2->next);
    izbrisiStablo(root);
    izbrisiListu(head);
    izbrisiListu(head2);
    return 0;
}

stablo* stvaranjeStablo()
{
    stablo* s = NULL;
    s = malloc(sizeof(stablo));
    if (NULL == s) {
        printf("Greska u alokaciji memorije\n");
    }
    else
    {
        s->left = NULL;
        s->right = NULL;
    }
    return s;
}

lista* stvaranjeLista()
{
    lista* l = NULL;
    l = malloc(sizeof(lista));
    if (l == NULL) {
        printf("Greska u alokaciji memorije\n");
    }
    else
        l->next = NULL;
    return l;
}

pozicijaNaStablo unesi(pozicijaNaStablo p, pozicijaNaStablo q)
{
    if (p == NULL)
        return q;
    if (p->broj < q->broj)
        p->left = unesi(p->left, q);
    else if (p->broj > q->broj)
        p->right = unesi(p->right, q);
    else { //ako su jednaki idemo na lijevu stranu jer je tako na slici
        p->left = unesi(p->left, q);
    }
    return p;
}

int zamijeni(pozicijaNaStablo p)
{
    if (p == NULL)
        return 0;
    int sumaLijevo = zamijeni(p->left);
    int sumaDesno = zamijeni(p->right);
    int suma = p->broj + sumaLijevo + sumaDesno;
    p->broj = sumaLijevo + sumaDesno;
    return suma;
}

pozicijaNaStablo inorderLista(pozicijaNaStablo ps, pozicijaNaListu pl)
{
    if (ps == NULL)
        return NULL;
    inorderLista(ps->right, pl);
    pozicijaNaListu q = NULL;
    q = stvaranjeLista();
    q->broj = ps->broj;
    q->next = pl->next; //dodajemo na pocetak liste, al zato smo obrnili pozive na lijevu i desnu stranu (inace se prvo zove ps->left pa poslije ps->right) tako da dobijemo inorder
    pl->next = q;
    inorderLista(ps->left, pl);
    return ps;
}

int izbrisiStablo(pozicijaNaStablo p)
{
    if (p != NULL)
    {
        izbrisiStablo(p->left);
        izbrisiStablo(p->right);
        free(p);
    }
    return 0;
}

int izbrisiListu(pozicijaNaListu head)
{
    pozicijaNaListu temp = NULL;
    while (head->next != NULL)
    {
        temp = head->next;
        head->next = temp->next;
        free(temp);
    }
    free(head);
    return 0;
}

int randomBroj(int min, int max)
{
    int num = (rand() % (max - min + 1)) + min;

    return num;

}

int ispisUFile(char* ime, pozicijaNaListu head)
{
    FILE* fp;
    fp = fopen(ime, "w");

    if (fp == NULL)
    {
        printf("Error\n");
        return FILE_ERROR;
    }
    else
    {
        while (head != NULL)
        {
            fprintf(fp, "%d\n", head->broj);
            head = head->next;
        }
        return 0;
    }
    fclose(fp);
}