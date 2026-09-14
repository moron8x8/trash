#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int giverandnum(int start, int stop){
    int num = rand() % (stop - start + 1) + start;
    return num;
}

int main(void){
    srand(time(NULL));
    int start, stop;
    printf("Game guess the number\n");
    printf("Start: ");
    if(scanf("%d", &start) != 1) return 0;
    printf("Stop: ");
    if(scanf("%d", &stop) != 1 || start > stop) return 0;
    int ans = giverandnum(start, stop);
    int n = 0;
    while(n != ans){
        printf("Print num: ");
        if(scanf("%d", &n) != 1) return 0;
        if(n > ans) printf("Lower!\n");
        else if(n < ans) printf("Bigger!\n");
        else printf("Correct!\n");
    }
    return 0;
}