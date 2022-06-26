#include <stdio.h>
#include "bigint.h"

void factorial(bigint *res, int n)
{
  bigint bi;
  bigint_set_int(res, 1);
  for (int i = 1; i <= n; i++) {
    bigint_set_int(&bi, i);
    bigint_mul(res, &bi);
    bigint_clear(&bi);
  }
}

int main()
{
  bigint res;
  for (int i = 1; i <= 50; i++) {
    factorial(&res, i);
    printf("%d! = ", i);
    bigint_print(&res);
    bigint_clear(&res);
  }
  return 0;
}