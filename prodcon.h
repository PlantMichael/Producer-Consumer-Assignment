#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#define errExit(msg)	do { perror(msg); exit(EXIT_FAILURE);\
			} while (0)

#define BUF_SIZE 2
#define MAX_ITEM_SIZE 10


struct shmbuf {
	sem_t sem1;
	sem_t sem2;
	int buf[BUF_SIZE];
};

