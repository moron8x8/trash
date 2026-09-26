#include <stdio.h>

int main(void)
{
  long long base, res;
  int exp;

  res = 1;

  if (scanf("%lld", &base) != 1) return 0; 
  if (scanf("%d", &exp) != 1 || exp < 0) return 0;

  while (exp > 0) {
    if (exp % 2 == 0) {
      base *= base;
      exp /= 2;
    } else {
      res *= base;
      exp--;
    }

  }
  printf("%lld\n", res); 
  
  return 0;
}
