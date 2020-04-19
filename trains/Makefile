CC     = gcc
CFLAGS = -g -std=c99 -pedantic -Wall

trains: scanner.c trains.c trainsMain.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f trains
