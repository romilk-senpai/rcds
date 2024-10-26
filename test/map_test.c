#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint32_t string_hash(void *key);
void read_set1();
void read_set2();

int main(void) {
  printf("---map_test---\n");

  read_set1();
  read_set2();

  printf("---map_test---\n");
  return 0;
}

// http://www.cse.yorku.ca/~oz/hash.html
uint32_t string_hash(void *key) {
  char *str = (char *)key;
  uint32_t hash = 5381;
  int c;

  while ((c = *str++)) {
    hash = ((hash << 5) + hash) + c; // hash * 33 + c
  }

  return hash;
}

void read_set1() {
  hash_map *map = hash_map_create(10, string_hash);

  FILE *file = fopen("out/test/map_test_set1.txt", "rb");
  if (file == NULL) {
    fprintf(stderr, "Error opening file t1\n");
    return;
  }
  char *buf = malloc(sizeof(char) * 1024);
  size_t buf_index = 0;
  char ch;
  while ((ch = fgetc(file)) != EOF) {
    if (ch == 10 || ch == 32) {
      if (buf_index == 0)
        continue;

      buf[buf_index] = '\0';
      char *key = strdup(buf);
      if (hash_map_contains(map, key) == 0) {
        hash_map_set(map, key, 0);
      } else {
        int val = hash_map_get(map, int, key);
        hash_map_set(map, key, val + 1);
      }

      buf_index = 0;
      continue;
    }

    buf[buf_index] = ch;
    buf_index++;
  }

  if (buf_index > 0) {
    buf[buf_index] = '\0';
    char *key = strdup(buf);
    if (hash_map_contains(map, key) == 0) {
      hash_map_set(map, key, 0);
    } else {
      int val = hash_map_get(map, int, key);
      hash_map_set(map, key, val + 1);
    }
  }

  fclose(file);

  if (hash_map_contains(map, "banana") == 1) {
    int val = hash_map_get(map, int, "banana");
    printf("%s: %d", "banana", val);
  }

  free(buf);
  hash_map_free(map);
}

void read_set2() {}
