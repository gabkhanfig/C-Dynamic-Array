CC = gcc

dynamic_array: src/main.c src/array/array.c src/array_alt/array_alt.c
	gcc -o dynamic_array src/main.c src/array/array.c src/array_alt/array_alt.c -I.