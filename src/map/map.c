#include "map.h"
#include <stdio.h>
#include <stdlib.h>

hash_map *_hash_map_create(size_t capacity, hash_provider hash_provider) {
  hash_map *map = malloc(sizeof(hash_map));
  map->size = 0;
  map->capacity = capacity;
  map->data = calloc(map->capacity, sizeof(key_value_pair *));
  map->hash_provider = hash_provider;
  return map;
}

key_value_pair *_hash_map_set(hash_map *map, void *key_obj) {
  if ((double)map->size / map->capacity > LOAD_FACTOR_THRESHOLD) {
    _hash_map_resize(map);
  }

  uint32_t hash = map->hash_provider(key_obj);
  size_t index = hash & (map->capacity - 1);

  key_value_pair *ptr = *(map->data + index);
  while (ptr != NULL) {
    if (map->hash_provider(ptr->key) == map->hash_provider(key_obj)) {
      return ptr;
    }
    ptr = ptr->next;
  }

  key_value_pair *new_pair = malloc(sizeof(key_value_pair));
  new_pair->key = key_obj;
  new_pair->value = NULL;
  new_pair->next = *(map->data + index);
  *(map->data + index) = new_pair;
  map->size++;

  return new_pair;
}

void *_hash_map_get(hash_map *map, void *key_obj) {
  uint32_t hash = map->hash_provider(key_obj);
  size_t index = hash & (map->capacity - 1);

  key_value_pair *ptr = map->data[index];
  while (ptr != NULL) {
    if (map->hash_provider(ptr->key) == map->hash_provider(key_obj)) {
      return ptr->value;
    }
    ptr = ptr->next;
  }

  return NULL;
}

int _hash_map_contains(hash_map *map, void *key_obj) {
  return _hash_map_get(map, key_obj) != NULL;
}

void _hash_map_resize(hash_map *map) {
  size_t new_capacity = map->capacity * 2;

  key_value_pair **new_data = calloc(new_capacity, sizeof(key_value_pair *));

  for (size_t i = 0; i < map->capacity; i++) {
    key_value_pair *ptr = *(map->data + i);
    while (ptr != NULL) {
      uint32_t hash = map->hash_provider(ptr->key);
      size_t new_index = hash & (new_capacity - 1);

      key_value_pair *new_pair = malloc(sizeof(key_value_pair));
      if (new_pair) {
        new_pair->key = ptr->key;
        new_pair->value = ptr->value;
        new_pair->next = *(new_data + new_index);
        *(new_data + new_index) = new_pair;
      }

      ptr = ptr->next;
    }
  }

  free(map->data);
  map->data = new_data;
  map->capacity = new_capacity;
}

void _hash_map_for_each(hash_map *map, map_for_each_func for_each_func, void *context) {
  for (size_t i = 0; i < map->capacity; i++) {
    key_value_pair *ptr = *(map->data + i);
    while (ptr != NULL) {
      for_each_func(ptr, context);
      ptr = ptr->next;
    }
  }
}

void _hash_map_free(hash_map *map) {
  for (size_t i = 0; i < map->capacity; i++) {
    key_value_pair *current = map->data[i];
    while (current != NULL) {
      key_value_pair *temp = current;
      current = current->next;
      free(temp);
    }
  }
  free(map->data);
  free(map);
}
