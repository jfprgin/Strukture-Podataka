#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct direktorij;
typedef struct direktorij Dir;
typedef Dir* PositionD;

struct direktorij
{
	char name[256];
	PositionD Next;
	PositionD Child;
};

struct stack;
typedef struct stack Stack;
typedef Stack* PositionS;

struct stack
{
	PositionD El;
	PositionS Next;
};

int Push(PositionD, PositionS);
PositionD Pop(PositionS);
int MakeDir(PositionD, char*);
int PrintDir(PositionD, char*);
PositionD EnterDir(PositionD, char*, char*, PositionS);
PositionD ExitDir(PositionD, char*, PositionS);

int main()
{
	char instruction[256];
	char command[10];
	char name[256];
	char path[256];
	char* SpacePosition = NULL;
	char* BreakPosition = NULL;
	Dir root;
	Stack head;

	root.Child = NULL;
	root.Next = NULL;
	head.Next = NULL;

	PositionD UpDir = &root;

	printf("Enter root directory name: ");
	scanf(" %s", root.name);

	root.Child = NULL;
	root.Next = NULL;

	strcpy(path, root.name);;
	strcat(path, ":\\");

	printf("Enter command:");
	printf("\n\t dir");
	printf("\n\t cd..");
	printf("\n\t cd name_dir");
	printf("\n\t md name_dir");
	printf("\n\t exit\n");

	fgets(instruction, 256, stdin);

	while (strcmp(command, "exit") != 0) {
		printf("\n\n%s", path);

		memset(name, '\0', 256);
		memset(name, '\0', 10);

		fgets(instruction, 256, stdin);

		SpacePosition = strchr(instruction, ' ');

		if (SpacePosition == NULL) {
			strcpy(command, instruction);
			BreakPosition = strchr(command, '\n');
			*BreakPosition = 0;
		}
		else {
			strncpy(command, instruction, SpacePosition - instruction);
			command[SpacePosition - instruction] = 0;
			strcpy(name, SpacePosition + 1);
		}

		if (strcmp(command, "dir") == 0)
			PrintDir(UpDir, path);

		else if (strcmp(command, "cd..") == 0)
			UpDir = ExitDir(UpDir, path, &head);

		else if (strcmp(command, "cd") == 0) {
			if (name[0] == 0)
				printf("Command syntax error!\n Should be: cd ime_dir");
			else
				UpDir = EnterDir(UpDir, name, path, &head);
		}

		else if (strcmp(command, "md") == 0) {
			if (name[0] == 0)
				printf("Command syntax error!\n Should be: md ime_dir");
			else
				MakeDir(UpDir, name);

		}

		else if (strcmp(command, "exit") != 0)
			printf("\nWrong input!\n");
	}

	return 0;
}

int PrintDir(PositionD D, char* path)
{
	int i = 0;

	printf("\nDirectory of %s\n", path);

	if (D == NULL) {
		printf("\nNo root directory! ");
		return -1;
	}

	printf("\n");

	D = D->Child;
	while (D) {
		printf("\t%s", D->name);
		D = D->Next;
		i++;
	}

	printf("\n\t%d Dir(s)", i);

	return 0;
}

PositionD ExitDir(PositionD D, char* path, PositionS S)
{
	PositionD temp = NULL;
	char* a;

	temp = Pop(S);
	if (temp == NULL) {
		printf("\nWe are in the root directory!");
		return D;
	}
	else {
		a = strrchr(path, '\\');
		*a = 0;

		a = strrchr(path, '\\');
		*(a + 1) = 0;

		return temp;
	}
}

PositionD EnterDir(PositionD D, char* name, char* path, PositionS S)
{
	PositionD temp = D->Child;
	char* a;
	while (temp != NULL && strcmp(temp->name, name) != 0)
		temp = temp->Next;

	if (temp == NULL) {
		printf("The system cannot find the path specified!");
		return D;
	}
	else {
		Push(S, D);

		strcat(path, temp->name);
		a = strchr(path, '\n');
		*a = '\\';

		return temp;
	}
}

int MakeDir(PositionD D, char* name)
{
	PositionD q = NULL;

	q = (PositionD)malloc(sizeof(Dir));
	q->Child = NULL;
	q->Next = NULL;

	strcpy(q->name, name);

	if (q == NULL) {
		printf("\nMemory allocation error!");
		return -1;
	}
	else {
		if (D->Child == NULL)
			D->Child = q;
		else {
			q->Next = D->Child;
			D->Child = q;
		}
	}

	return 0;
}

int Push(PositionS S, PositionD D)
{
	PositionS q = NULL;

	q = (PositionS)malloc(sizeof(Stack));

	if (q == NULL) {
		printf("\nMemory allocation error!");
		return -1;
	}
	else {
		q->El = D;
		q->Next = S->Next;
		S->Next = q;
	}

	return 0;
}

PositionD Pop(PositionS S)
{
	PositionD q = NULL;
	PositionS temp = NULL;

	if (S->Next == NULL)
		return NULL;
	else {
		q = S->Next->El;
		temp = S->Next;
		S->Next = temp->Next;

		free(temp);
		return q;
	}
}