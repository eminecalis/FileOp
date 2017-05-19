//
// Created by sebastiangeiger on 31/03/17.
//

#include "contact-client.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <glib.h>
#include <string.h>
#include <wait.h>

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
  int exec_result = execve (args[0], args, NULL);
  if (exec_result == -1)
  {
   printf("Generator failed to start child process!\n");
   return EXIT_FAILURE ;
  }
 }
 else
 {
   close(write_channel[PIPE_READ]);
   close(read_channel[PIPE_WRITE]);
   //ask user --> typ, query
   // zuhause

   enum Type {NAME, TEL};

   enum Type type = NAME;
   char *command = "search_index";

   // send to generator

   //Command: <command>\n
   //<data>\n
   //\n

   char *data = "3";
   gchar *buffer = g_strdup_printf ("Command: %s\n%s\n",command,data);
   printf("%s\n",buffer);
   ssize_t write_elements = write(write_channel[PIPE_WRITE],buffer,strlen(buffer));
   //printf("%d\n",write_elements);
   //printf("%d\n",strlen(buffer));
   g_free (buffer);

   char readbuffer[1024] = {};
   read(read_channel[PIPE_READ],readbuffer,1024);
   //readbuffer[strstr (readbuffer, "\n")];
   printf("%s\n",readbuffer);

   //ask child to exit
   buffer = g_strdup_printf ("Command: exit\n");
   //printf("%s\n",buffer);
   write(write_channel[PIPE_WRITE],buffer,strlen(buffer));
   g_free (buffer);

   //wait for reply
   int status;
   wait(&status);
   //waitpid(pid, &status, 0);
   printf ("Child process endet mit: %d\n", WEXITSTATUS (status));
   //print
 }





 return 0;
}


