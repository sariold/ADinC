CC = gcc

CFLAGS = -O2 -std=c99 -pedantic -Wall -o -lm

graph: graphsmain.c graphs.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean debug-scan

clean:
	rm -f eval recog scan eq
