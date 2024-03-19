all:
	gcc -Wall --pedantic src/*.c -o bin/maze

test: all
	bin/maze 
