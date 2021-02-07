#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUFFER_LENGTH 1024
#define TABLE_SIZE 11

struct node;
typedef struct node Node;
typedef Node* NPosition;

struct node
{
	char* ime;
	char* prezime;
	int mb;
	NPosition next;
};

struct hash;
typedef struct hash Hash;
typedef Hash* HPosition;

struct hash
{
	int index;
	NPosition node;
};

int InitializeHashTable(HPosition*);
int CreateNode(NPosition*);
int ReadFromFile(HPosition, char*);
int Key(char*);
int InsertHash(HPosition, NPosition);
NPosition InsertNode(NPosition, NPosition); //??
int PrintHash(HPosition);
int PrintNode(NPosition);
int FindHash(char*, char *, HPosition);
int FindNode(NPosition, char*, char*);

int main()
{
	HPosition ht = NULL;
	char* filename = NULL;
	char* buffer = NULL;
	char ime[256];
	char prezime[256];

	buffer = (char*)malloc(sizeof(char) * BUFFER_LENGTH);
	if (buffer == NULL) {
		printf("Memory allocation failed!");
		return -1;
	}
	memset(buffer, '\0', BUFFER_LENGTH);

	filename = (char*)malloc(sizeof(char) * BUFFER_LENGTH);
	if (filename == NULL)
	{
		printf("Memory allocation error -> filename");
		return -1;
	}
	memset(filename, '\0', BUFFER_LENGTH);

	printf("Enter name of file to read: ");
	scanf(" %s", filename);

	if (strchr(filename, '.') == NULL)
		strcat(filename, ".txt");

	InitializeHashTable(&ht);
	
	ReadFromFile(ht, filename);
	
	PrintHash(ht);

	printf("\nEnter first and last name: ");
	scanf(" %[^\t\n]", buffer);
	sscanf(buffer, "%s %s", ime, prezime);
	
	FindHash(ime, prezime, ht);

	return 0;
}

int InitializeHashTable(HPosition* H)
{
	int i;
	HPosition q = NULL;

	q = (HPosition)malloc(sizeof(Hash) * TABLE_SIZE);
	if (NULL == q) {
		printf("Memory allocation failed!");
		return -1;
	}

	for (int i = 0; i < TABLE_SIZE; i++) {
		q[i].index = i;
		q[i].node = NULL;
	}

	*H = q;
	return 0;
}

int CreateNode(NPosition* N)
{
	NPosition q = NULL;

	q = (NPosition)malloc(sizeof(Node));
	if (q == NULL) {
		printf("Memory allocation failed!");
		return NULL;
	}

	q->ime = (char*)malloc(sizeof(char) * BUFFER_LENGTH);
	if (q->ime == NULL) {
		printf("Memory allocation failed!");
		return NULL;
	}

	q->prezime = (char*)malloc(sizeof(char) * BUFFER_LENGTH);
	if (q->prezime == NULL) {
		printf("Memory allocation failed!");
		return NULL;
	}

	q->mb = 0;
	q->next = NULL;

	*N = q;

	return 0;
}

int ReadFromFile(HPosition H, char* filename)
{
	FILE* fPointer = NULL;
	char* ime = NULL;
	char* prezime = NULL;
	char* buffer = NULL;
	int mb = 0;
	NPosition N = NULL;

	buffer = (char*)malloc(sizeof(char) * BUFFER_LENGTH);
	if (buffer == NULL)
	{
		printf("Memory allocation error -> buffer");
		return -1;
	}

	ime = (char*)malloc(sizeof(char) * BUFFER_LENGTH);
	if (ime == NULL)
	{
		printf("Memory allocation error -> buffer");
		return -1;
	}

	prezime = (char*)malloc(sizeof(char) * BUFFER_LENGTH);
	if (prezime == NULL)
	{
		printf("Memory allocation error -> buffer");
		return -1;
	}
	
	fPointer = fopen(filename, "r");
	if (fPointer == NULL) {
		printf("File could not be opened!");
		return -1;
	}

	while (!feof(fPointer))
	{
		memset(buffer, '\0', BUFFER_LENGTH);

		fscanf(fPointer, " %[^\t\n]", buffer);
		if (buffer == NULL || strlen(buffer) == 0)
			continue;

		//fscanf(fPointer, "%s %s %d", ime, prezime, &mb); ZAMJENA

		CreateNode(&N);
		
		sscanf(buffer, "%s %s %d", ime, prezime, &mb);
	
		strcpy(N->ime, ime);
		strcpy(N->prezime, prezime);
		N->mb = mb;

		InsertHash(H, N); 
	}

	free(buffer);
	free(filename);
	fclose(fPointer);

	return 0;
}

int Key(char* prezime)
{
	int i = 0;
	int sum = 0;

	while (prezime[i] != '\0' || i < 5)
	{
		sum += (int)prezime[i];
		i++;
	}
	
	return sum % TABLE_SIZE;
}

int InsertHash(HPosition H, NPosition N)
{
	int k = 0;

	k = Key(N->prezime);
	
	H[k].node = InsertNode(H[k].node, N);
	
	return 0;
}

NPosition InsertNode(NPosition p, NPosition q) //pojednostavi
{
	NPosition temp = NULL;
	
	temp = p;
	
	if (temp == NULL)
		return q;

	if (strcmp(temp->prezime, q->prezime) < 0) {
		q->next = temp;
		return q;
	}
	
	while (temp->next != NULL && strcmp(temp->prezime, q->prezime) > 0)
		temp = temp->next;

	if (temp->next == NULL) {
		q->next = temp->next;
		temp->next = q;

		return p;
	}

	if (strcmp(temp->prezime, p->prezime) == 0) {
		if (strcmp(temp->ime, q->ime) < 0) {
			q->next = temp->next;
			temp->next = q;

			return p;
		}

		while (temp->next != NULL && strcmp(temp->ime, q->ime) > 0)
			temp = temp->next;

		if (temp->next == NULL) {
			q->next = temp->next;
			temp->next = q;

			return p;
		}

		if (strcmp(temp->ime, q->ime) == 0)
			while (temp->next != NULL && temp->mb < q->mb)
				temp = temp->next;
	}

	q->next = temp->next;
	temp->next = q;

	return p;
}

int PrintHash(HPosition H)
{
	int i;

	for (i = 0; i < TABLE_SIZE; i++)
	{
		printf("Key = %d:\n", H[i].index);
		PrintNode(H[i].node);
	}

	return 0;
}

int PrintNode(NPosition N)
{
	while (N != NULL)
	{
		printf("\t%s %s\n", N->prezime, N->ime);
		N = N->next;
	}

	return 0;
}

int FindHash(char* ime, char* prezime, HPosition H)
{
	int k = 0;

	k = Key(prezime);

	FindNode(H[k].node, ime, prezime);

	printf("\tKey = %d\n", k);

	return 0;
}

int FindNode(NPosition N, char* ime, char* prezime)
{
	while (strcmp(N->prezime, prezime) != 0 && N != NULL)
		N = N->next;

	while (strcmp(N->ime, ime) != 0 && N != NULL)
		N = N->next;

	if (N == NULL) {
		printf("No person with this last name");
		return -1;
	}

	printf("\t%s %s %d", N->ime, N->prezime, N->mb);

	return 0;
}