#include <stdio.h>

void main(){
    int initHeadPo;
    int numRequest;
    
    printf("Enter the initial Heas postion: ");
    scanf("%d", &initHeadPo);

    printf("Enter the number of request comming: ");
    scanf("%d", &numRequest);

    int request[numRequest];

    printf("Enter the request: ");
    for(int i=0; i<numRequest; i++){
        scanf("%d", &request[i]);
    }

    int totalSeekTime = 0;

    for(int i=0; i<numRequest; i++){

        int nextReq = request[i];
        int seekTime = 0;
        if(nextReq > initHeadPo){
            seekTime = nextReq - initHeadPo;
        }else{
            seekTime = initHeadPo - nextReq;
        }
       
        initHeadPo = nextReq;
        totalSeekTime += seekTime;
        printf("[%d]->", seekTime);

    }

    printf("total head postion: %d", totalSeekTime);
}