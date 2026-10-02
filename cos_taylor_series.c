#include <stdio.h>

double sum_n(double x, int n)
{
  double sum = 1, t = 1;

  for (int k = 1; k < n + 1; k ++){

    t *= - (x * x) / ((2 * k - 1) * (2 * k));
    sum += t;
  }

  return sum;
}

double sum_max_precision(double x)
{
  double sum = 1, t = 1;

  for (int k = 1; ; k ++){
    t *= - (x * x) / ((2 * k - 1) * (2 * k));

    if (sum + t == sum) break;

    sum += t;
  }

  return sum;
}


int main (void)
{
  double x;
  int n;

  scanf("%d %lf", &n, &x);

  printf("sum_n=%.15lf\n", sum_n(x, n));
  printf("sum_max_precision=%.15lf\n", sum_max_precision(x));

  return 0;
}
