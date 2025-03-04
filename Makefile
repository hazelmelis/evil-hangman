CC = gcc -g
CFLAGS = -Wall --std=c99
OBJECTS = main.o my_string.o

string_driver: $(OBJECTS)
	$(CC) $(CFLAGS) -o string_driver $(OBJECTS)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
my_string.o: my_string.h my_string.c
	$(CC) $(CFLAGS) -c my_string.c -o my_string.o
clean:
	rm -f string_driver main.o my_string.o
