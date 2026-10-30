#include <stdio.h>

#define MAXLEN 10000
#define BASE 10000

typedef struct {
  short num[MAXLEN];
  int sign;
  int len;
} Big_int;



int my_strlen(char *s)
{
  int i = 0;
  while (s[i] != '\0')
    i++;
  return i;
}

void fix(Big_int *n)
{
  while (n->len > 1 && n->num[n->len - 1] == 0) n->len--  ;
  if (n->len == 1 && n->num[0] == 0) n->sign = 1; // change -0
}

void create_num(char *s, Big_int *n)
{
  int start = 0, len, from, val;

  n->sign = 1;

  if (s[0] == '-'){
    n->sign = -1;
    start = 1;
  }

  len = my_strlen(s);

  n->len = 0;

  for (int i = len; i > start; i -= 4) {
    from = i - 4;
    if (from < start) from = start;
    val = 0;
    for (int k = from; k < i; k++) {
      val = val * 10 + (s[k] - '0');
    }
    n->num[n->len] = val;
    n->len++;
  }

  fix(n);
}


void print_num(Big_int *n)
{
  if (n->sign == -1) putchar('-');
  printf("%d", n->num[n->len - 1]);

  for (int i = n->len - 2; i >= 0; i--) printf("%04d", n->num[i]);

  putchar('\n');
}

int compare_abs(Big_int *n1, Big_int *n2)
{
  if (n1->len > n2->len) return 1;
  else if (n1->len < n2->len) return -1;
  for (int i = n1->len - 1; i >= 0; i--) {
    if (n1->num[i] > n2->num[i]) return 1;
    else if (n1->num[i] < n2->num[i]) return -1;
  }
  return 0;
}

void sum_abs(Big_int *n1, Big_int *n2, Big_int *res)
{
  int sum, extra, n;
  n = (n1->len < n2->len) ? n2->len: n1->len;
  extra = 0;
  for (int i = 0; i < n; i++) {
    sum = extra;
    if (i < n1->len) sum += n1->num[i];
    if (i < n2->len) sum += n2->num[i];
    res->num[i] = sum % BASE;
    extra = sum / BASE;
  }
  if (extra > 0) {
    if (n >= MAXLEN) return;
    res->num[n] = extra;
    n++;
  }

  res->len = n;
}

void diff_abs(Big_int *n1, Big_int *n2, Big_int *res)
{
  int sum, diff;
  diff = 0;

  for (int i = 0; i < n1->len; i++) {
    sum = n1->num[i] - diff;
    if (i < n2->len) sum -= n2->num[i];
    if (sum < 0) {
      sum += BASE;
      diff = 1;
    }
    else diff = 0;

    res->num[i] = sum;
  }

  res->len = n1->len;
}

void sum(Big_int *n1, Big_int *n2, Big_int *res)
{
  int n1_sign = n1->sign;
  int n2_sign = n2->sign;

  if (n1_sign == n2_sign) {
    sum_abs(n1, n2, res);
    res->sign = n1_sign;
  } else if (compare_abs(n1, n2) > 0) {
    diff_abs(n1, n2, res);
    res->sign = n1_sign;
  }
  else {
    diff_abs(n2, n1, res);
    res->sign = n2_sign;
  }
  fix(res);
}

void diff(Big_int *n1, Big_int *n2, Big_int *res)
{
  n2->sign = -n2->sign;
  sum(n1, n2, res);
  n2->sign = -n2->sign;
  fix(n2);
}


void mult_int(Big_int *n, int num)
{
  int current, extra, len;
  extra = 0;
  len = n->len;

  for (int i = 0; i < len; i++) {
    current = n->num[i] * num + extra;
    n->num[i] = current % BASE;
    extra = current / BASE;
  }
  while(extra > 0)
  {
    if (len >= MAXLEN) return;
    n->num[len] = extra % BASE;
    extra /= BASE;
    n->len++;
    len++;
  }
  fix(n);
}

void mult(Big_int *n1, Big_int *n2, Big_int *res) // its like mult in cols
{
  Big_int temp_mult;

  int len1 = n1->len;
  int len2 = n2->len;
  if (len1 + len2 > MAXLEN) return;

  create_num("0", res);
  for (int i = 0; i < len2; i++) {
    temp_mult = *n1;
    mult_int(&temp_mult, n2->num[i]);

    for (int j = temp_mult.len - 1; j >= 0; j--) temp_mult.num[j + i] = temp_mult.num[j];
    for (int j = 0; j < i; j++) temp_mult.num[j] = 0;

    temp_mult.len += i;
    sum_abs(res, &temp_mult, res);
  }

  res->sign = n1->sign * n2->sign;
  fix(res);
}

void fact(Big_int *n, Big_int *res)
{
  Big_int count, one, temp_fac;

  create_num("1", res);
  create_num("1", &one);
  create_num("1", &count);

  while (compare_abs(&count, n) <= 0) {
    mult(res, &count, &temp_fac);
    *res = temp_fac;
    sum(&one, &count, &count);
  }
}

void div2(Big_int *n) // idea n / 2 = n * 5000 / 10000 => * 5000 and remove last cell
{
  mult_int(n, 5000);
  for (int i = 0; i < n->len - 1; i++){
    n->num[i] = n->num[i + 1];
  }
  if (n->len > 1) n->len--;
  else n->num[0] = 0;
  fix(n);
}


void power(Big_int *base, Big_int *exp, Big_int *res)
{
  Big_int temp_pow;

  create_num("1", res);

  while(!(exp->len == 1 && exp->num[0] == 0)) {
    if (exp->num[0] % 2 == 1) {
      mult(res, base, &temp_pow);
      *res = temp_pow;
    }
    mult(base, base, &temp_pow);
    *base = temp_pow;
    div2(exp);
  }
}

void range_sum(Big_int *n1, Big_int *n2, Big_int *res)
{
  Big_int one;
  Big_int *low = n1;
  Big_int *high = n2;

  if (n1->sign > n2->sign || (n1->sign == n2->sign && compare_abs(n1, n2) * n1->sign > 0)) {
    low = n2;
    high = n1;
  }

  create_num("1", &one);
  sum(low, high, res); // res = n1 + n2
  diff(high, low, high); // high = n2 - n1
  sum(high, &one, high); // high = n2 - n1 + 1
  mult(res, high, low); // low = (n1 + n2) * (n2 - n1 + 1)
  div2(low);
  *res = *low;
}

int main(void)
{
  Big_int num1, num2, result;

  char operation;
  char str[1100];

  scanf(" %c", &operation);
  scanf("%1099s", str);
  create_num(str, &num1);
  if(operation != '!') {
    scanf("%1099s", str);
    create_num(str, &num2);
  }

  switch (operation) {
    case '+':
      sum(&num1, &num2, &result);
      break;
    case '-':
      diff(&num1, &num2, &result);
      break;
    case '*':
      mult(&num1, &num2, &result);
      break;
    case '^':
      power(&num1, &num2, &result);
      break;
    case '!':
      fact(&num1, &result);
      break;
    case 'S':
      range_sum(&num1, &num2, &result);
      break;
  }

  print_num(&result);

  return 0;
}