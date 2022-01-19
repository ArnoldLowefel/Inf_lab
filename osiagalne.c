#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//indent -linux 
struct lista {
	int *val;
	struct lista *next;
};
typedef struct lista Tlista;

struct wezel {
	int numer;
	char *nazwa;
	bool odwiedzony;
	Tlista *sasiedzi;
};
typedef struct wezel Twezel;

struct magazyn {
	Twezel *element;
	struct magazyn *next;
};
typedef struct magazyn Tmagazyn;

Tlista *push_lista(Tlista * l, int w)
{
	Tlista *new = malloc(sizeof(Tlista));
	*(new->val) = w;
	new->next = l;
	return new;
}

Tmagazyn *zanicjalizuj_magazyn()
{
	Tmagazyn *first = malloc(sizeof(Tmagazyn));
	first->next = NULL;
	first->element = NULL;
	return first;
}

void dodaj(Tmagazyn * m, Twezel * w)
{
	Tmagazyn *new = malloc(sizeof(Tmagazyn));
	new->element = w;
	new->next = m->next;
	m->next = new;
}

bool pusty(Tmagazyn * m)
{
	if (m->element == NULL) {
		return true;
	} else {
		return false;
	}
}

Twezel *pobiez(Tmagazyn * m)
{
	Tmagazyn *temp = m->next;
	m->next = temp->next;
	Twezel *w = temp->element;
	free(temp);
	return w;
}

Twezel *top(Tmagazyn * m)
{
	return (m->next)->element;
}

void spacer(Twezel * graf[], int n)
{
	graf[0]->odwiedzony = true;
	for (int i = 1; i < n; i++) {
		graf[i]->odwiedzony = false;
	}
	Tmagazyn *magazyn = zanicjalizuj_magazyn();
	dodaj(magazyn, graf[0]);
	Twezel *aktualny;
	Tlista *l;
	while (!pusty(magazyn)) {
		aktualny = pobiez(magazyn);
		l = graf[aktualny->numer]->sasiedzi;
		while (l != NULL) {
			if (!(graf[*(l->val)]->odwiedzony)) {
				graf[*(l->val)]->odwiedzony = true;
				dodaj(magazyn, graf[*(l->val)]);
			}
		}
		l = l->next;
	}
}

int main()
{
	return 0;
}
