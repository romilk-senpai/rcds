#include "map.h"
#include <stdlib.h>

hash_map *_hash_map_create(size_t capacity, hash_provider hash_provider) {
  hash_map *map = malloc(sizeof(hash_map));

  map->size = 0;
  map->capacity = capacity;
  map->data = malloc(sizeof(key_value_pair) * map->capacity);
  map->hash_provider = hash_provider;

  return map;
}

void _hash_map_add(hash_map *map, void *key_obj, void *item) {
  uint32_t hash = map->hash_provider(key_obj);
}

void *_hash_map_get(hash_map *map, void *key_obj) { return NULL; }

void *_hash_map_contains(hash_map *map) { return NULL; }

map_str _hash(void *obj) {
  map_str hash = {0};
  return hash;
}
