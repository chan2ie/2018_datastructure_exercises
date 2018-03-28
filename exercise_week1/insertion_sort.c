#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    time_t start=0, end=0;

    FILE *fp = fopen("lab1.data","r");
    
    int datasize;

    start = clock();

    fscanf(fp,"%d",&datasize);

    int *sorted, *unsorted;

    unsorted = malloc(datasize*sizeof(int));
    sorted = malloc(datasize*sizeof(int));
    
    printf("Input : ");

    for(int i = 0; i < datasize; i++){
        int temp;
        fscanf(fp,"%d",&(unsorted[i]));

        printf("%d ", unsorted[i]);
    }

    printf("\n");

    for(int i = 0; i < datasize; i++){
        int j;

        for(j = 0; j < i; j++){
            if(sorted[j] > unsorted[i]){
                break;
            }
        }

        if(i != j){
            for(int k = i-1; k > j - 1; k--){
                sorted[k + 1] = sorted[k];
            }
        }

        sorted[j] = unsorted[i];
    }

    printf("Sorted : ");

    for(int i = 0; i < datasize; i++){
        printf("%d ", sorted[i]);
    }

    printf("\n");

    free(unsorted);
    free(sorted);
    fclose(fp);

    end = clock();

    printf("%lf\n", ((double)end - (double)start)/CLOCKS_PER_SEC);
    
    return 0;
}
