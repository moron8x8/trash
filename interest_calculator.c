#include <stdio.h>

double power(double num, int exp){
    double res = 1.0;
    while(exp > 0){
        res *= num;
        exp--;
    }
    return res;
}

int main(void){
    double R, CI, P, T;
    if(scanf("%lf", &P) != 1 || P <= 0) return 0;
    if(scanf("%lf", &R) != 1 || R <= 0) return 0;
    if(scanf("%lf", &T) != 1 || T <= 0) return 0;
    double procent = 1 + (R / 100);

    CI = P * (power(procent, T));
    printf("%.2f\n", CI);

    return 0;
}