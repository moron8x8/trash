#include <stdio.h>

int tPasc(int n, int k){
    if (k == 0 || k == n) return 1;
    return tPasc(n - 1, k - 1) + tPasc(n - 1, k);


}

int main(void){

    int row;

    scanf("%d", &row);

    for (int i = 0; i < row + 1; i++){
        int space = row - i;
        for(int s = 0; s < space; s++){
            printf("  ");
        }
        for(int j = 0; j <= i; j++){
            printf("%4d ", tPasc(i, j));
            if (j != 1) printf(" "); 
        }
        printf("\n");
    }

    return 0;

}