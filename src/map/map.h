#ifndef MAP_H
#define MAP_H

#include <stddef.h>
#include <stdint.h>

#define MAP_INITIAL_CAPACITY 10
#define LOAD_FACTOR_THRESHOLD 0.7

typedef struct key_value_pair {
  void *key;
  void *value;
  struct key_value_pair *next;
} key_value_pair;

typedef uint32_t (*hash_provider)(void *);
typedef void (*map_for_each_func)(key_value_pair *value, void *context);

typedef struct {
  size_t size;
  size_t capacity;
  key_value_pair **data;
  hash_provider hash_provider;
} hash_map;

hash_map *hash_map_create(hash_provider hash_provider);
hash_map *hash_map_create_cap(size_t capacity, hash_provider hash_provider);
static hash_map *_hash_map_create(size_t capacity, hash_provider hash_provider);
void hash_map_set(hash_map *map, void *key_obj, void *item);
void *hash_map_get(hash_map *map, void *key_obj);
int hash_map_contains(hash_map *map, void *key_obj);
static void hash_map_resize(hash_map *map);
void hash_map_for_each(hash_map *map, map_for_each_func for_each_func,
                       void *context);
void hash_map_free(hash_map *map);

#endif
