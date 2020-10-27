#include<stdio.h>

typedef struct _student {
	char ime[20];
	char prezime[20];
	int bodovi;
}Student;
int main()
{
	Student *q;
	FILE * fPointer;
	int max_bodovi = 200;
	int i=0;
	fPointer = fopen("student.txt", "r");
	if (fPointer == NULL) {
		printf("Greska pri otvaranju\n");
		return -1;
	}
	while (!feof(fPointer)) {
		q = (Student*)malloc(sizeof(Student));
		fscanf(fPointer, "%s %s %d", &q->ime, &q->prezime, &q->bodovi);
		printf("%s %s %d %f\n", q->ime, q->prezime, q->bodovi, (float)q->bodovi / max_bodovi * 100);
		i++;
	}
	printf("Broj redaka: %d", i);
	fclose(fPointer);
return 0;
}