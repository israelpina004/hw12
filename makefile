all: hw12.o
	gcc -o hw12 hw12.o

hw12.o: hw12.c
	gcc -c hw12.c

run:
	./hw12

clean:
	rm *.o
