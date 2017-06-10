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

char *commands[] = {
  "search_name",
  "search_tel",
  "search_index"
};

enum SearchType {SEARCH_NAME, SEARCH_TEL, SEARCH_INDEX, SEARCH_ERROR};
enum MainType {MAIN_SEARCH, MAIN_EXIT, MAIN_ERROR};

void print_main_menu ();

enum MainType handle_main_menu ();

void print_search_menu ();

enum SearchType handle_search_menu ();

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

   enum MainType result = handle_main_menu ();
   char *command;
   char *data;
   gchar *buffer;
   gboolean searchMenu = TRUE;
   if (result == MAIN_SEARCH) {

     enum SearchType search_result = handle_search_menu ();
     while (search_result != SEARCH_ERROR) {

       handle_search_result (search_result, &data, &command);


       // send to generator

       //Command: <command>\n
       //<data>\n
       //\n
       buffer = g_strdup_printf ("Command: %s\n%s\n", command, data);
       printf ("%s\n", buffer);
       ssize_t write_elements = write (write_channel[PIPE_WRITE], buffer,
                                       strlen (buffer));
       //printf("%d\n",write_elements);
       //printf("%d\n",strlen(buffer));
       g_free (buffer);
       char readbuffer[1024] = {};
       read (read_channel[PIPE_READ], readbuffer, 1024);
       //readbuffer[strstr (readbuffer, "\n")];
       printf ("%s\n", readbuffer);
       break;
     }
   }
    else if( result == MAIN_EXIT)
   {
       command = "exit";
       //ask child to exit
       buffer = g_strdup_printf ("Command: %s\n", command);
       //printf("%s\n",buffer);
       write(write_channel[PIPE_WRITE],buffer,strlen(buffer));
       g_free (buffer);
   }

   //wait for reply
   int status;
   wait(&status);
   //waitpid(pid, &status, 0);
   printf ("Child process endet mit: %d\n", WEXITSTATUS (status));
   //print
 }

 return 0;
}

enum SearchType handle_search_menu () {
  print_search_menu ();
  char *search_index;
  scanf("%ms",&search_index);
  long index =strtol(search_index,NULL,10);
  enum SearchType result;
  if(index < 1 || index > 3)
    {
      result = SEARCH_ERROR;
    }else {
    result = (enum SearchType) (index - 1);
  }

  return result;
}

void print_search_menu () {
  printf("How do you want to search for contacts: \n");
  printf("[1] Search by Name.\n");
  printf("[2] Search by Telefonnumber.\n");
  printf("[3] Search by Index.\n");
  printf("Select a number>");
}

enum MainType handle_main_menu () {// 1. print menu
  print_main_menu ();

  // 2. read input from user
  char *menuChoice;
  scanf("%ms", &menuChoice);

  //menuChoice = malloc (100);
  //scanf("%s", menuChoice);

  // 3. parse index from input
  long index = strtol(menuChoice,NULL,10);
  enum MainType result;
  if(index < 1 || index > 2)
  {
    printf("Wrong choice\n");
    result = MAIN_ERROR;
  } else {
    result = (enum MainType) (index - 1);
  }

  return result;
}

void print_main_menu () {
  printf("Select an option: \n");
  printf("[1] Search for contact\n");
  printf("[2] Exit program\n");
  printf("Select a number>");
}

gboolean handle_search_result (enum SearchType search_result, char **data, char **command)
{
  switch (search_result) {
    case SEARCH_NAME:
      printf ("Name\n");
      *command = commands[SEARCH_NAME];
      printf ("Gesuchter Name:");
      scanf ("%ms", data);
      break;
    case SEARCH_TEL:
      printf ("Telnumber\n");
      *command = commands[SEARCH_TEL];
      printf ("Gesuchte Telefonnummer:");
      scanf ("%ms", data);
      break;
    case SEARCH_INDEX:
      printf ("Index\n");
      *command = commands[SEARCH_INDEX];
      printf ("Gesuchter Index:");
      scanf ("%ms", data);
      break;
    case SEARCH_ERROR:
      printf ("Wrong selection\n");
      return FALSE;
    default:
      printf ("Not implemented!\n");
      break;
  }
  return TRUE;
}

