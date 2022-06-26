#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct bigint {
  int size;
  int *int_array;
} bigint;

void bigint_set_int(bigint *x, int v)
{
  int cnt = 0;
  x->int_array = (int *)malloc(0);
  do {
    cnt++;
    x->int_array = (int *)realloc(x->int_array, sizeof(int)*cnt);
    x->int_array[cnt-1] = v % 10000;
    v /= 10000;
  } while (v != 0);
  x->size = cnt;
}

void bigint_clear(bigint *x)
{
  free(x->int_array);
}

void bigint_add(bigint *x, const bigint *a)
{
  int adv, i, res;
  int is_larger_than_a = x->size > a->size ? 1 : 0;

  if (!is_larger_than_a) {
    x->int_array = (int *)realloc(x->int_array, sizeof(int)*a->size);
    for (;x->size < a->size; x->size++) {
      x->int_array[x->size] = 0;
    }
  }

  for (i = 0, adv = 0; i < a->size; i++) {
    res = x->int_array[i] + a->int_array[i];
    x->int_array[i] = res % 10000 + adv;
    adv = res / 10000;
  }

  if (adv) {
    if (is_larger_than_a) {
      x->int_array[i] += adv;
    } else {
      x->int_array = (int *)realloc(x->int_array, sizeof(int)*++x->size);
      x->int_array[x->size-1] = adv;
    }
  }
}

void bigint_mul(bigint *x, const bigint *a)
{
  int i, j, res;
  int adv[] = {0, 0};

  bigint tmp;
  tmp.int_array = (int *)malloc(sizeof(int)*(x->size + a->size));
  tmp.size = x->size+a->size;
  for (int cnt = 0; cnt < tmp.size; cnt++) tmp.int_array[cnt] = 0;

  for (i = 0; i < x->size; i++) {
    for (j = 0; j < a->size; j++) {
      res = x->int_array[i] * a->int_array[j];
      tmp.int_array[i+j] += res % 10000 + adv[0];
      tmp.int_array[i+j+1] += res / 10000 + adv[1];
      adv[0] = tmp.int_array[i+j] / 10000;
      adv[1] = tmp.int_array[i+j+1] / 10000;
      tmp.int_array[i+j] %= 10000;
      tmp.int_array[i+j+1] %= 10000;
    }
    tmp.int_array[i+j] += adv[0];
    tmp.int_array[i+j+1] += adv[1];
  }

  for (int k = 1; k <= tmp.size; k++) {
    if (tmp.int_array[tmp.size-k] != 0) {
      x->size = tmp.size - k + 1;
      x->int_array = (int *)realloc(x->int_array, sizeof(int)*x->size);
      break;
    }
  }

  memcpy(x->int_array, tmp.int_array, sizeof(int)*x->size);

  bigint_clear(&tmp);
}

void bigint_print(bigint *res)
{
  int i = 1;
  printf("%d", res->int_array[res->size-i++]);
  for (; i <= res->size; i++) printf("%04d", res->int_array[res->size-i]);
  putchar('\n');
}
