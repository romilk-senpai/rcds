#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

vector *vector_create(size_t element_size) {
  vector *v = malloc(sizeof(vector));

  v->element_size = element_size;
  v->size = 0;
  v->capacity = VEC_INITIAL_CAPACITY;
  v->data = malloc(element_size * v->capacity);

  return v;
}

void *vector_get(vector *v, size_t index) {
  return v->data + index * v->element_size;
}

void *vector_add(vector *v) {
  if (v->size == v->capacity) {
    vector_resize(v, v->capacity * 2);
  }

  v->size++;

  return v->data + v->element_size * (v->size - 1);
}

void vector_resize(vector *v, size_t capacity) {
  void *data = realloc(v->data, v->element_size * capacity);
  v->capacity = capacity;
  v->data = data;
}

void vector_free(vector *v) { free(v->data); }
