CC = gcc

CFLAGS = -Wall -pthread

TARGETS = mutex sem cv

all: $(TARGETS)

mutex: mutex.c
	$(CC) $(CFLAGS) -o mutex mutex.c -lm

20210292-sem: 20210292-sem.c
	$(CC) $(CFLAGS) -o sem sem.c -lm

20210292-cv: 20210292-cv.c
	$(CC) $(CFLAGS) -o cv cv.c -lm

clean:
	rm -f $(TARGETS)
