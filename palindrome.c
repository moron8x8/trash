#include <stdio.h>
#include <stdlib.h>

char* create_palindrome(const char *str)
{
  if (str == NULL) return 0;
  size_t len = 0;

  while (str[len] != '\0') {
    len++;
  }

  char *res = malloc(len * 2 * sizeof(char) + 1);
  if (res == NULL) return NULL;

  for (size_t i = 0; i < len; i++) {
    *(res + i) = *(str + i);
    *(res + 2 * len - i - 1) = *(str + i);
  }

  *(res + len * 2) = '\0';

  return res;
}

int is_palindrome(const char *str)
{
  if (str == NULL) return 0;
  size_t len = 0;

  while (str[len] != '\0') {
    len++;
  }

  for (size_t i = 0; i < len / 2; i++){
    if (*(str + i) != *(str + len - i - 1)) {
      return 0;
    }
  }
  return 1;
}

int main(void)
{

  char str[] = "1221";

  int res = is_palindrome(str);

  if (res) puts("palindrome");
  else puts("not palindrome");

  char *str2 = create_palindrome(str);

  printf("%s\n", str2);
  free(str2);

  return 0;
}