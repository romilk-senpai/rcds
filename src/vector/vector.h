#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

#define VEC_INITIAL_CAPACITY 10

typedef struct {
  size_t element_size;
  size_t size;
  size_t capacity;
  void *data;
} vector;

vector *vector_create(size_t element_size);
void *vector_add(vector *v);
void *vector_remove(vector *v, size_t index);
void *vector_get(vector *v, size_t index);
// void *vector_insert(vector *v, void *item, size_t index);
// void *vector_remove_at(vector *v, size_t index);
void vector_resize(vector *v, size_t capacity);
void vector_free(vector *v);

#endif
