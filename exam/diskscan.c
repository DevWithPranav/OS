#include <stdio.h>
#include <stdlib.h>

void main(){
    int numRequest, initHead;

    printf("Enter the number of Request: ");
    scanf("%d", &numRequest);

    printf("Enter the current Head Position: ");
    scanf("%d", &initHead);

    int request[numRequest];
    printf("Enter the request: ");
    for(int i=0; i<numRequest; i++){
        scanf("%d", &request[i]);
    }

    int direction;
    printf("Enter the direction (high: 1 | low: 0): ");
    scanf("%d", &direction);

    request[numRequest] = initHead;
    numRequest++;

    for(int i =0; i<numRequest; i++){
        for(int j=0; j<numRequest - i - 1; j++){
            if(request[j] > request[j+1]){
                int temp = request[j+1];
                request[j+1] = request[j];
                request[j] = temp;
            }
        }
    }

    int headIndex;

    for(int i=0; i<numRequest; i++){
        if(request[i] == initHead){
            headIndex = i;
            break;
        }
    }

    int totalSeekTime = 0;

    int currentHead = initHead;
    if(direction == 0){
        for(int i=headIndex; i>=0; i--){
            totalSeekTime += abs(currentHead - request[i]);
            currentHead = request[i];
            printf("->%d", request[i]);
        }
        for(int i=headIndex; i<numRequest; i++){
            totalSeekTime += abs(currentHead - request[i]);
            currentHead = request[i];
            printf("->%d", request[i]);
        }
    }else{
        for(int i=headIndex; i<numRequest; i++){
            totalSeekTime += abs(currentHead - request[i]);
            currentHead = request[i];
            printf("->%d", request[i]);
        }
        for(int i=headIndex-1; i>=0; i--){
            totalSeekTime += abs(currentHead - request[i]);
            currentHead = request[i];
            printf("->%d", request[i]);
        }
    }

    printf("total seektime: %d", totalSeekTime);

}