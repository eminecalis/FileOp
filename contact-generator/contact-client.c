//
// Created by sebastiangeiger on 14/02/17.
//

#include "contact-client.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PIPE_READ 0
#define PIPE_WRITE 1

int main(){

  int write_pipe[2];
  printf("%d  %d\n", write_pipe[PIPE_READ],write_pipe[PIPE_WRITE]);
  pipe(write_pipe);
  printf(" Write Pipe: %d  %d\n", write_pipe[PIPE_READ],write_pipe[PIPE_WRITE]);

  int read_pipe[2];
  pipe(read_pipe);
  printf("Read Pipe: %d  %d\n", read_pipe[PIPE_READ],read_pipe[PIPE_WRITE]);


  pid_t pid = fork();

  if(pid == 0)
  {
    close(write_pipe[PIPE_WRITE]);
    close(read_pipe[PIPE_READ]);
    printf("You are in child process\n");
    pid_t ownId = getpid();
    pid_t parentId = getppid();
    printf("[child] Process Id of child: %d\n", ownId);
    printf("[child] Process Id of parent: %d\n", parentId);
    char buffer[1024];// = {};
    long count = read(write_pipe[PIPE_READ],buffer,1024);
    buffer[count]='\0';
    printf("child: %s\n", buffer);
    char *childMessage = "Hallo Parent";
    write(read_pipe[PIPE_WRITE], childMessage, strlen(childMessage)+1);
    close(write_pipe[PIPE_READ]);
    close(read_pipe[PIPE_WRITE]);
  }
  else
  {
    close(write_pipe[PIPE_READ]);
    close(read_pipe[PIPE_WRITE]);
    printf("You are in parent process\n");
    pid_t ownId = getpid();
    pid_t parentId = getppid();
    printf("[parent] Process Id of child: %d\n", pid);
    printf("[parent] Process Id of this process: %d\n", ownId);
    printf("[parent] Process Id of  parent: %d\n", parentId);

    char *message = "Hallo Emine";
    write(write_pipe[PIPE_WRITE],message,strlen(message)+1);
    char buffer[1024];// = {};
    long count = read(read_pipe[PIPE_READ],buffer,1024);
    buffer[count]='\0';
    printf("parent: %s\n", buffer);
    close(write_pipe[PIPE_WRITE]);
    close(read_pipe[PIPE_READ]);
    int status;
    wait(&status);
  }


}
