#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 50

typedef enum { head, entry } tagfield;
typedef struct matrix_node *matrix_pointer;
typedef struct entry_node {
	int row;
	int col;
	int value;
} entry_node;
typedef struct matrix_node {
	matrix_pointer down;
	matrix_pointer right;
	tagfield tag;
	union {
		matrix_pointer next;
		struct entry_node entry;
	} u;
} matrix_node;

matrix_pointer hdnode[MAX_SIZE];

matrix_pointer new_node();
matrix_pointer mread(FILE*); // file ���� matrix �ڷḦ �о� ����Ʈ�� �����Ѵ�.
void mwrite(matrix_pointer); // ����� ������ ���� (2���� �������)���� ����Ѵ�.
void merase(matrix_pointer*); // NULL parameter �� ��� ������ ó��.

int maximum(int num1, int num2) {
	if (num1 > num2) {
		return num1;
	}
	return num2;
}

int main() {

	matrix_pointer a, b;
	FILE *fp_A, *fp_B;

	fp_A = fopen("A.txt", "r");
	fp_B = fopen("B.txt", "r");
	a = mread(fp_A);
	b = mread(fp_B);
	mwrite(a);
	mwrite(b);
	merase(&a);
	merase(&b);
	mwrite(a);
	mwrite(b);

	fclose(fp_A);
	fclose(fp_B);

	return 0;
}

matrix_pointer mread(FILE* fp) {
	matrix_node *node, *last;

	int row, col, value, current_row;

	fscanf(fp, "%d %d", &row, &col);

	node = new_node();
	node->tag = entry;

	node->u.entry.row = row;
	node->u.entry.col = col;

	if (!row && !col) {
		node->right = node;
		return node;
	}

	for (int i = 0; i < maximum(row, col); i++) {
		matrix_pointer temp = new_node();
		hdnode[i] = temp;
		hdnode[i]->tag = head;
		hdnode[i]->right = temp;
		hdnode[i]->u.next = temp;
	}

	current_row = 0; last = hdnode[0];

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			fscanf(fp, "%d", &value);
			if (value == 0) {
				continue;
			}
			else {
				if (i > current_row) {
					last->right = hdnode[current_row];
					current_row = i; last = hdnode[i];
				}
				matrix_pointer temp = new_node();
				temp->tag = entry;
				temp->u.entry.row = i;
				temp->u.entry.col = j;
				temp->u.entry.value = value;
				last->right = temp;
				last = temp;
				hdnode[j]->u.next->down = temp;
				hdnode[j]->u.next = temp;
			}
		}
	}

	last->right = hdnode[current_row];
	for (int i = 0; i < col; i++) {
		hdnode[i]->u.next->down = hdnode[i];
	}
	for (int i = 0; i < maximum(row, col) - 1; i++) {
		hdnode[i]->u.next = hdnode[i + 1];
	}
	hdnode[maximum(row, col) - 1]->u.next = node;
	node->right = hdnode[0];

	return node;
}
void mwrite(matrix_pointer node) {
	matrix_pointer temp, hdnode = node->right;

	for (int i = 0; i < node->u.entry.row; i++){
		temp = hdnode->right;
		for (int j = 0; j < node->u.entry.col; j++) {
			if (temp->u.entry.col == j) {
				printf("%d ", temp->u.entry.value);
				temp = temp->right;
			}
			else {
				printf("0 ");

			}
		}
		hdnode = hdnode->u.next;
		printf("\n");
	}

}

void merase(matrix_pointer *node) {

	int i, num_heads;
	matrix_pointer x, y, head = (*node)->right;

	for (i = 0; i< (*node)->u.entry.row; i++) {
		y = head->right;
		while (y != head) {
			x = y;
			y = y->right;
			free(x);
		}
		x = head;
		head = head->u.next;
		free(x);
	}

	y = head;
	while (y != *node) {
		x = y;
		y = y->u.next;
		free(x);
	}
	free(*node);

}

matrix_pointer new_node() {
	matrix_pointer node = (matrix_pointer)malloc(sizeof(matrix_node));
	if (node == NULL) {
		printf("Could not allocate memory.\n");
		exit(-1);
	}
	return node;
}