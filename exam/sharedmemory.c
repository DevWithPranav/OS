#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define SIZE 1000
#define NAME "/myshm"

struct message {
    char msg[100];
    int turn; // 0 for parent to write, 1 for child to write
};

int main() {
    int fd = shm_open(NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, SIZE);

    struct message *message = mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    message->turn = 0;

    pid_t pid = fork();

    if (pid == 0) {
        // 👶 Child
        while (1) {
            if (message->turn == 1) {
                printf("Parent says: %s\n", message->msg);
                printf("Child: ");
                fgets(message->msg, sizeof(message->msg), stdin);
                message->msg[strcspn(message->msg, "\n")] = '\0';
                if (strcmp(message->msg, "exit") == 0){
                 message->turn = 0;
                break;
                }
                message->turn = 0;
            }
            usleep(100000);
        }
    } else {
        // 👨 Parent
        while (1) {
            if (message->turn == 0) {
                printf("Parent: ");
                fgets(message->msg, sizeof(message->msg), stdin);
                message->msg[strcspn(message->msg, "\n")] = '\0';
                if (strcmp(message->msg, "exit") == 0) break;
                message->turn = 1;
            }
            usleep(100000);
        }

        wait(NULL);
        shm_unlink(NAME);
    }

    return 0;
}
