#define _POSIX_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "list.h"

#define MAX 1000
#define SEP ";"
#define LEN 20

/*Das Prorgamm soll die eingelesenen Zeilen am Semikolon aufsplitten und in ein struct ablegen, welches du mit malloc allocierst*/

typedef struct contact {
  int index;
  char *name;
  char *telefonnumber;

}Contact;

Contact* contact_from_buffer (char *buffer);
void print_table (List *mylist);
int compare_by_index(List *mylist, void *value);
int compare_by_string(List *mylist, void *value);
void free_contact (void *data);
char *read_line (FILE *file, char *buffer);

int main (int argc, char **argv) {

  FILE *file;
  char buffer[MAX];
  char *buffer_ptr = buffer;
  int zeilenNummer = 0;
 // Contact *contact;

  if(argc <= 1)
  {
    printf("program needs path\n");
    exit(EXIT_FAILURE);
  }

  char *path;
  char filename []= "phonebook.csv";
//  size_t argumentLength = strlen(argv[1]);
//  size_t filenamLength = strlen(filename);
//  path = malloc(argumentLength + filenamLength + 1);
//  strncat(path, argv[1], argumentLength);
//  strncat(path, filename, filenamLength);

  path = g_build_filename (argv[1],
                           filename,
                           NULL);
  
  file = fopen (path, "r+");
  if (file == NULL) {
    printf ("Error opening file\n");
    exit(EXIT_FAILURE);
  }
  g_free (path);
  List *mylist = NULL;

  while (read_line(file,buffer) != NULL) {

    if (zeilenNummer != 0) {

        Contact *contact = contact_from_buffer (buffer);
        mylist = insert (mylist, contact);
      }
      
      zeilenNummer++;
    }
  

  // print table
  print_table (mylist);
  
  //list search
  int value = 1;
  
   mylist = list_search(mylist,compare_by_index,&value);

  //free list
   list_free_all(mylist,free_contact);

  fclose (file);

  return 0;
}

char *read_line (FILE *file, char *buffer) {
  int c, zaehler = 0;
  while (!feof (file)) {
    c = fgetc (file);

    *(buffer + zaehler) = (char) c;
    zaehler++;

    if (c == '\n') {
      *(buffer + zaehler) = '\0';

      return buffer;

    }

  }
  return NULL;
}

void free_contact (void *data)
{
	Contact *contact =(Contact*) data;
  free(contact->name);
  contact->name = NULL;
	free(contact->telefonnumber);
  contact->telefonnumber = NULL;
	free(contact);

}

int compare_by_index(List *mylist, void *value)
{	
	int index = *(int*) value;
	Contact *contact =(Contact*) mylist->data;
	if(index == contact->index)
	{
		printf("%i	%s	%s", contact->index, contact->name, contact ->telefonnumber);
		return 0;
	}	
		return 1;
}

int compare_by_string(List *mylist, void *value)
{
	char *string = (char*) value;
	Contact *contact =(Contact*) mylist->data;	
	if(strstr(contact->name,string) == 0)
	{
		printf("%i	%s	%s", contact->index, contact->name, contact ->telefonnumber);
		return 0;
	}
	else if (strstr(contact->telefonnumber,string))
	{
		printf("%i	%s	%s", contact->index, contact->name, contact ->telefonnumber);
		return 0;
		
	}
  return 1;
}
		


void print_contact(List *mylist)
{
	Contact *contact =(Contact*) mylist->data;
	printf("%10i| %-20s|%-25s|\n",contact->index, contact->name, contact->telefonnumber);
}

Contact* contact_from_buffer (char *buffer) {
  char *token;
  int tokenZaehler = 0;
  struct contact *contact = malloc(sizeof(Contact));
  token = strtok (buffer, SEP);
  while (token != NULL) {
    if( tokenZaehler == 0) {
      sscanf(token, "%i", &(contact->index));
    }
    if( tokenZaehler == 1) {
      sscanf(token, "%ms", &(contact->name));
    }
    if( tokenZaehler == 2) {
      contact->telefonnumber = malloc (strlen (token));
      sscanf(token, "%s", (contact->telefonnumber));
    }

    tokenZaehler++;

    token = strtok (NULL, SEP);
  }
  return contact;
}

void print_table (List *mylist){
  mylist = list_find_first(mylist);
  printf("================================================================\n");
  printf("Index     | Name                |Tel                      |\n");
  list_for_each(mylist,print_contact);
  printf("================================================================\n");

}



/**

 ==================================
 | Index |    Name     |   Tel    |
 |     1 | Peter       | 12234    |
 |     .. | ..         | ..       |
 ==================================

*/
