all: malloc_stub.so use_malloc

malloc_stub.so: malloc_stub.c
	gcc -shared -fPIC -g -o $@ $^ -ldl

use_malloc:	use_malloc.cpp
	g++ -Wall -g $^ -o $@ -ldl


