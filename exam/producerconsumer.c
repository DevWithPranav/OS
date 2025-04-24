// producer.c
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define BUFFER_SIZE 5

struct data {
    int a[BUFFER_SIZE];      // circular buffer
    int index, count;        // index to insert, and total items in buffer
    sem_t full, empty, mutex; // semaphores
} *d;

int main() {
    int produced_item = 0;

    // Create shared memory
    int fd = shm_open("/shared", O_CREAT | O_RDWR, 0666);
    ftruncate(fd, sizeof(struct data));

    // Map shared memory
    d = mmap(NULL, sizeof(struct data), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    // Initialize semaphores
    sem_init(&d->mutex, 1, 1);               // binary mutex
    sem_init(&d->full, 1, 0);                // full slots = 0 initially
    sem_init(&d->empty, 1, BUFFER_SIZE);     // all slots are empty initially

    d->index = 0;
    d->count = 0;

    while (1) {
        sleep(1); // simulate delay

        sem_wait(&d->empty);     // wait for empty slot
        sem_wait(&d->mutex);     // enter critical section

        // Produce item
        d->a[d->index] = produced_item;
        printf("Produced: %d\n", produced_item);
        produced_item++;

        d->index = (d->index + 1) % BUFFER_SIZE;
        d->count++;

        sem_post(&d->mutex);     // leave critical section
        sem_post(&d->full);      // signal that one item is added
    }

    return 0;
}
// consumer.c
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define BUFFER_SIZE 5

struct data {
    int a[BUFFER_SIZE];      // circular buffer
    int index, count;        // index (used by producer), count of items
    sem_t full, empty, mutex; // semaphores
} *d;

int main() {
    int consumed_item, out = 0;

    // Open existing shared memory
    int fd = shm_open("/shared", O_RDWR, 0666);
    d = mmap(NULL, sizeof(struct data), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    while (1) {
        sleep(2); // simulate delay

        if(sem_getValue(&d->full,&value) == 0){
            printf("Buffer is empty, waiting for producer...\n");
            continue; // wait for producer to produce an item
        }

        sem_wait(&d->full);      // wait until at least one item is available
        sem_wait(&d->mutex);     // enter critical section

        consumed_item = d->a[out];
        printf("Consumed: %d | Buffer Count: %d\n", consumed_item, d->count - 1);

        out = (out + 1) % BUFFER_SIZE;
        d->count--;

        sem_post(&d->mutex);     // leave critical section
        sem_post(&d->empty);     // signal that one slot is now free
    }

    return 0;
}
