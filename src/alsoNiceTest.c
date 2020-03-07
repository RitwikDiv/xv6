#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "stat.h"

int main(int argc, char *argv[]){
    int pid = getpid();
    int cid = fork();
    if (cid < 0){
        printf(2,"%d couldn't fork",pid);
    }
    else if(cid > 0){
        printf(1,"pid %d created child pid %d \n",pid, cid);
        wait();
    }
    else{
        printf(1, "child pid %d \n", cid);
        for(int i = 0; i < 100000; i = i + 1){
            int x = x * 100;
        } 
    }
    kill(cid);
    kill(pid);
}