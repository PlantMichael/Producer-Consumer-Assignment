#include <string.h>
#include "prodcon.h"



int main()
{
	int shared = shm_open("/Shared_memory", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

	if (shared == -1) printf("shm_open() ERROR");

	if (ftruncate(shared, sizeof(struct shmbuf)) == -1) printf("ftruncate() ERROR");
    else ftruncate(shared, sizeof(struct shmbuf));

    struct shmbuf *consumer = mmap(0, sizeof(struct shmbuf), PROT_READ | PROT_WRITE, MAP_SHARED, shared, 0);
	if (consumer == MAP_FAILED) printf("mmap() ERROR");

    int itemSets = 0;
    while (itemSets < MAX_ITEM_SIZE){
        while(consumer->buf[0] == 0 && consumer->buf[1] == 0);
            sleep(1);
            sem_wait(&consumer->sem2);
        for (int j = 0; j < BUF_SIZE; ++j){
            printf("consumer removed %d\n", consumer->buf[j]);
            consumer->buf[j] = 0;
		}
        ++itemSets;
        sem_post(&consumer->sem1);
    }
    return 0;
}


