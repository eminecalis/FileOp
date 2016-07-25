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
	 struct contact* data;	
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
    //  Contact *contact;
      List *mylist;
      

      if (zeilenNummer != 0) {
        //printf ("%s", buffer);

        //sscanf(buffer, "%i;%s;%s", &contact.index, contact.name, contact.telefonnumber);
        
        char *token;
       // char *currentToken;
        int tokenZaehler = 0;
        
        mylist = malloc(sizeof(List));
        token = strtok (buffer, SEP);

        while (token != NULL) {
          if( tokenZaehler == 0) {
            sscanf(token, "%i", &(List->data->index)); 
          }
          if( tokenZaehler == 1) {
            sscanf(token, "%ms", &(List->data->name); 
          }
          if( tokenZaehler == 2) {
            contact->telefonnumber = malloc (strlen (token));
            sscanf(token, "%s", (List->data->telefonnumber);
          }
          tokenZaehler++;

          token = strtok (NULL, SEP);
       }
        List->next = mylist;
        List->prev = NULL;
        printf("%i %s %s\n", contact->index, contact->name, contact->telefonnumber);
      }
      zaehler = 0;
      zeilenNummer++;
    
    }
 
  }

  fclose (file);

  return 0;
}
