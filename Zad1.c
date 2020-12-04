#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct _student;
typedef struct _student Student;
typedef struct _student* Pok;

struct _student {
	char ime[20];
	char prezime[20];
	int bodovi;
};

int Brojac(char*);
int AlokacijaNiz(Pok *, int);
int UcitajIzDat(Pok, char*, int);
int Ispis(Pok, int, int);

int main()
{
	Student *head = NULL;
	int n;
	int max_br_bodova = 0;
	char imedat[50];

	printf("Unesite ime datoteke:");
	scanf(" %s", imedat);

	n = Brojac(imedat);
	if (n == -1)
		return - 1;
	printf("Broj redaka: %d", n);
	AlokacijaNiz(&head, n);
	max_br_bodova = UcitajIzDat(head, imedat, n);
	Ispis(head, max_br_bodova, n);

	return 0;
}

int Brojac(char* imedat)
{
	FILE* fPointer;
	int brojac = 0;
	char* buffer;

	fPointer = fopen(imedat, "r");
	buffer = (char*)malloc(50 * sizeof(char));

	if (fPointer == NULL) {
		printf("Greska pri otvaranju\n");
		return -1;
	}

	while (!feof(fPointer)) {
		fgets(buffer, 50, fPointer);
		brojac++;
	}
	fclose(fPointer);
	free(buffer);

	return brojac;
}
int AlokacijaNiz(Pok *p, int n)
{
	*p = (Pok)malloc(n * sizeof(Student));
	if (p == NULL) {
		printf("Greska pri otvaranju\n");
		return -1;
	}
	return 0;
}
int UcitajIzDat(Pok p, char* imedat, int n)
{
	FILE* fPointer;
	int max_br_bodova = 0;

	fPointer = fopen(imedat, "r");

	if (fPointer == NULL) {
		printf("Greska pri otvaranju\n");
		return -1;
	}
	while (!feof(fPointer)) {
		for (int i = 0; i < n; i++) {
			fscanf(fPointer, " %s %s %d", p[i].ime, p[i].prezime, &p[i].bodovi);
			if (p[i].bodovi > max_br_bodova)
				max_br_bodova = p[i].bodovi;
		}
	}
	fclose(fPointer);
	return max_br_bodova;
}
int Ispis(Pok p, int max_br_bodova, int n)
{
	for (int i = 0; i < n; i++) {
		printf("\n%s %s %d\n", p[i].ime, p[i].prezime, p[i].bodovi);
		printf("Apsolutan broj bodova je %d,a relativan broj bodova je %f.\n", p[i].bodovi, (float)p[i].bodovi / max_br_bodova * 100);
	}
	return 0;
}