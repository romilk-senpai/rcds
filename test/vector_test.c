#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  printf("---vector_test---\n");

  vector *v = vector_create(int);

  int N = 10;

  vector_add(v, int, 0);
  vector_add(v, int, 1);

  for (int i = 0; i < N - 2; i++) {
    vector_add(v, int,
               vector_get(v, int, v->size - 1) +
                   vector_get(v, int, v->size - 2));
  }

  printf("Uh oh fibonacci sequence: [");
  for (int i = 0; i < N; i++) {
    char *format = i == 0 ? "%d" : ", %d";

    printf(format, vector_get(v, int, i));
  }
  printf("]\n");

  vector_free(v);
  free(v);

  printf("---SUCCESS---\n\n");

  return 0;
}
