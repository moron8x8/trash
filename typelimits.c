#include <stdio.h>

#define critical(type)\
    {\
    unsigned type x = 1, y; \
    while(1){\
        y = x * 2;\
        if (y == 0) break;\
        x = y;\
    }\
    printf("unsigned %s max %llu\n", #type, (unsigned long long)(x + x - 1));\
    printf("unsigned %s min %d\n", #type, 0);\
    printf("signed %s max %llu\n", #type, (unsigned long long) ((x + x - 1) / 2));\
    printf("signed %s min %lld\n\n", #type, - (long long) ((x + x - 1) / 2) - 1);\
    }

#define criticalfloat(type)\
    {\
        type x = 1;\
        while (x * 2 != x * 4){\
            x = x * 2;\
        }\
        type mantissa = x / 2;\
        while(mantissa > 0){\
            if ((x + mantissa) != ((x + mantissa) * 2)) x += mantissa;\
            mantissa /= 2; \
        }\
        type minplus = 1;\
        while(minplus / 2 > 0){ \
            minplus = minplus / 2;\
        }\
        printf("%s max %Le\n", #type, (long double)x);\
        printf("%s min + %Le\n", #type, (long double)minplus);\
        printf("%s min - %Le\n\n", #type, -(long double)x);\
    }


int main(void){
    critical(int);
    critical(long);
    critical(long long);
    critical(char);
    criticalfloat(float);
    criticalfloat(double);
    criticalfloat(long double);
    return 0;
}
