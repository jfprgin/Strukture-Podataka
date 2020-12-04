#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct _osoba;
typedef struct _osoba Osoba;
typedef struct _osoba* Pok;

struct _osoba {
	char ime[50];
	char prezime[50];
	int god_rod;
	Pok next;
};

int UnosP(Pok);
int Ispis(Pok);
int UnosK(Pok);
int Trazi(Pok);
int Brisi(Pok);

int main()
{
	Osoba head;
	char izbor = 0;
	head.next = NULL;
	while (izbor != 'K' && izbor != 'k') {
		printf("\nUnesi:");
		printf("\n\t0 - unos elementa na pocetak");
		printf("\n\t1 - ispis niza");
		printf("\n\t2 - unos elementa na kraj");
		printf("\n\t3 - trazenje elementa u listi po prezimenu");
		printf("\n\t4 - brisanje");
		printf("\n\tk - kraj\n");
		printf("\nUnesi: ");
		scanf(" %c", &izbor);
		switch (izbor)
		{
		case '0':
			UnosP(&head);
			break;
		case '1':
			Ispis(head.next);
			break;
		case '2':
			UnosK(&head);
			break;
		case '3':
			Trazi(&head);
			break;
		case '4':
			Brisi(&head);
			break;
		}
	}
	return 0;
}

int UnosP(Pok p)
{
	Pok q;
	q = (Pok)malloc(sizeof(Osoba));

	if (q == NULL) {
		printf("Greska pri alocrianju memorije\n");
		return -1;
	}
	printf("\nUnesite podatke o osobi: ");
	scanf("%s %s %d", &q->ime, &q->prezime, &q->god_rod);
	q->next = p->next;
	p->next = q;

	return 0;
}
int Ispis(Pok p)
{
	int i = 0;
	while (p != NULL) {
		printf("\n%s %s %d\n", p->ime, p->prezime, p->god_rod);
		p = p->next;
		i++;
	}
	if (i < 1) {
		printf("\nNiz je prazan\n");
		return -1;
	}

	return 0;
}
int UnosK(Pok p)
{
	Pok q;
	q = (Pok)malloc(sizeof(Osoba));

	if (q == NULL) {
		printf("Greska pri alocrianju memorije\n");
		return -1;
	}

	printf("\nUnesite podatke o osobi: ");
	scanf("%s %s %d", &q->ime, &q->prezime, &q->god_rod);

	while (p->next != NULL)
		p = p->next;
	q->next = p->next;
	p->next = q;

	return 0;
}
int Trazi(Pok p)
{
	char prezime[50];

	printf("Unesite prezime osobe koje zelite pronaci: ");
	scanf("%s", prezime);

	while (strcmpi(p->prezime, prezime) != 0 && p != NULL)
		p = p->next;
	if (p == NULL) {
		printf("Nema osobe s tim prezimenom");
		return -1;
	}
	printf("\n%s %s %d\n", p->ime, p->prezime, p->god_rod);

	return 0;
}
int Brisi(Pok p)
{

	char prezime[50];
	printf("Unesite prezime osobe koje zelite izbrisati: ");
	scanf("%s", &prezime);
	Pok prev;
	prev = p;
	p = p->next;
	while (p != NULL) {
		if (strcmpi(p->prezime, prezime) == 0) {
			prev->next = p->next;
			p = p->next;
		}
		prev = p;
		p = p->next;
	}
	return 0;
}