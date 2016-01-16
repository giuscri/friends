CFLAGS=-g -m32 -O0 -std=c11 -Wall -pedantic

main:
	cc $(CFLAGS) main.c -o main
