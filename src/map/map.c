#include "map.h"
#include <stdlib.h>

hash_map *_hash_map_create(size_t capacity, hash_provider hash_provider) {
  hash_map *map = malloc(sizeof(hash_map));

  map->size = 0;
  map->capacity = capacity;
  map->data = calloc(sizeof(key_value_pair) * map->capacity);
  map->hash_provider = hash_provider;

  return map;
}

void _hash_map_set(hash_map *map, void *key_obj, void *item) {
  uint32_t hash = map->hash_provider(key_obj);

  size_t index = hash & (map->capacity - 1);
  key_value_pair *ptr = map->data + index;
  int i = 0;
  while (ptr + i != NULL) {
    if (hash == map->hash_provider(ptr + i))
    {
      (ptr + i)->value = item;
      break;
    }
    i++;
  }

  *ptr = (key_value_pair) { key_obj, item }
}

void *_hash_map_get(hash_map *map, void *key_obj) { return NULL; }

void *_hash_map_contains(hash_map *map) { return NULL; }
