#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "project.h"
#include <limits.h>
#define MAX_TREE_HT 1000

int main(int argc, char *argv[]){
    char ch,c;
    int index = 0;
    char newstr[MAX_TREE_HT];
    char str2[1024];
    FILE *fp = fopen(argv[1],"r");
    if(!fp){
        return 0;
    }
    //printing the file as well
    while((ch = fgetc(fp))!=EOF) {
        c = putchar(ch);
        newstr[index]=c;
        index++;
    }
    fclose(fp);
    int n = sizeof(newstr) / sizeof(newstr[0]);
    strcpy(str2,newstr);

    int farr[MAX_TREE_HT];
    int i=0;
    int count;
    while(i<strlen(newstr)){
        count = freqinit(newstr,newstr[i]);
        farr[i]=count;
        i++;
    }
    checkInArr(newstr,farr,n);
    removeDuplicate(newstr,n);

    int newlen = strlen(newstr);
    printf("\nThe Final String after Removing All Duplicates = %s\n ", newstr);
    SplayCodes(newstr,str2,farr,newlen-1);
    return 0;
}
