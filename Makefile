main:
	gcc main.c -o run

noinit:
	gcc main.c -o run && \
	./run

init:
	gcc main.c -o run && \
	./run init

