#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUFFER_LENGTH 1024

struct tree;
typedef struct tree Tree;
typedef Tree* TPosition;

struct tree {
	char* El;
	TPosition Left;
	TPosition Right;
};

struct stack;
typedef struct stack Stack;
typedef Stack* SPosition;

struct stack{
	TPosition El;
	SPosition Next;
};

int CreateNodeT(TPosition*);
int CreateNodeS(SPosition*);
TPosition ReadFromFile(char*, TPosition, SPosition);
int Push(TPosition, SPosition);
TPosition Pop(SPosition);
int PrintInOrder(TPosition);
int DeleteTree(TPosition);
int DeleteStack(SPosition);

int main()
{
	TPosition root = NULL;
	SPosition head = NULL;
	char* filename = NULL;

	CreateNodeS(&head);

	filename = (char*)malloc(sizeof(char) * BUFFER_LENGTH);
	if (filename == NULL) {
		printf("\"filename\" memory allocation error!");
		return -1;
	}
	memset(filename, '\0', BUFFER_LENGTH);

	printf("Enter name of file to read: ");
	scanf("%s", filename);
	
	root = ReadFromFile(filename, root, head);
	
	PrintInOrder(root);

	int DeleteStack(head);
	int DeleteTree(root);

	return 0;
}

int CreateNodeS(SPosition* S)
{
	SPosition q = NULL;
	q = (SPosition)malloc(sizeof(Stack));

	if (NULL == q) {
		printf("Memory allocation error!");
		return -1;
	}

	q->El = NULL;
	q->Next = NULL;

	*S = q;

	return 0;
}

int CreateNodeT(TPosition* T)
{
	TPosition q = NULL;
	q = (TPosition)malloc(sizeof(Tree));

	if (NULL == q) {
		printf("Memory allocation error!");
		return -1;
	}

	q->El = NULL;
	q->Left = NULL;
	q->Right = NULL;

	*T = q;

	return 0;
}

TPosition ReadFromFile(char* filename, TPosition T, SPosition S)
{
	FILE* fPointer = NULL;
	char* buffer = NULL;
	int number = 0;
	int SizeOfBuffer = 0;
	int n = 0;
	TPosition q = NULL;

	buffer = (char*)malloc(sizeof(char) * BUFFER_LENGTH);
	if (buffer == NULL) {
		printf("Memory allocation error!");
		return NULL;
	}
	memset(buffer, '\0', BUFFER_LENGTH);

	fPointer = fopen(filename, "r");
	if (fPointer == NULL) {
		printf("File could not be opened!");
		return NULL;
	}
	
	while(!feof(fPointer)) {
		memset(buffer, '\0', BUFFER_LENGTH);

		CreateNodeT(&q);

		fscanf(fPointer, " %s", buffer);

		if (buffer != NULL || strlen(buffer) != NULL) {
			SizeOfBuffer = strlen(buffer);
			SizeOfBuffer++;

			q->El = (char*)malloc(sizeof(char) * SizeOfBuffer);
			if (q->El == NULL)
			{
				printf("Memory allocation error!");
				free(q);
				break;
			}
			
			memset(q->El, '\0', SizeOfBuffer);
			SizeOfBuffer--;

			strncpy(q->El, buffer, SizeOfBuffer);
			q->Left = NULL;
			q->Right = NULL;
			
			n = sscanf(buffer, " %d", &number);

			if (n == EOF || n <= 0) {
				q->Right = Pop(S);
				q->Left = Pop(S);
			}
			
			Push(q, S);
		}
	}
	fclose(fPointer);
	free(buffer);
	T = Pop(S);

	return T;
}

int Push(TPosition T, SPosition S)
{
	SPosition q = NULL;
	CreateNodeS(&q);

	q->El = T;
	q->Next = S->Next;
	S->Next = q;

	return 0;
}

TPosition Pop(SPosition S)	//provjeri
{
	SPosition temp = NULL;
	TPosition q = NULL;

	if (S == NULL) {
		printf("\nStack is empty!\n");
		return NULL;
	}

	temp = S->Next;
	S->Next = temp->Next;
	q = temp->El;
	free(temp);

	return q;
}

int PrintInOrder(TPosition T)
{
	if (T != NULL) {
		if (T->Left != NULL)
			printf(" (");

		PrintInOrder(T->Left);
		printf(" %s ", T->El);
		PrintInOrder(T->Right);

		if (T->Right != NULL)
			printf(") ");
	}

	return 0;
}

int DeleteTree(TPosition T)
{
	if (NULL == T)
		return 0;

	DeleteTree(T->Left);
	DeleteTree(T->Right);
	free(T);

	return 0;
}

int DeleteStack(SPosition S)
{
	if (NULL == S)
		return 0;

	DeleteStack(S->El);
	DeleteStack(S->Next);
	free(S);

	return 0;
}