#define _POSIX_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int main (int argc, char **argv) {

  FILE *file;
  char buffer[MAX];
  int c, zeilenNummer = 0, zaehler = 0;
 // Contact *contact;
  
  
  file = fopen ("phonebook.csv", "r+");
  if (file == NULL) {
    printf ("Error opening file\n");
    //error
  }
  List *mylist = NULL;
  while (!feof (file)) {
    c = fgetc (file);

    buffer[zaehler] = (char) c;
    zaehler++;

    if (c == '\n') {					// c ist ein Int wie kann man es direkt mit einem char vergleichen???
      buffer[zaehler] = '\0';

      if (zeilenNummer != 0) {

        Contact *contact = contact_from_buffer (buffer);
        mylist = insert (mylist, contact);
      }
      zaehler = 0;
      zeilenNummer++;
    }
  }

  // print table
  print_table (mylist);

  fclose (file);

  return 0;
}
List *compare_by_index(List *mylist, void *value)
{	
	int index = *(int*) value;
	Contact *contact =(Contact*) mylist->data;
	if(index == contact->index)
	{
		return mylist;
		printf("%i	%s	%s", contact->index, contact->name, contact ->telefonnumber);
	}	
		
}

List *compare_by_name(List *mylist, void *value)
{
	char *name = (char*) value;
	Contact *contact =(Contact*) mylist->data;	
	if(strstr(contact->name,name))
	{
		return mylist;
		printf("%i	%s	%s", contact->index, contact->name, contact ->telefonnumber);
	}	
}

List *compare_by_number(List *mylist, void *value)
{
	char *telefonnumber =(char*)value;
	Contact *contact =(Contact*) mylist->data;
	if(strstr(contact->telefonnumber,telefonnumber))
	{
		return mylist;
		printf("%i	%s	%s", contact->index, contact->name, contact ->telefonnumber);
	}	
		
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
