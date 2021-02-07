#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct _node;
typedef struct _node Node;
typedef Node* Position;

struct _node {
	int El;
	Position Next;
};

int PushStog(Position);
int PushRed(Position);
int Pop(Position);
int Print(Position);

int main()
{
	Node headS, headR;
	char izbor = 0;

	srand((unsigned)time(NULL));

	headS.Next = NULL;
	headR.Next = NULL;

	while (izbor != 'K' && izbor != 'k') {
		printf("\n\t0 - Push Stog");
		printf("\n\t1 - Pop Stog");
		printf("\n\t2 - Push Red");
		printf("\n\t3 - Pop Red");
		printf("\n\tk - kraj\n");
		printf("\nUnesi: ");
		scanf(" %c", &izbor);

		switch (izbor)
		{
		case '0':
			PushStog(&headS);
			Print(headS.Next);
			break;
		case '1':
			Pop(&headS);
			Print(headS.Next);
			break;
		case '2':
			PushRed(&headR);
			Print(headR.Next);
			break;
		case '3':
			Pop(&headR);
			Print(headR.Next);
			break;
		}
	}

	return 0;
}

int PushStog(Position p)
{
	Position q = NULL;
	int min = 10;
	int max = 100;
	int RandBr = rand() % (max - min) + min;

	q = (Position)malloc(sizeof(Node));
	if (q == NULL) {
		printf("Greska pri alocrianju memorije\n");
		return -1;
	}
	q->Next = NULL;

	q->El = RandBr;
	q->Next = p->Next;
	p->Next = q;

	return 0;
}

int PushRed(Position p)
{
	static Position last;
	Position q = NULL;
	int min = 10;
	int max = 100;
	int RandBr = rand() % (max - min) + min;
	
	if (p->Next == NULL)
		last = p;
	
	q = (Position)malloc(sizeof(Node));
	if (q == NULL) {
		printf("Greska pri alocrianju memorije\n");
		return -1;
	}
	q->Next = NULL;
	
	q->El = RandBr;
	q->Next = last->Next;
	last->Next = q;
	
	last = q;
	
	return 0;
}

int Pop(Position p)
{
	Position temp = NULL;

	if (p->Next == NULL) {
		printf("\nStog je prazan!");
		return -1;
	}

	temp = p->Next;
	p->Next = temp->Next;
	printf("\nBrise se : %d", temp->El);

	free(temp);
}

int Print(Position p)
{
	if (p == NULL) {
		printf("\nStog je prazan!");
		return -1;
	}

	printf("\nU stogu se nalaze: ");

	while (p != NULL) {
		printf(" %d", p->El);
		p = p->Next;
	}

	return 0;
}