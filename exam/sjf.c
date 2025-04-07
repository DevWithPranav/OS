struct process {
    int pid;
    int at;
    int bt;
    int wt;
    int tt;
    int completed;
};

int main(){
    struct process p[10];

    int n;
    int completed = 0;
    int currentTime = 0;
    

    while(completed<n){

        int idx = -1;
        int minbt = __INT_MAX__;

        for (int i = 0; i < n; i++)
        {
            if(p[i].at <= currentTime & p[i].completed == 0){
                if(p[i].bt < minbt){
                    minbt = p[i].bt;
                    idx = i;
                }
            }
        }

        if(idx != -1){
            p[idx].wt = currentTime - p[idx].at;
            p[idx].tt = p[idx].wt + p[idx].bt;
            currentTime += p[idx].bt;
            p[idx].completed = 1;
            completed++;
        }else{
            completed++;
        }
        
    }
}