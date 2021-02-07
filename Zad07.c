#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUFFER_LENGTH 1024

struct _node;
typedef struct _node Node;
typedef Node* Position;

struct _node {
	int El;
	Position Next;
};

Position CreateNode(Position);
int Push(Position, int);
int Pop(Position, int*); 
int Calculator(int, int, char, int*);
int CalculatePostfix(char*, Position);
int Print(Position);

int main()
{
	char filename[50];
	Node head;
	head.Next = NULL;
	int provjera = 0;

	printf("\nUnesite ime datoteke iz koje zelite citati: ");
	scanf(" %s", filename);
	
	if (CalculatePostfix(filename, &head) == -1)
		return -1;
	
	printf("\nRezultat je: ");
	Print(head.Next);

	return 0;
}

Position CreateNode(Position p)
{
	p = NULL;
	p = (Position)malloc(sizeof(Node));

	if (p == NULL) {
		printf("\nGreska pri alocrianju memorije");
		return -1;
	}

	p->Next = NULL;

	return p;
}

int Push(Position p, int x)
{
	Position q = NULL;

	q = CreateNode(q);

	q->El = x;
	q->Next = p->Next;
	p->Next = q;

	return 0;
}

int Pop(Position p, int* x)
{
	Position temp = NULL;

	if (p->Next == NULL) {
		printf("\nStog je prazan!");
		return -1;
	}

	temp = p->Next;
	if (temp == NULL)
		return -1;

	p->Next = temp->Next;
	*x = temp->El;

	free(temp);
	return 0;
}

int Calculator(int x, int y , char operation, int* result)
{
	switch (operation)
	{
	case '+':
		*result = x + y;
		break;
	case '-':
		*result = x - y;
		break;
	case '*':
		*result = x * y;
		break;
	case '/':
		if (y == 0) {
			printf("\nDjeljenje s 0 nije moguce!");
			return -1;
		}
		*result = x / y;
		break;
	default:
		printf("\nOperacija nije prepoznata!");
		return -1;
		break;
	}

	return 0;
}

int CalculatePostfix(char* filename, Position p)
{
	char* buffer = NULL;
	FILE* fPointer = NULL;
	int x = 0;
	int y = 0;
	int result = 0;
	
	buffer = (char*)malloc(BUFFER_LENGTH * sizeof(char));
	if (buffer == NULL) {
		printf("\nGreska pri alociranju buffera!");
		return -1;
	}
	memset(buffer, '\0', BUFFER_LENGTH);

	fPointer = fopen(filename, "r");
	if (fPointer == NULL) {
		printf("\nGreska pri otvaranju datoteke!");
		return -1;
	}
	
	while (!feof(fPointer))
	{
		memset(buffer, 0, BUFFER_LENGTH);
		fscanf(fPointer, " %s", buffer);
		
		if (isdigit(buffer[0])) {
			sscanf(buffer, " %d", &x);
			Push(p, x);
			printf("\nUnosimo %d", x);
		}
		else {
			Pop(p, &x);
			Pop(p, &y);
			Calculator(x, y, buffer[0], &result);
			printf("\nMedurezultat je: %d", result);
			Push(p, result);
		}
	}

	fclose(fPointer);
	free(buffer);

	return 0;
}

int Print(Position p) {
	while (p != NULL) {
		printf(" %d", p->El);
		p = p->Next;
	}

	return 0;
}