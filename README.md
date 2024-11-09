# C Data Structures

Archconvenient generic data structures lib<br>
Examples can be found in [test/](https://github.com/romilk-senpai/rcds/tree/master/test)<br>
Note that sometimes type of items should be specified explicitly

* vector ✅
* hash map ✅

Build static library cmd (uses clang compiler)
```sh
make static
```
Build and run tests
```sh
make testc
```

## Vector

Definition
```c
typedef struct {
  size_t element_size;
  size_t size;
  size_t capacity;
  void *data;
} vector;
```

* vector *vector_create(type)
  ```c
  vector *v = vector_create(int); // type is specified explicitly
  ```
* vector* vector_create_cap(type, capacity)
  ```c
  vector *v = vector_create_cap(int, 25); // type & capcity are specified exlicitly
  ```
* vector_add(v, item)
  ```c
  vector_add(v, 777);
  ```
* (typeof(type)) vector_get(v, type, index)
  ```c
  int item = vector_get(v, int, 1); // type is specified explicitly
  ```
* vector_insert_at(v, index, item)
  ```c
  vector_insert_at(v, 0, 100);
  ```
* vector_remove_at(v, index)
  ```c
  vector_remove_at(v, 0);
  ```
* vector_free(v)
  ```c
  vector_free(v);
  ```

## Hash map
Library does not provide hash any functions, you have to pass hashing functor when creating a map

Definition

```c
typedef struct {
  size_t size;
  size_t capacity;
  key_value_pair **data;
  hash_provider hash_provider;
} hash_map;
```

```c
typedef struct key_value_pair {
  void *key;
  void *value;
  struct key_value_pair *next;
} key_value_pair;
```

Functors signatures
```c
typedef uint32_t (*hash_provider)(void *);
typedef void (*map_for_each_func)(key_value_pair *value);
```

* hash_map *hash_map_create(hash_provider) 
  ```c
  uint32_t my_hash_func(void *key) { return 777; }

  hash_map *map = hash_map_create(my_hash_func);
  ```

* hash_map *hash_map_create_cap(capacity, hash_provider)
  ```c
  uint32_t my_hash_func(void *key) { return 777; }

  hash_map *map = hash_map_create_cap(1000, my_hash_func);
  ```

* hash_map_set(map, key_obj, item)
  ```c
  hash_map_set(map, "my_key", "my_value");
  ```

* (typeof(type)) hash_map_get(map, val_type, key_obj)
  ```c
  char* value = (char *)hash_map_get(map, "my_key");
  ```

* int hash_map_contains(map, key_obj)
  ```c
  if (hash_map_contains(map, "my_key") == 1) {
    printf("%s", "victory");
  }
  ```

* hash_map_for_each(map, for_each_func)
  ```c
  void print_map_kvp(key_value_pair *kvp) {
    printf("%s: %d\n", (char *)kvp->key, *(int *)kvp->value);
  }

  hash_map_for_each(map, print_map_kvp);
  ```

* hash_map_free(map)
  ```c
  hash_map_free(map);
  ```
