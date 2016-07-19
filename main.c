#define _POSIX_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000
#define SEP ";"
#define LEN 20

/*Das Prorgamm soll die eingelesenen Zeilen am Semikolon aufsplitten und ein ein struct ablegen, welches du mit malloc allocierst*/

typedef struct contact {
  int index;
  char *name;
  char *telefonnumber;

} Contact;

int main (int argc, char **argv) {

  FILE *file;
  char buffer[MAX];
  int c, i = 0, zaehler = 0;
  file = fopen ("phonebook.csv", "r+");
  if (file == NULL) {
    printf ("Error opening file\n");
    //error
  }


  while (!feof (file)) {
    c = fgetc (file);

    buffer[zaehler] = (char) c;
    zaehler++;

    if (c == '\n') {
      buffer[zaehler] = '\0';
      Contact contact;

      if (i != 0) {
        //printf ("%s", buffer);

        //sscanf(buffer, "%i;%s;%s", &contact.index, contact.name, contact.telefonnumber);

        char *token;

        //     strtok(buffer, SEP);

        char *currentToken;
        int tokenZaehler = 0;

        token = strtok_r (buffer, SEP, &currentToken);

        while (token != NULL) {
          if( tokenZaehler == 0) {
            sscanf(token, "%i", &contact.index);
          }
          if( tokenZaehler == 1) {
            sscanf(token, "%ms", &contact.name);
          }
          if( tokenZaehler == 2) {
            contact.telefonnumber = malloc (strlen (token));
            sscanf(token, "%s", contact.telefonnumber);
          }
          tokenZaehler++;

          token = strtok_r (NULL, SEP, &currentToken);
       }

        printf("%i %s %s\n", contact.index, contact.name, contact.telefonnumber);
      }
      zaehler = 0;
      i++;
    }
  }

  fclose (file);

  return 0;
}
	
