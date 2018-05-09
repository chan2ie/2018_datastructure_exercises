#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 24
#define FALSE 0
#define TRUE 1
#define MALLOC(x, y) x=(struct node *)malloc(y)

typedef struct node* nodePointer;
typedef struct node {
	int data;
	nodePointer link;
} Node;

void push(nodePointer* top, int value)
{
	nodePointer new, temp = *top;
	new = malloc(sizeof(Node));

	new->data = value;
	new->link = (*top)->link;
	(*top)->link = new;
}
int pop(nodePointer* top)
{
	int value;
	nodePointer temp;

	temp = (*top)->link;

	(*top)->link = (*top)->link->link;
	value = temp->data;
	free(temp);

	return value;
}

void main(void)
{
	short int out[MAX_SIZE];
	nodePointer seq[MAX_SIZE];
	nodePointer x, y, top;

	int size, num1, num2;

	FILE *fp;

	fp = fopen("input.txt", "r");

	fscanf(fp, "%d", &size);

	for (int i = 0; i < size; i++) {
		out[i] = FALSE;
		seq[i] = malloc(sizeof(Node));
		seq[i]->link = NULL;
	}

	while (1) {
		fscanf(fp, "%d %d", &num1, &num2);

		if (num1 == -1 && num2 == -1) {
			break;
		}

		push(&(seq[num1]), num2);
		push(&(seq[num2]), num1);
	}

	fclose(fp);

	top = malloc(sizeof(Node));
	top->link = NULL;

	for (int i = 0; i < size; i++) {
		if (out[i] == TRUE) {
			continue;
		}
		out[i] = TRUE;
		printf("New class :\t%d", i);

		x = seq[i];

		while (1) {
			if (x->link != NULL) {
				x = x->link;
				if (out[x->data] == FALSE) {
					printf("\t%d", x->data);
					push(&top, x->data);
					out[x->data] = TRUE;
				}
			}
			else {
				x = seq[pop(&top)];
			}
			if (top->link == NULL && x->link == NULL) {
				break;
			}
		}
		printf("\n");
	}

	free(top);

	for (int i = 0; i < size; i++) {
		free(seq[i]);
	}


	return;
}
