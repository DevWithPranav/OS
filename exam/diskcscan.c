#include <stdio.h>
#include <stdlib.h>

void main(){
    int numRequest, diskSize, initHead;

    printf("Enter the number of request: ");
    scanf("%d",&numRequest);

    int reqest[numRequest+3];
    printf("Enter the request: ");
    for(int i=0; i<numRequest;i++){
        scanf("%d", &reqest[i]);
    }

    printf("Enter the disk Size: ");
    scanf("%d", &diskSize);

    printf("Enter the initial head: ");
    scanf("%d", &initHead);

    int totalSeektime =0;

    reqest[numRequest] = 0;
    reqest[numRequest+1] = initHead;
    reqest[numRequest+2] = diskSize - 1;
    numRequest += 3;

    for(int i=0; i<numRequest; i++){
        for(int j=0; j<numRequest-i-1; j++){
            if(reqest[j] >reqest[j+1]){
                int temp = reqest[j+1];
                reqest[j+1] = reqest[j];
                reqest[j] = temp;
            }
        }
    }

    int headIndex = -1;

    for(int i=0;i<numRequest;i++){
        if(reqest[i] == initHead){
            headIndex = i;
            break;
        }
    }

    int currentHead = initHead;
    for(int i=headIndex; i>=0; i--){
        printf("%d->", reqest[i]);
        totalSeektime += abs(currentHead - reqest[i]);
        currentHead = reqest[i];
    }
    for(int i=numRequest-1; i>headIndex; i--){
        printf("%d->", reqest[i]);
        totalSeektime += abs(currentHead - reqest[i]);
        currentHead = reqest[i];
    }

    printf("total seekTime : %d", totalSeektime);

}