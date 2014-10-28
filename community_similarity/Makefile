# gdb flags are for debugging purposes

crime: reset.o compute.o main.o data.o
	gcc -ggdb -o crime reset.o compute.o main.o data.o -lm

main.o: main.c reset.h  compute.h
	gcc -ggdb -c -o main.o main.c 

compute.o: data.h compute.c compute.h 
	gcc -ggdb -c -o compute.o compute.c 

reset.o: reset.h reset.c
	gcc -ggdb -c -o reset.o reset.c

data.o: data.h data.c
	gcc -ggdb -c -o data.o data.c 

clean:
	rm *.o *~ crime
