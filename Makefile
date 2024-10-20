COMPILER = clang

dyn:

static:
	mkdir -p out/
	mkdir -p librcds/include/
	$(COMPILER) -g -c src/vector/vector.c -o out/vector.o
	$(COMPILER) -g -c src/map/map.c -o out/map.o
	ar rcs librcds/librcds.a out/vector.o out/map.o
	yes | cp -rf src/vector/vector.h librcds/include/vector.h
	yes | cp -rf src/map/map.h librcds/include/map.h

testc:
	make clean
	make static
	mkdir -p out/test/
	$(COMPILER) -g test/vector_test.c -Ilibrcds/include -Llibrcds -lrcds -o out/test/vector_test
	$(COMPILER) -g test/map_test.c -Ilibrcds/include -Llibrcds -lrcds -o out/test/map_test
	./out/test/vector_test
	./out/test/map_test

clean:
	rm -d -r -f librcds/
	rm -d -r -f out/
