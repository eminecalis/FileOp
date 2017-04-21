//
// Created by sebastiangeiger on 31/03/17.
//
#define _XOPEN_SOURCE 500

#include "contact-generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include <glib.h>



int main (int argc, char *argv[])
{
  /*generate contacts
   zwei char *array  fuer namen
   und die ersten 4 nummern der tel nummer
   ungefaehr 100 kontakte mit einer
   Schleife
   speichere alle kontakte (als struct) in einer Liste

   Todo: erweitere den Teil mit den Nachnamen!
   */
   Contact *contact;
   char *names[] = {"Peter","Stephan","Martin","Paris","Marina"};
   GList *mylist = NULL;

   for (int i = 0; i <100; i++)
   {

     contact = malloc(sizeof(Contact));
     int indexName = random() % G_N_ELEMENTS(names);
     contact->name = names[indexName];
     char *telNumber;
     telNumber = malloc(4*sizeof(char));
     for(int j =0; j<4;j++)
     {
      snprintf (&telNumber[j],1,"%d",(int)(random()%10));
     }
     contact->telefonnumber = telNumber;
     contact->index =i+1;

     g_list_append (mylist, contact);
   }
  //wait for request

   char buffer[1024];
   char* bytesRead = fgets (buffer,1024,stdin);
   if(bytesRead == NULL)
   {
     printf("Error reading input\n");
     return EXIT_FAILURE;
   }
   size_t bufferLength = strlen(buffer);
   if ( buffer[bufferLength] != '\n')
   {
     // wird das naechste Mal behandelt
     return EXIT_FAILURE;
   }
   /* Parent schickt den
    *
    * <command>: "exit", "search_name", "search_number", "search_index"
    * <data>: "..."
    *
    * "COMMAND: <command>\n"
    * "<data>\n"
    * ""
    *
    */



  /*search contact
   * search funktion von der
   * doppel verketteten Liste adaptieren
   *
   * */

  //send respond
  return 0;
}
