#include <stdio.h>

void main(){
    int numPages , numFrames , pageFault = 0;
    printf("Enter the number of frames: ");
    scanf("%d", &numFrames);

    printf("Enter the number of pages: ");
    scanf("%d", &numPages);

    int Frames[numFrames], Pages[numPages];
    int freq[numFrames], time[numFrames];

    int currentTime = 0;

    printf("Enter the pages: ");
    for(int i=0; i<numPages; i++){
        scanf("%d", &Pages[i]);
    }

    for(int i=0 ;i<numFrames; i++){
        Frames[i] = -1;
        freq[i] = 0;
        time[i] = 0;
    }

    for(int i=0; i<numPages; i++){
        int page = Pages[i];
        int found = 0;

        for(int j=0; j<numFrames; j++){
            if(Frames[j] == page){
                found = 1;
                freq[j]++;
                time[j] = currentTime++;
                break;
            }
        }

        if(!found){
            int minIndex = -1;
            int minPageFrq = __INT_MAX__;

            for(int j =0 ; j<numFrames; j++){
                if(Frames[j] == -1){
                    minIndex = j;
                    break;
                }
                if(minIndex == -1 || freq[j] < minPageFrq || (freq[j] == minPageFrq && time[j] < time[minIndex])){
                    minIndex = j;
                    minPageFrq = freq[j];
                }
            }

            Frames[minIndex] = page;
            freq[minIndex] = 1;
            time[minIndex] = currentTime++;
            pageFault++;
        }

        for(int j=0 ;j <numFrames; j++){
            printf("[%d]", Frames[j]);
        }
        printf("\n");
    }

    printf("Page Fault for the LFU algo is: %d", pageFault);

}