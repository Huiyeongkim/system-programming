CC=gcc
CFLAGS=-I.

DEPS = 20210292.h

OBJ = 20210292.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

20210292: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJ) 20210292
