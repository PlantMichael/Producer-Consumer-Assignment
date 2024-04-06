#include <ctype.h>
#include "prodcon.h"


int main()
{
	srand(time(NULL));

	int shared = shm_open("/Shared_memory", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR); // shared memory object

	if (shared == -1) printf("shm_open() ERROR");

	if (ftruncate(shared, sizeof(struct shmbuf)) == -1) printf("ftruncate() ERROR");
    else ftruncate(shared, sizeof(struct shmbuf));

    struct shmbuf *producer = mmap(0, sizeof(struct shmbuf), PROT_READ|PROT_WRITE, MAP_SHARED, shared, 0);

	if (producer == MAP_FAILED) printf("mmap() ERROR");

    // initializing the semaphores
    sem_init(&producer->sem1, 1, BUF_SIZE);
    sem_init(&producer->sem2, 1, 0);

    for (int j = 0; j < BUF_SIZE; ++j) producer->buf[j] = 0;

    int itemSets = 0;

	while (itemSets < MAX_ITEM_SIZE)
	{
        while (producer->buf[0] != 0 && producer->buf[1] != 0);
            sleep(1);
            sem_wait(&producer->sem1);
        int itemValue;
        for (int j = 0; j< BUF_SIZE; ++j){
            itemValue = rand() % 100 + 1;

			if (itemValue == 0) itemValue = 1;

			producer->buf[j] = itemValue;
            printf("producer added %d\n", itemValue);
        }
        ++itemSets;
        sem_post(&producer->sem2);
    }
    return 0;
}
