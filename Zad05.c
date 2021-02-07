#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct _node;
typedef struct _node Node;
typedef Node* Position;
struct _node
{
	int el;
	Position Next;
};

Position CreateNode(Position);
int ReadFromFile(char*, Position);
int PrintList(Position);
int Intersection(Position, Position, Position);
int Union(Position, Position, Position);

int main()
{
	char filename[50];
	Node headL1, headL2, headI, headU;
	
	headL1.Next = NULL;
	headL2.Next = NULL;
	headI.Next = NULL;
	headU.Next = NULL;

	printf("\nUnesite ime datoteke iz koje zelite ucitati prvu listu: ");
	scanf(" %s", filename);
	if (ReadFromFile(filename, &headL1) == -1)
		return -1;

	printf("\nUnesite ime datoteke iz koje zelite ucitati drugu listu: ");
	scanf(" %s", filename);
	if (ReadFromFile(filename, &headL2) == -1)
		return -1;

	printf("\nLista 1 = ");
	PrintList(headL1.Next);

	printf("\nLista 2 = ");
	PrintList(headL2.Next);

	printf("\nPresjek lista = ");
	Intersection(&headL1, &headL2, &headI);
	PrintList(headI.Next);

	printf("\nUnija lista = ");
	Intersection(&headL1, &headL2, &headU);
	PrintList(headU.Next);

	return 0;
}

Position CreateNode(Position p)
{
	Position q = NULL;
	q = (Position)malloc(sizeof(Node));

	if (q == NULL) {
		printf("Greska pri alocrianju memorije\n");
		return -1;
	}
	
	q->Next = NULL;

	return q;
}

int ReadFromFile(char* filename, Position p)
{
	FILE* fPointer = NULL;
	Position q, temp, prev;

	fPointer = fopen(filename, "r");
	if (fPointer == NULL) {
		printf("Greska pri otvaranju datoteke!");
		return -1;
	}

	while (!feof(fPointer))
	{
		q = CreateNode(p);
		fscanf(fPointer, " %d", q->el);
		temp = p->Next;
		prev = p;

		while (temp != NULL && temp->el > q->el) {
			prev = temp;
			temp = temp->Next;
		}

		prev->Next = q;

		if (temp != NULL)
			q->Next = temp;
		else
			q->Next = NULL;
	}
	fclose(fPointer);

	return 0;
}

int PrintList(Position p)
{
	while (p != NULL) {
		printf(" %d", p->el);
		p = p->Next;
	}

	return 0;
}

int Intersection(Position L1, Position L2, Position I)
{
	Position q;

	while (L1 != NULL && L2 != NULL) {
		if (L1->el > L2->el)
			L1 = L1->Next;
		else if (L1->el < L2->Next)
			L2 = L2->Next;
		else {
			q = CreateNode(I);
			q->el = L1->el;
			q->Next = I->Next;
			I->Next = q;
			I = q;

			L1 = L1->Next;
			L2 = L2->Next;
		}
	}

	return 0;
}

int Union(Position L1, Position L2, Position U)
{
	Position q;
	Position temp;

	while (L1 != NULL && L2 != NULL) //L1 && L2
	{
		q = CreateNode(U);

		if (L1->el > L2->el) {
			q->el = L1->el;
			L1 = L1->Next;
		}
		else if (L1->el < L2->el) {
			q->el = L2->el;
			L2 = L2->Next;
		}
		else {
			q->el = L1->el;
			L1 = L1->Next;
			L2 = L2->Next;
		}

		if (U->el == q->el)
			free(q);
		else {
			q->Next = U->Next;
			U->Next = q;
			U = q;
		}
	}
	if (L1 == NULL)
		temp = L2;
	else
		temp = L1;

	while (temp != NULL) {
		q = CreateNode(U);

		q->el = temp->el;
		if (U->el == q->el)
			free(q);
		else {
			q->Next = U->Next;
			U->Next = q;
			U = q;
		}
		temp = temp->Next;
	}

	return 0;
}