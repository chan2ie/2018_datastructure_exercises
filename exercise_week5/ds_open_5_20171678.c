#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPR_SIZE 1000

typedef enum {lparen, rparen, plus, minus, times, divide, mod, eos, operand} precedence;

/* Global Variables */

/* expression */
char expr[MAX_EXPR_SIZE];
/* isp, icp */
static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0};
static int icp[] = {20, 19, 12, 12, 13, 13, 13, 0};

typedef struct _node{
    int data;
    struct _node *link;
}node;
    
node* top = NULL;

/* Functions already implemented by MDH */
void readExpr(FILE* _fp, char* _expr);

/* Functions to be implemented by you */
precedence getToken(char*, int*);
void postfix();
void printToken(precedence );
/* Functions relavant to stack also will be implemented by you. */
precedence pop();
void push(precedence );

int main()
{
	/* Local variables */
	FILE* readfp = fopen("infix.txt","r");

	readExpr(readfp, expr);


    postfix();

	return 0;
}
void readExpr(FILE* _fp, char* _expr)
{

	/* File Existence Check */
	if( !_fp){
		fprintf(stderr, "Input file doesn't exist\n");
		fprintf(stderr, "Program will be shutdown\n");
		exit(0);
	}

	/* Scanning Input */
	fscanf(_fp,"%s",_expr);

	fclose(_fp);
}

void  printToken (precedence symbol){
    switch(symbol) {
        case lparen: return;
        case rparen: return;
        case plus: printf("+"); return;
        case minus: printf("-"); return;
        case divide: printf("/"); return;
        case times: printf("*"); return ;
        case mod: printf("%%"); return ;
    }

}

precedence getToken (char* symbol, int* n){
    *symbol = expr[(*n)++];
    switch(*symbol) {
        case '(': return lparen;
        case ')': return rparen;
        case '+': return plus;
        case '-': return minus;
        case '/': return divide;
        case '*': return times;
        case '%': return mod;
        case '\0': return eos;
        default: return operand;
    }

}

void postfix () {
    char symbol, token;
    int n = 0;
    
    top = malloc(sizeof(node));
    top->data = eos;
    top->link = NULL;

    for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)){
        if(token == operand){
            printf("%c", symbol);
        }
        else if(token == rparen) {
            while(top->data != lparen){
                printToken(pop());
            }
            pop();
        }
        else{
            while(isp[top->data] >= icp[token]){
                printToken(pop());
            }
            push(token);
        }
    }
    while((token = pop()) != eos){
        printToken(token);
    }
    printf("\n");
}

precedence pop() {
    int returnvalue = top->data;
    node *temp = top;

    top = top->link;
    free(temp);

    return returnvalue;
}

void push (precedence token){
    node *newnode = malloc(sizeof(node));

    newnode->data = token;
    newnode->link = top;
    top = newnode;
}

