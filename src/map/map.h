#ifndef MAP_H
#define MAP_H

#include <stddef.h>
#include <stdint.h>

#define MAP_INITIAL_CAPACITY 10

typedef struct {
  char *data;
  size_t len;
} map_str;

typedef struct key_value_pair {
  void *key;
  void *value;
  struct key_value_pair *next;
} key_value_pair;

typedef uint32_t (*hash_provider)(void *);

typedef struct {
  size_t size;
  size_t capacity;
  key_value_pair **data;
  hash_provider hash_provider;
} hash_map;

#define hash_map_create(capacity, hash_provider)                               \
  ({ _hash_map_create(capacity, hash_provider); })

#define hash_map_set(map, key_obj, item)                                       \
  ({ *(typeof(item) *)_hash_map_set(map, key_obj) = item; })

#define hash_map_get(map, val_type, key_obj)                                   \
  ({ *(val_type *)_hash_map_get(map, key_obj); })

#define hash_map_contains(map, key_obj) ({ _hash_map_contains(map, key_obj); })

#define hash_map_free(map) ({ _hash_map_free(map); })

hash_map *_hash_map_create(size_t capacity, hash_provider hash_provider);
void *_hash_map_set(hash_map *map, void *key_obj);
void *_hash_map_get(hash_map *map, void *key_obj);
int _hash_map_contains(hash_map *map, void *key_obj);
void _hash_map_free(hash_map *map);

#endif
