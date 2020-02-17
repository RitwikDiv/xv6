#include "types.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]){
  
  //checking if file name is 
  char *filename;
  int inpFile = -1;
  
  // taking input from the file 
  char buf[1028];

    // Creating the parent and child files regardless of input where they are write only with an option to create a new file
  int parentFile = open("parent.txt", O_WRONLY|O_CREATE);
  int childFile = open("child.txt", O_WRONLY|O_CREATE);
  
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
    // read from the file
    read(inpFile, buf, sizeof(buf));
    // create parallel processes to write into the file 
    if(fork() == 0){
      write(childFile, buf, sizeof(buf)-1);
    } else {
      write(parentFile,buf,sizeof(buf)-1);
    }
    close(inpFile);
  }
  else{
    // open the console to take input from the user in read write mode similar to sh.c
    int consoleOpen;
    while((consoleOpen = open("console", O_RDWR)) >= 0){
    printf(2,"Enter content: ");
    if(consoleOpen >= 3){
      close(consoleOpen);
      break;
      }
    }
    // create a buffer and set memory and get the input from the user
    memset(buf, 0, sizeof(buf));
    gets(buf, sizeof(buf));

  // create parallel processes to write into the file 
    if(fork() == 0){
      write(childFile, buf, sizeof(buf)-1);
    } else {
      write(parentFile,buf,sizeof(buf)-1);
    }
    close(consoleOpen);
  }
  close(childFile);
  close(parentFile);
  return 0;
}


