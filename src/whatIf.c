#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "stat.h"

int fork1(void);  // Fork but panics on failure.
void panic(char*);

int main(int argc, char *argv[]){
  // to get the statistics of a file to allocate memory accordingly 
  struct stat st;
  //checking if file name is 
  char *filename;
  int inpFile = -1;
  
  //Checking if the file has been passed
  if (argc == 2){
    
    filename = argv[1];
    // Opening the file to be read on readonly mode
    inpFile = open(filename, O_RDONLY);
    if (inpFile == -1){
      // if the file is not found, then we need to print an error message and exit
      printf(2, "Failed to find the file %s\n",filename);
      exit();
    }
    // Creating the parent and child files regardless of input where they are write only with an option to create a new file
    int parentFile = open("parent.txt", O_WRONLY|O_CREATE);
    int childFile = open("child.txt", O_WRONLY|O_CREATE);
    stat(filename, &st);
    long size = st.size;
    char buf[size];
    // read from the file
    read(inpFile, buf, size);
    // create parallel processes to write into the file 
    if(fork1() == 0){
      write(childFile, buf, size);
    } else {
      write(parentFile,buf,size);
      wait();
    }
    close(inpFile);
    close(childFile);
    close(parentFile);
    free(buf);
  }
  else{
    //to take input from the console
    char buf[2048];
    // Creating the parent and child files regardless of input where they are write only with an option to create a new file
    int parentFile = open("parent.txt", O_WRONLY|O_CREATE);
    int childFile = open("child.txt", O_WRONLY|O_CREATE);
    // open the console to take input from the user in read write mode similar to sh.c
    int consoleOpen;
    consoleOpen = open("console", O_RDWR);
    if(consoleOpen >= 3){
      close(consoleOpen);
      }
    printf(1,"Enter content: ");
    gets(buf, sizeof(buf));
    int trueSize = strlen(buf) - 1;
  // create parallel processes to write into the file 
    if(fork1() == 0){
      write(childFile, buf, trueSize);
    } else {
      write(parentFile,buf, trueSize);
      wait();
    }
    close(consoleOpen);
    close(childFile);
    close(parentFile);
    free(buf);
  }
  return 0;
}

int
fork1(void)
{
  int pid;
  pid = fork();
  if(pid == -1)
    panic("fork");
  return pid;
}

void
panic(char *s)
{
  printf(2, "%s\n", s);
  exit();
}


