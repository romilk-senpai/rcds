# C Data Structures

Archconvenient generic data structures lib.<br>
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
* vector_get(v, type, index)
  ```c
  vector_get(v, int, 1); // type is specified explicitly
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