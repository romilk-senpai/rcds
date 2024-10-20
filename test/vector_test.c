#include "vector.h"
#include <stdio.h>

void print_int_vec(vector *v) {
  printf("[");
  for (int i = 0; i < v->size; i++) {
    char *format = i == 0 ? "%d" : ", %d";

    printf(format, vector_get(v, int, i));
  }
  printf("] Size: %zu\n", v->size);
}

int main(void) {
  printf("---vector_test---\n");

  vector *v1 = vector_create(int);

  int N = 10;

  vector_add(v1, int, 0);
  vector_add(v1, int, 1);

  for (int i = 0; i < N - 2; i++) {
    vector_add(v1, int,
               vector_get(v1, int, v1->size - 1) +
                   vector_get(v1, int, v1->size - 2));
  }

  print_int_vec(v1);

  vector_insert_at(v1, int, 0, 100);
  vector_insert_at(v1, int, 11, 101); // teehee~

  print_int_vec(v1);

  vector_remove_at(v1, 0);
  vector_remove_at(v1, 11);

  print_int_vec(v1);

  vector_free(v1);

  printf("---vector_test---\n");

  return 0;
}
