#include <stdio.h>
#include <string.h>

int failure[100];
char string[100];
char pat[100];

void fail(char *pat){
    int n = strlen(pat);
    failure[0] = -1;
    
    for(int j = 1; j < n; j++){
    
        int i = failure[j-1];
        while ((pat[j] != pat[i+1] && (i >= 0))){
            i = failure[i];
        }
        if (pat[j] == pat[i+1]){
            failure[j] = i + 1;
        }
        else failure[j] = -1;
    }
}

int pmatch(char* string, char* pat){
    int i = 0, j = 0;
    int lens = strlen(string);
    int lenp = strlen(pat);

    while (i < lens && j < lenp){
        if(string[i] == pat[j]) {
            i++;
            j++;
        }
        else if (j == 0){
            i++;
        }
        else j = failure[j - 1] + 1;
    }

    return ((j == lenp) ? (i - lenp) : -1);
}

int main (){
	FILE *fp;
	fp = fopen("kmp.txt", "r");

	fscanf(fp, "%s\n%s", string, pat);
	fail(pat);
	printf("%d\n", pmatch(string, pat));
   
    fclose(fp);

    return 0;
}
