#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

vector *_vector_create(size_t element_size) {
  vector *v = malloc(sizeof(vector));

  v->element_size = element_size;
  v->size = 0;
  v->capacity = VEC_INITIAL_CAPACITY;
  v->data = malloc(element_size * v->capacity);

  return v;
}

void *_vector_add(vector *v) {
  _resize_if_necessary(v);

  v->size++;

  return v->data + v->element_size * (v->size - 1);
}

void *_vector_get(vector *v, size_t index) {
  return v->data + index * v->element_size;
}

void *_vector_insert(vector *v, size_t index) {
  _resize_if_necessary(v);

  memmove(v->data + v->element_size * (index + 1),
          v->data + v->element_size * index,
          (v->size - index) * v->element_size);

  v->size++;

  return v->data + index * v->element_size;
}

void _vector_remove_at(vector *v, size_t index) {
  memmove(v->data + v->element_size * index,
          v->data + v->element_size * (index + 1),
          (v->size - index - 1) * v->element_size);

  v->size--;
}

void _resize_if_necessary(vector *v) {
  if (v->size == v->capacity) {
    _vector_resize(v, v->capacity * 2);
  }
}

void _vector_resize(vector *v, size_t capacity) {
  void *data = realloc(v->data, v->element_size * capacity);
  v->capacity = capacity;
  v->data = data;
}

void _vector_free(vector *v) {
  free(v->data);
  free(v);
}


