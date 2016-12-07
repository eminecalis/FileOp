#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

#define LENGTH   80
typedef struct contact {
  int index;
  char *name;
  char *telefonnumber;
}Contact;



int main() {
  Contact *contact;
  char buffer[LENGTH];

  GList *mylist = NULL;

  while(1)
  {
    int index = 0;
    contact = malloc (sizeof(Contact));
    mylist = g_list_append (mylist,contact);
    contact->index = index;
    printf("Name: \n");
    fgets(buffer,LENGTH,stdin);
    contact->name = g_strdup (buffer);
    printf("Telefonnumber: \n");
    fgets(buffer,LENGTH,stdin);
    contact->telefonnumber = g_strdup (buffer);
    printf("Moechten Sie noch einen Contact eingeben? [J/n] \n");
    fgets(buffer,LENGTH,stdin);
    int morecontacts = (!g_strcmp0(buffer,"J\n")) || (!g_strcmp0 (buffer,"j\n")) || (!g_strcmp0 (buffer,"\n"));
    if(!morecontacts)
    {
      break;
    }
    index++;
  }
  while(mylist != NULL)
  {
    fgets(buffer,LENGTH,stdin);
    mylist = g_list_sort(mylist,GCompareFunc(mylist,buffer));

    mylist = mylist->next;
  }

return (EXIT_SUCCESS);
}

