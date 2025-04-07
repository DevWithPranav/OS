#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    int pipe1[2], pipe2[2], pipe3[2];
    pipe(pipe1);
    pipe(pipe2);
    pipe(pipe3);
    
    if(fork() == 0){
        close(pipe3[0]);
        close(pipe3[1]);
        close(pipe2[0]);
        close(pipe1[1]);
        
        int numbers[5];
        read(pipe1[0], numbers, sizeof(numbers));
        
        write(pipe2[1], numbers , sizeof(numbers));
        
        return 0;
        
    }
    if(fork() == 0){
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe3[0]);
        close(pipe2[1]);
        int numbers[5];
        int sum = 0;
        read(pipe2[0], numbers, sizeof(numbers));
        for(int i=0;i<5;i++){
            sum+=numbers[i];
        }
        
        write(pipe3[1], &sum, sizeof(sum));
        return 0;
    }
    
    int numbers[5] = {1,2,3,4,5};
    close(pipe1[0]);
    close(pipe2[0]);
    close(pipe2[1]);
    close(pipe3[1]);
    
    write(pipe1[1], numbers, sizeof(numbers));
    
    int sum;
    read(pipe3[0], &sum, sizeof(sum));
    printf("sum: %d", sum);
    
    wait(NULL);
    wait(NULL);
    
    return 0;
}