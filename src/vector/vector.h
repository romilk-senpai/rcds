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

#define vector_create(type) ({ _vector_create(sizeof(type)); })

#define vector_add(v, type, item) ({ *(type *)_vector_add(v) = item; })

#define vector_get(v, type, index) ({ *(type *)_vector_get(v, index); })

#define vector_insert_at(v, type, index, item)                                 \
  ({ *(type *)_vector_insert(v, index) = item; })

#define vector_remove_at(v, index) ({ _vector_remove_at(v, index); })

#define vector_free(v) ({ _vector_free(v); })

#define vector_print(v) ({ _vector_print(v); })

vector *_vector_create(size_t element_size);
void *_vector_add(vector *v);
void *_vector_get(vector *v, size_t index);
void *_vector_insert(vector *v, size_t index);
void _vector_remove_at(vector *v, size_t index);
void _resize_if_necessary(vector *v);
void _vector_resize(vector *v, size_t capacity);
void _vector_free(vector *v);

#endif
