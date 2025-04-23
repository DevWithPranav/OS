#include <stdio.h>

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4};
    int n = sizeof(pages) / sizeof(pages[0]);
    int frames = 3;
    int memory[frames];
    int front = 0, pageFaults = 0;

    // Initialize memory to -1 (means empty)
    for (int i = 0; i < frames; i++) {
        memory[i] = -1;
    }

    printf("Page\tFrames\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if page is already in memory
        for (int j = 0; j < frames; j++) {
            if (memory[j] == page) {
                found = 1;
                break;
            }
        }

        // If not found, it's a page fault
        if (!found) {
            memory[front] = page;          // Replace page at the front
            front = (front + 1) % frames;  // Move front in circular fashion
            pageFaults++;
        }

        // Print current state of memory
        printf("%d\t", page);
        for (int j = 0; j < frames; j++) {
            if (memory[j] == -1)
                printf("- ");
            else
                printf("%d ", memory[j]);
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);

    return 0;
}
