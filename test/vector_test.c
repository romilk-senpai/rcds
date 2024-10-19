#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  printf("---vector_test---\n");

  vector *v = vector_create(sizeof(int));

  int N = 10;

  *(int *)vector_add(v) = 0;
  *(int *)vector_add(v) = 1;

  for (int i = 0; i < N - 2; i++) {
    *(int *)vector_add(v) =
        *(int *)vector_get(v, v->size - 1) + *(int *)vector_get(v, v->size - 2);
  }

  printf("[");
  for (int i = 0; i < N; i++) {
    char *format = i == 0 ? "%d" : ", %d";

    printf(format, *(int *)vector_get(v, i));
  }
  printf("]\n");

  vector_free(v);
  free(v);

  printf("---SUCCESS---\n");

  return 0;
}
