#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
void main(){
    int initHeadPos , numRequest;

    printf("Enter the current Heas Postion: ");
    scanf("%d", &initHeadPos);

    printf("Enter the number request: ");
    scanf("%d", &numRequest);

    int request[numRequest];
    bool completed[numRequest];
    for(int i=0; i<numRequest; i++){
        scanf("%d", &request[i]);
        completed[i] = false;
    }

    int totalSeekTime = 0;
    int nextRequest = initHeadPos;
    printf("%d",initHeadPos);
    for(int i=0; i<numRequest; i++){

        int minSeekTime = __INT_MAX__;
        int minIndex = -1;
        
        for(int j=0; j<numRequest; j++){
            if(completed[j] == false && (abs(nextRequest - request[j]) < minSeekTime)){
                minSeekTime = abs(nextRequest - request[j]);
                minIndex = j;
            }
        }

        if(minIndex == -1){
            break;
        }
        totalSeekTime += minSeekTime;
        nextRequest = request[minIndex];
        completed[minIndex] = true;
        printf("->%d", request[minIndex]);
    }

    printf("total head Movement: %d", totalSeekTime);
}