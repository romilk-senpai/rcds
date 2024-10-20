#ifndef MAP_H
#define MAP_H

#include <stddef.h>
#include <stdint.h>

#define MAP_INITIAL_CAPACITY 10

typedef struct {
  char *data;
  size_t len;
} map_str;

typedef struct {
  map_str key;
  void *value;
} key_value_pair;

typedef uint32_t (*hash_provider)(void *);

typedef struct {
  size_t size;
  size_t capacity;
  key_value_pair *data;
  hash_provider hash_provider;
} hash_map;

#endif
