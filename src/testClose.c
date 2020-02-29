#include "types.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]){
    int fd = 9; 
    printf(1,"testClose has been executed \n");
    // some random value which is going to be passed to open() and then to close()
    // this should give an exception
    close(fd);
    // This should print the execution thread of the close
}