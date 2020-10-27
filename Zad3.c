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
	if (i <= 1) {
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
Pok Trazi(Pok p)
{
	char prezime[50];

	printf("Unesite prezime osobe koje zelite pronaci: ");
	scanf("%s", prezime);

	while (strcmpi(p->prezime, prezime) != 0 && p != NULL)
		p = p->next;
	return p;
}
Pok TraziPrev(Pok p)
{
	char prezime[50];
	Pok prev;
	prev = p;
	p = p->next;

	printf("Unesite prezime osobe koje zelite pronaci: ");
	scanf("%s", prezime);

	while (strcmpi(p->prezime, prezime) != 0 && p != NULL) {
		prev = p;
		p = p->next;
	}

	return prev;
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
int Sort(Pok p)
{

}
int Write(Pok p)
{
	FILE *dat;

}
int Read(Pok p)
{

}
int main()
{
	Osoba *q;
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
		printf("\n\t5 - dodavanje iza elementa");
		printf("\n\t6 - dodavanje ispred elementa");
		printf("\n\t7 - sortiranje liste po prezimenu");
		printf("\n\t8 - citanje iz datoteke");
		printf("\n\t9 - upisivanje liste u datoteku");
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
			q = Trazi(head.next);
			if (q == NULL)
				printf("\n Osoba ne postoji u listi!\n");
			else
				printf("\n\tOsoba je: %s %s, %d\n", q->ime, q->prezime, q->god_rod);
			break;
		case '4':
			Brisi(&head);
			break;
		case '5':
			q = Trazi(head.next);
			if (q == NULL)
				printf("\n Osoba ne postoji u listi!\n");
			else
				UnosP(q);
			break;
		case '6':
			q = TraziPrev(&head);
			if (q == NULL)
				printf("\n Osoba ne postoji u listi!\n");
			else
				UnosP(q);
			break;
		case '7':
			break;
		case '8':
			break;
		case '9':
			break;
		}
	}
	return 0;
}