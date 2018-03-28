#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 100
#define COMPARE(x,y) (((x)>(y)) ? 1 : (((x) == (y)) ? 0 : -1 ))

typedef struct{
    float coef;
    int expon;
} polynomial;

polynomial terms[MAX_TERMS];

int avail = 0;


void attach(float coefficient, int exponent); 

void padd(int starta, int finisha, int startb, int finishb, int *startd, int *finishd){
   /* add A(x) and B(x) to obtain D(x) */
  float coefficient;
  *startd = avail;
  while (starta <= finisha && startb <= finishb)

    switch (COMPARE(terms[starta].expon, terms[startb].expon)) {

    case -1: /* a expon < b expon */
      attach(terms[startb].coef, terms[startb].expon);
      startb++;
      break;

    case 0: /* equal exponents */
      coefficient = terms[starta].coef + terms[startb].coef;

      if (coefficient){
        attach(coefficient, terms[starta].expon);
      }

        starta++;
        startb++;
        break;

    case 1: /* a expon > b expon */
      attach(terms[starta].coef, terms[starta].expon);
      starta++;
    }

    /* add in remaining terms of A(x) */
    for (; starta <= finisha; starta++){
      attach(terms[starta].coef, terms[starta].expon);
    }

    /* add in remaining terms of B(x) */
    for (; startb <= finishb; startb++){
      attach(terms[startb].coef, terms[startb].expon);
    }

    *finishd =avail-1;
}

void attach(float coefficient, int exponent){ 
    /* add a new term to the polynomial */
	if (avail >= MAX_TERMS){
		fprintf(stderr, "Too many terms in the polynomial");
		exit(1); }
	terms[avail].coef = coefficient;
	terms[avail++].expon = exponent;
}

void readPoly(int *finisha, int *finishb) {
    FILE* file_a= fopen("A.txt","r");
    FILE* file_b= fopen("B.txt","r");
    
    float coefficient;
    int exponent;
    while(1){
        if( fscanf(file_a, "%f%d", &coefficient, &exponent) == EOF ){
            *finisha = avail - 1;
            break;
        }

        attach(coefficient, exponent);
    }
    while(1){
        if( fscanf(file_b, "%f%d", &coefficient, &exponent) == EOF ){
            *finishb = avail - 1;
            break;
        }

        attach(coefficient, exponent);
    }

    fclose(file_a);
    fclose(file_b);

    return;
}

void printPoly(int startd, int finishd) {
    for(int i = startd; i <= finishd; i++){
        if(i != startd){
            printf(", ");
        }
        printf("(%d,%d)", (int)terms[i].coef, terms[i].expon);
    }
    printf("\n");
}

int main () {
    int starta = 0, startb, finisha, finishb, startd, finishd;

    readPoly(&finisha, &finishb);

    startb = finisha + 1;

    padd(starta, finisha, startb, finishb, &startd, &finishd);

    printPoly(startd, finishd);

    return 0;
}
