CC = gcc -g
CFLAGS = -Wall --std=c99
OBJECTS = main.o my_string.o
TESTOBJ = my_string.o unit_test.o test_def.o

string_driver: $(OBJECTS)
	$(CC) $(CFLAGS) -o string_driver $(OBJECTS)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
my_string.o: my_string.h my_string.c
	$(CC) $(CFLAGS) -c my_string.c -o my_string.o

unit_test: $(TESTOBJ)
	$(CC) $(CFLAGS) -o unit_test $(TESTOBJ)
unit_test.o: unit_test.h unit_test.c
	$(CC) $(CFLAGS) -c unit_test.c -o unit_test.o
test_def.o: unit_test.h unit_test.c
	$(CC) $(CFLAGS) -c test_def.c -o test_def.o


clean:
	rm -f string_driver unit_test $(OBJECTS) $(TESTOBJ)
