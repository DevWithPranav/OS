#include <stdio.h>

void main(){
    int numPage , numFrame , pageFault = 0;

    printf("Enter the number of Pages: ");
    scanf("%d", &numPage);

    printf("Enter the number of Frames: ");
    scanf("%d", &numFrame);

    int Frames[numFrame] , Pages[numPage];
    int Time[numFrame];
    int timeCount = 0;

    for(int i=0; i<numFrame; i++){
        Time[i] = 0;
        Frames[i] = -1;
    }

    printf("Enter the Pages: ");
    for(int i=0; i<numPage; i++){
        scanf("%d", &Pages[i]);
    }

    for(int i=0; i<numPage; i++){
        int page = Pages[i];
        int found = 0;

        for(int j=0; j<numFrame ; j++){
            if(Frames[j] == page){
                found = 1;
                Time[j] = timeCount++;
                break;
            }
        }

        if(!found){
            int minIndex = -1;
            int minPageTime = __INT_MAX__;
            for(int j=0; j<numFrame; j++){
                if(Frames[j] == -1){
                    minIndex = j;
                    break;
                }
                if(Time[j] < minPageTime){
                    minIndex = j;
                    minPageTime = Time[j];
                }
            }

            Frames[minIndex] = page;
            Time[minIndex] = timeCount++;
            pageFault++;

        }

        for(int j=0 ;j<numFrame; j++){
            printf("[%d]", Frames[j]);
        }
        printf("\n");
    }
    printf("page fault: %d", pageFault);
}