#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct stablo;
typedef struct stablo Stablo;
typedef Stablo *Position;

struct stablo
{
	int El;
	Position Left;
	Position Right;
};

Position CreateNode(int);
Position Insert(Position, int);
Position Find(Position, int);
Position Delete(Position, int);
Position FindMin(Position);
Position FindMax(Position);
int PrintInOrder(Position);

int main()
{
	Position root = NULL;
	Position temp;
	char c = 0;
	int n;

	while (c != 'k' && c != 'K') {
		printf("\nEnter your selection:\t\n1 - Enter an element in the tree\n\t2 - Delete element\n\t3 - Find element\n\t4 - Print tree\n");
		scanf(" %c", &c);

		switch (c)
		{
		case '1':
			printf("Enter element:\n");
			scanf("%d", &n);
			root = Insert(root, n);
			break;

		case '2':
			printf("Enter the element you want to delete from the tree:\n");
			scanf("%d", &n);
			root = Delete(root, n);
			break;
		case '3':

			printf("What element do you want to find?\n");
			scanf("%d", &n);
			temp = Find(root, n);
			if (temp != NULL)
				printf("The required element %D is in the tree!\n", temp->El);
			break;

		case '4':
			PrintInOrder(root);
			break;
		}
	}

	return 0;
}

Position CreateNode(int n)
{
	Position p = NULL;

	p = (Position)malloc(sizeof(Stablo));
	if (p == NULL)
	{
		printf("Memory allocation failed!");
		return NULL;
	}

	p->El = n;
	p->Left = NULL;
	p->Right = NULL;

	return p;
}

Position Insert(Position p, int n)
{
	if (NULL == p)
		p = CreateNode(n);

	else if (p->El > n)
		p->Left = Insert(p->Left, n);

	else if (p->El < n)
		p->Right = Insert(p->Right, n);

	else
		printf("\nThis element already exists!\n");

	return p;
}

Position Find(Position p, int n)
{
	if (NULL == p) {
		printf("\nElement doesn't exist!\n");
		return NULL;
	}

	else if (p->El > n)
		return Find(p->Left, n);

	else if (p->El < n)
		return Find(p->Right, n);

	else
		return p;
}

Position Delete(Position p, int n)
{
	Position temp;

	if (NULL == p) {
		printf("\nElement doesn't exist!\n");
		return NULL;
	}

	else if (p->El > n)
		p->Left = Delete(p->Left, n);

	else if (p->El < n)
		p->Right = Delete(p->Right, n);

	else {
		if (p->Left != NULL && p->Right != NULL) {
			// Min from Right subtree
			temp = FindMin(p->Left);
			p->El = temp->El;
			p->Right = Delete(p->Right, temp->El);
			/* or Max from Left subtree
			tmp = FindMax(P->Right);
			P->El = tmp->El;
			P->Left = Delete(P->Left, tmp->El);
			*/
		}

		else {
			temp = p;
			if (p->Left == NULL)
				p = p->Right;
			else
				p = p->Left;

			free(temp);
		}
	}

	return p;
}

Position FindMin(Position p)
{
	if (p != NULL) {
		while (p->Left != NULL)
			p = p->Left;
	}
	/* recursive
	if (p != NULL && p->Left != NULL)
		return FIndMin(p->Left);*/

	return p;
}

Position FindMax(Position p)
{
	if (p != NULL) {
		while (p->Right != NULL)
			p = p->Right;
	}
	/* recursive
	if (p != NULL && p->Right != NULL)
		return FIndMin(p->Right);*/

	return p;
}

int PrintInOrder(Position p)
{
	if (p != NULL) {
		PrintInOrder(p->Left);
		printf("%d\t", p->El);
		PrintInOrder(p->Right);
	}

	/*preorder
	printf("%d\t", p->El);
	PrintInOrder(p->Left);
	PrintInOrder(p->Right);*/

	/*postorder
	PrintInOrder(p->Left);
	PrintInOrder(p->Right);
	printf("%d\t", p->El);
	*/

	return 0;
}