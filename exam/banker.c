#include <stdio.h>
#include <stdbool.h>

// Available = {3, 3, 2}

// Allocation:
// P0: {0, 1, 0}
// P1: {2, 0, 0}
// P2: {3, 0, 2}

// Max:
// P0: {7, 5, 3}
// P1: {3, 2, 2}
// P2: {9, 0, 2}

// Need = Max - Allocation:
// P0: {7, 4, 3}
// P1: {1, 2, 2}
// P2: {6, 0, 0}

void main()
{
    int Available[] = {3, 3, 2};
    int allocation[20][20];
    int max[20][20];
    int need[20][20];

    int P, R;

    printf("Enter the number of process: ");
    scanf("%d", &P);
    printf("Enter the number of reaourse: ");
    scanf("%d", &R);

    printf("Enter the allocation matrix: ");
    for (int i = 0; i < P; i++)
    {
        printf("Enter the resources for p[%d]: ", i);
        for (int j = 0; j < R; j++)
        {

            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the max matrix: ");
    for (int i = 0; i < P; i++)
    {
        printf("Enter the resources for p[%d]: ", i);
        for (int j = 0; j < R; j++)
        {

            scanf("%d", &max[i][j]);
        }
    }

    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < R; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    int work[R];
    int safe[P];
    bool finsh[P];

    for (int i = 0; i < R; i++)
    {
        work[i] = Available[i];
    }

    for (int i = 0; i < P; i++)
    {
        finsh[i] = false;
    }

    int count = 0;
    while (count < P)
    {
        int found = 0;

        for (int i = 0; i < P; i++)
        {
            if (!finsh[i])
            {
                int j;
                for (j = 0; j < R; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        break;
                    }
                }

                if (j == R)
                {
                    for (int k = 0; k < R; k++)
                    {
                        work[k] += allocation[i][k];
                    }
                    safe[count++] = i;
                    found = 1;
                    finsh[i] = true;
                }
            }
        }

        if (found == 0)
        {
            printf("no safe");
            return;
        }
    }

    printf("is safe");
    return;
}
int reqestResource(int process, int reqest[R]){
    for(int i = 0; i<R; i++){
       if(reqest[i]> need[process][i] || reqest[i] > avalaible[i]){
          return 0;
       }
    }
    
    for(int i=0; i<R; i++){
       avalaible[i] -= reqest[i];
       allocation[process][i] += reqest[i];
       need[process][i] -= reqest[i];
    }
    
    if(isSafe()){
      return 1;
    }
    return 1;
}