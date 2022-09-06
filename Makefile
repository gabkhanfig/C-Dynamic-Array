CC = gcc

dynamic_array: src/main.c src/array/array.c
	gcc -o dynamic_array src/main.c src/array/array.c -I.