//
// Created by sebastiangeiger on 31/03/17.
//

#include "contact-client.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define PIPE_READ 0
#define PIPE_WRITE 1


int main (int argc, char *argv[])
{
 int write_channel[2];
 pipe(write_channel);

 //ein pipe zum lesen
 int read_channel[2];
 pipe(read_channel);

 pid_t pid = fork();
 if(pid == 0)
 {
  close(write_channel[PIPE_WRITE]);
  dup2(write_channel[PIPE_READ],STDIN_FILENO);
  close(write_channel[PIPE_READ]);
  close(read_channel[PIPE_READ]);
  dup2(read_channel[PIPE_WRITE],STDOUT_FILENO);
  close(read_channel[PIPE_WRITE]);
  char *args[] = {"/home/sebastiangeiger/ClionProjects/FileOp/cmake-build-debug/contact-manager-generator", NULL};
  int exec_result = execve ("/home/sebastiangeiger/ClionProjects/FileOp/cmake-build-debug/contact-manager-generator", args,NULL);
  if (exec_result == -1)
  {
   printf("Generator failed to start child process!\n");
   return EXIT_FAILURE ;
  }
 }
 else
 {
  //ask user --> typ, query
  // zuhause

  enum Type {NAME, TEL};

  enum Type type = NAME;
  char *query = "Max";

  // send to generator


  //wait for reply

  //print
 }





 return 0;
}


