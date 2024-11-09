#include "map.h"
#include <stdio.h>

uint32_t string_hash(void *key);
void test_ref_type();

int main(void) {
  printf("---map_test---\n");

  test_ref_type();

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

void print_map_kvp2(key_value_pair *kvp, void *context) {
  printf("%d:%s\n", *(int *)kvp->key, (char *)kvp->value);
}

void test_ref_type() {
  hash_map *map = hash_map_create(string_hash);

  char *c1 = "hello1";
  char *c2 = "hello2";
  char *c3 = "hello3";

  int i1 = 1;
  int i2 = 2;
  int i3 = 3;

  hash_map_set(map, &i1, c1);
  hash_map_set(map, &i2, c2);
  hash_map_set(map, &i3, c3);

  int ctx = 9;
  hash_map_for_each(map, print_map_kvp2, &ctx);

  printf("Element at %d, %s\n", i1, (char *)hash_map_get(map, &i1));
}
