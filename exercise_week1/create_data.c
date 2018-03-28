#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *fp;
    int num;

    srand(time(NULL));
    
    fp = fopen("lab1.data", "w");

    printf("input : ");
    scanf("%d", &num);

    fprintf(fp,"%d\n", num);

    for(int i = 0; i < num; i++){
        fprintf(fp,"%d\n", rand());
    }

    fclose(fp);
}
