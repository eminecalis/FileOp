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


GList *generate_contacts ();
gint find_contact_by_name (gconstpointer data, gconstpointer userdata);
gint find_contact_by_number (gconstpointer data, gconstpointer userdata);

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
  GList *mylist = generate_contacts ();

  //wait for request

  char buffer[1024];

  int running = 1;

  while(running) {
    char *bytesRead = fgets (buffer, 1024, stdin);  //um zu ueberpruefen ob die
    // funktion erfolgreich beendet wurde
    if (bytesRead == NULL) {
      printf ("Error reading input\n");
      return EXIT_FAILURE;
    }
    //COMMAND: SEARCH_NAME\n\0
    strtok (buffer, ":");
    char *token = strtok (NULL, ": ");
    token = strtok (token, "\n");

    if (strcmp (token, "search_name") == 0) {
      bytesRead = fgets (buffer, 1024, stdin);  //um zu ueberpruefen ob die
      // funktion erfolgreich beendet wurde
      if (bytesRead == NULL) {
        printf ("Error reading input\n");
        return EXIT_FAILURE;
      }
      token = strtok (buffer, "\n");
      GList *contact_item = g_list_find_custom (mylist, token,
                                                find_contact_by_name);
      if (contact_item == NULL) {
        printf ("Searched name not found\n");
        continue;
      }
      print_contact ((Contact *) contact_item->data);
    } else if (strcmp (token, "search_tel") == 0) {
      bytesRead = fgets (buffer, 1024, stdin);  //um zu ueberpruefen ob die
      // funktion erfolgreich beendet wurde
      if (bytesRead == NULL) {
        printf ("Error reading input\n");
        return EXIT_FAILURE;
      }
      token = strtok (buffer, "\n");
      GList *contact_item = g_list_find_custom (mylist, token,
                                                find_contact_by_number);
      if (contact_item == NULL) {
        printf ("Searched number not found\n");
        continue;
      }
      print_contact ((Contact *) contact_item->data);
    } else if (strcmp (token, "search_index") == 0) {

    } else if (strcmp (token, "exit") == 0) {
      running = 0;
    } else {
      printf ("Command not known\n");
      return EXIT_FAILURE;
    }
  }
    return EXIT_SUCCESS;
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

GList *generate_contacts () {
  char *names[] = { "Peter", "Stephan", "Martin", "Paris", "Marina" };
  GList *mylist = NULL;

  for (int i = 0; i < 100; i++) {
    Contact *contact;
    contact = malloc (sizeof (Contact));
    int indexName = random () % G_N_ELEMENTS(names);
    contact->name = names[indexName];
    char *telNumber;
    telNumber = malloc (5 * sizeof (char));

    snprintf (telNumber, 5, "%d%d%d%d", (int) (random () % 10),
              (int) (random () % 10), (int) (random () % 10),
              (int) (random () % 10));

    contact->telefonnumber = telNumber;
    contact->index = i + 1;

    mylist = g_list_append (mylist, contact);
  }
  return mylist;
}

gint find_contact_by_name (gconstpointer data, gconstpointer userdata) {
  Contact *contact = (Contact *) data;
  char *searched_name = (char *) userdata;
  if (strcmp (contact->name, searched_name) == 0) {
    return 0;
  } else
    return 1;
}
gint find_contact_by_number (gconstpointer data, gconstpointer userdata) {
  Contact *contact = (Contact *) data;
  char *searched_number = (char *) userdata;
  if (strcmp (contact->telefonnumber, searched_number) == 0) {
    return 0;
  } else
    return 1;
}

