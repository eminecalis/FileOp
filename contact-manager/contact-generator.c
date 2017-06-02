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
gint find_contact_by_index (gconstpointer data, gconstpointer userdata);
gboolean handle_search_name(GList *mylist);
gboolean handle_search_number(GList *mylist);
gboolean handle_search_index(GList *mylist);

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

      gboolean result = handle_search_name(mylist);

      if (result == FALSE) {
        fprintf (stderr, "Error in Handle Command 'search_name'\n");
      }

    } else if (strcmp (token, "search_tel") == 0) {

      gboolean result = handle_search_number(mylist);
      if (result == FALSE) {
        fprintf (stderr, "Error in Handle Command 'search_number'\n");
      }

    } else if (strcmp (token, "search_index") == 0) {

      gboolean result = handle_search_index (mylist);
      if(result == FALSE) {
        fprintf (stderr,"Error in Handle Command 'search_index'\n");
      }

    } else if (strcmp (token, "exit") == 0) {
      running = 0;
    } else {
      printf ("Command not known\n");
      return EXIT_FAILURE;
    }

    fflush (stdout);
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

gint find_contact_by_index (gconstpointer data, gconstpointer userdata) {
  Contact *contact = (Contact *) data;
  int * search_index_pointer = (int *) userdata;
  int searched_index = *search_index_pointer;
  if(searched_index == contact->index) {
    return 0;
  } else
    return 1;
}

gboolean handle_search_name(GList *mylist)
{
  char buffer[1024];
  char *line = fgets (buffer, 1024, stdin);  //um zu ueberpruefen ob die
  // funktion erfolgreich beendet wurde
  if (line == NULL) {
    printf ("Error reading input\n");
    return FALSE;
  }
  char *token = strtok (buffer, "\n");

  GCompareFunc compareFunction = find_contact_by_name;

  GList *contact_item = g_list_find_custom (mylist, token,
                                            compareFunction);
  if (contact_item == NULL) {
    printf ("Searched name not found\n");
    return TRUE;
  }
  print_contact ((Contact *) contact_item->data);
  fflush (stdout);
  return TRUE;
}

gboolean handle_search_number(GList *mylist)
{
  char buffer[1024];

  char *line = fgets (buffer, 1024, stdin);  //um zu ueberpruefen ob die
  // funktion erfolgreich beendet wurde
  if (line == NULL) {
    fprintf (stderr, "Error reading input\n");
    return FALSE;
  }
  char *token = strtok (buffer, "\n");
  GList *contact_item = g_list_find_custom (mylist, token,
                                            find_contact_by_number);
  if (contact_item == NULL) {
    fprintf (stderr,"Searched number not found\n");
    return TRUE;
  }
  print_contact ((Contact *) contact_item->data);
  return TRUE;
}

gboolean handle_search_index(GList *mylist)
{
  char buffer [1024];
  int searched_value;
  char *line = fgets(buffer,1024,stdin);
  if(line == NULL)
  {
    fprintf (stderr,"Error reading input\n");
    return FALSE;
  }
  char *token = strtok (buffer, "\n");

  int *searched_value_pointer;
  searched_value_pointer = &searched_value;
  int test_search = sscanf(token,"%d",searched_value_pointer);
  if(test_search == 0)
  {
    fprintf (stderr, "Wrong format\n");
    return FALSE;
  }

  GList *contact_item =g_list_find_custom (mylist,searched_value_pointer,find_contact_by_index);

  if(contact_item == NULL)
  {
    fprintf(stderr,"Searched index not found\n");
    return TRUE;          //spielt keine Rolle ob das Element gefunden wurde,
                          // der einzige Fehlerfall passiert bei der Eingabe!
  }
  print_contact ((Contact *)contact_item->data);
  return TRUE;
}
