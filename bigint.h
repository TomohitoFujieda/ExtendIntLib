#ifndef DEFINE_H_BIGINT
#define DEFINE_H_BIGINT

typedef struct bigint {
  int size;
  int *int_array;
} bigint;

extern void bigint_set_int(bigint *x, int a);
extern void bigint_add(bigint *x, bigint *a);
extern void bigint_mul(bigint *x, bigint *a);
extern void bigint_print(bigint *x);
extern void bigint_clear(bigint *x);

#endif /* DEFINE_H_BIGINT */