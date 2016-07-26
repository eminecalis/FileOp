#define _POSIX_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000
#define SEP ";"
#define LEN 20

/*Das Prorgamm soll die eingelesenen Zeilen am Semikolon aufsplitten und in ein struct ablegen, welches du mit malloc allocierst*/

typedef struct contact {
  int index;
  char *name;
  char *telefonnumber;

} Contact;

typedef struct list{
	struct list *prev;
	struct list *next;
	 struct contact *data;
}List;

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

  while (!feof (file)) {
    c = fgetc (file);

    buffer[zaehler] = (char) c;
    zaehler++;

    if (c == '\n') {					// c ist ein Int wie kann man es direkt mit einem char vergleichen???
      buffer[zaehler] = '\0';

      List *mylist;
      

      if (zeilenNummer != 0) {
        //printf ("%s", buffer);

        //sscanf(buffer, "%i;%s;%s", &contact.index, contact.name, contact.telefonnumber);
        
        char *token;
       // char *currentToken;
        int tokenZaehler = 0;
        
        mylist = malloc(sizeof(List));
        mylist->data = malloc(sizeof(Contact));

        token = strtok (buffer, SEP);

        while (token != NULL) {
          if( tokenZaehler == 0) {
            struct contact* contact1 = mylist->data;
            sscanf(token, "%i", &(contact1->index));
          }
          if( tokenZaehler == 1) {
            sscanf(token, "%ms", &(mylist->data->name));
          }
          if( tokenZaehler == 2) {
            mylist->data->telefonnumber = malloc (strlen (token));
            sscanf(token, "%s", (mylist->data->telefonnumber));
          }
          tokenZaehler++;

          token = strtok (NULL, SEP);
       }
        mylist->next = NULL;
        mylist->prev = mylist;
        printf("%i %s %s\n", mylist->data->index, mylist->data->name, mylist->data->telefonnumber);
      }
      zaehler = 0;
      zeilenNummer++;
    
    }
 
  }

  fclose (file);

  return 0;
}
