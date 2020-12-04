#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct _node;
typedef struct _node Node;
typedef Node* Position;

struct _node{
	int coefficijent;
	int exponent;
	Position Next;
};

Position CreateNode(Position);
int ReadFromFile(char*, Position);
int PrintList(Position);
int AddPolynoms(Position, Position, Position);
int MulPolynoms(Position, Position, Position);

int main()
{
	char filename[50];
	Node head1, head2, head3, head4;

	head1.Next = NULL;
	head2.Next = NULL;
	head3.Next = NULL;
	head4.Next = NULL;

	printf("\nUnesite ime datoteke iz koje zelite ucitati prvi polinom: ");
	scanf(" %s", filename);
	ReadFromFile(filename, &head1);
	printf("\nUnesite ime datoteke iz koje zelite ucitati drugi polinom: ");
	scanf(" %s", filename);
	ReadFromFile(filename, &head2);
	
	printf("\nPolinom 1 = ");
	PrintList(head1.Next);
	printf("\nPolinom 2 = ");
	PrintList(head2.Next);

	printf("\nSuma polinoma = ");
	AddPolynoms(head1.Next, head2.Next, &head3);
	PrintList(head3.Next);

	printf("\nUmnozak polinoma = ");
	MulPolynoms(head1.Next, head2.Next, &head4);
	PrintList(head4.Next);

	return 0;
}

Position CreateNode(Position p)//Prominit da bude Position p jer ne znam smiju li se funckije bez argumenta
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
	FILE *fPointer = NULL;
	Position q, temp, prev;
	
	fPointer = fopen(filename, "r");
	if (fPointer == NULL) {
		printf("Greska pri otvaranju datoteke!");
		return -1;
	}
	
	while (!feof(fPointer))
	{
		q = CreateNode(p);
		fscanf(" %d %d", q->coefficijent, q->exponent);
		temp = p->Next;
		prev = p;

		while (temp != NULL && temp->exponent > q->exponent) {
			q->Next = temp;
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

int PrintList(Position P)
{
	while (P != NULL)
	{
		if (P->coefficijent > 0)
			printf(" +%dx^%d", P->coefficijent, P->exponent);
		else
			printf(" %dx^%d", P->coefficijent, P->exponent);
		P = P->Next;
	}

	return 0;
}

int AddPolynoms(Position P1, Position P2, Position S)
{
	Position q = NULL;
	Position temp = NULL;

	while (P1 != NULL && P2 != NULL)
	{
		q = CreateNode(S);
		
		if (P1->exponent > P2->exponent)
		{
			q->exponent = P1->exponent;
			q->coefficijent = P1->coefficijent;
			P1 = P1->Next;
		}
		else if (P1->exponent < P2->exponent)
		{
			q->exponent = P2->exponent;
			q->coefficijent = P2->coefficijent;
			P2 = P2->Next;
		}
		else
		{
			q->exponent = P1->exponent;
			q->coefficijent = P1->coefficijent + P2->coefficijent;
			P1 = P1->Next;
			P2 = P2->Next;
		}

		q->Next = S->Next;
		S->Next = q;

		S = q;
	}

	if (P1 == NULL)
		temp = P2;
	else
		temp = P1;

	while (temp != NULL)
	{
		q = CreateNode(S);

		q->exponent = temp->exponent;
		q->coefficijent = temp->coefficijent;

		q->Next = S->Next;
		S->Next = q;

		S = q;

		temp = temp->Next;
	}

	return 0;
}

int MulPolynoms(Position P1, Position P2, Position M)
{
	Position q = NULL; 
	Position  temp = NULL;

	while (P1 != NULL)
	{
		while (P2 != NULL)
		{
			q = CreateNode(M);

			q->exponent = P1->exponent + P2->exponent;
			q->coefficijent = P1->coefficijent * P2->coefficijent;

			temp = M;

			while (temp->Next != NULL && temp->Next->exponent > q->exponent)
				temp = temp->Next;

			if (temp->Next != NULL && temp->Next->exponent == q->exponent)
			{
				temp->Next->coefficijent += q->coefficijent;
				free(q);

				if (temp->Next->coefficijent == 0)
				{
					q = temp->Next;
					temp->Next = q->Next;

					free(q);
				}
			}
			else
			{
				q->Next = temp->Next;
				temp->Next = q;
			}

			P2 = P2->Next;
		}
		P1 = P1->Next;
	}

	return 0;
}