#include "map.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

hash_map *hash_map_create(hash_provider hash_provider) {
  return _hash_map_create(MAP_INITIAL_CAPACITY, hash_provider);
}

hash_map *hash_map_create_cap(size_t capacity, hash_provider hash_provider) {
  return _hash_map_create(capacity, hash_provider);
}

static hash_map *_hash_map_create(size_t capacity,
                                  hash_provider hash_provider) {
  size_t cap = capacity;
  if (cap % 2 == 1) {
    cap++;
  }

  hash_map *map = malloc(sizeof(hash_map));
  map->size = 0;
  map->capacity = capacity;
  map->data = calloc(map->capacity, sizeof(key_value_pair *));
  map->hash_provider = hash_provider;
  return map;
}

void hash_map_set(hash_map *map, void *key_obj, void *item) {
  if ((double)map->size / map->capacity > LOAD_FACTOR_THRESHOLD) {
    hash_map_resize(map);
  }

  uint32_t hash = map->hash_provider(key_obj);
  size_t index = hash & (map->capacity - 1);

  key_value_pair *ptr = *(map->data + index);
  while (ptr != NULL) {
    if (map->hash_provider(ptr->key) == hash) {
      free(ptr->value);
      ptr->value = item;
      return;
    }
    ptr = ptr->next;
  }

  key_value_pair *new_pair = malloc(sizeof(key_value_pair));
  new_pair->key = key_obj;
  new_pair->value = item;
  new_pair->next = *(map->data + index);
  *(map->data + index) = new_pair;
  map->size++;
}

void *hash_map_get(hash_map *map, void *key_obj) {
  uint32_t hash = map->hash_provider(key_obj);
  size_t index = hash & (map->capacity - 1);

  key_value_pair *ptr = map->data[index];
  while (ptr != NULL) {
    if (map->hash_provider(ptr->key) == hash) {
      return ptr->value;
    }
    ptr = ptr->next;
  }

  return NULL;
}

void hash_map_delete(hash_map *map, void *key_obj) {
  uint32_t hash = map->hash_provider(key_obj);
  size_t index = hash & (map->capacity - 1);

  key_value_pair *prev = NULL;
  key_value_pair *current = map->data[index];

  while (current != NULL) {
    if (map->hash_provider(current->key) == hash) {
      if (prev == NULL) {
        map->data[index] = current->next;
      } else {
        prev->next = current->next;
      }
      free(current);
      map->size--;
      return;
    }
    prev = current;
    current = current->next;
  }
}

int hash_map_contains(hash_map *map, void *key_obj) {
  return hash_map_get(map, key_obj) != NULL;
}

static void hash_map_resize(hash_map *map) {
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

void hash_map_for_each(hash_map *map, map_for_each_func for_each_func,
                       void *context) {
  for (size_t i = 0; i < map->capacity; i++) {
    key_value_pair *ptr = *(map->data + i);
    while (ptr != NULL) {
      for_each_func(ptr, context);
      ptr = ptr->next;
    }
  }
}

void hash_map_free(hash_map *map) {
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
