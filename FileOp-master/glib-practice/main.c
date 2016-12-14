#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <glib.h>

#define LENGTH   80
typedef struct contact {
  int index;
  char *name;
  char *telefonnumber;
}Contact;

gint sort_by_name (gconstpointer a, gconstpointer b);
gint sort_by_index (gconstpointer a, gconstpointer b);
GList *write_contact (GList *mylist);

int main() {
  Contact *contact;
  char buffer[LENGTH];

  GList *mylist = NULL;
  int index = 0;
  while(1)
  {

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
    FILE *file;

    mylist = g_list_sort(mylist,sort_by_index);

  print_table(mylist);
  fclose(file);
return (EXIT_SUCCESS);
}

gint sort_by_name (gconstpointer a, gconstpointer b)
{
    Contact *contact1 = (Contact *) a;
    Contact *contact2 = (Contact *) b;
    return g_strcmp0(contact1->name,contact2->name);

}
gint sort_by_index (gconstpointer a, gconstpointer b)
{
    Contact *contact1 = (Contact *) a;
    Contact *contact2 = (Contact *) b;
    return contact1->index-contact2->index;
}

GList *write_contact (GList *mylist)
{
  FILE *file = fopen("myphonebook.csv","w+");
  write(file,g_strndup(stdin,strlen(stdin)-1),strlen(stdin)-1);

}

void print_contact(GList *mylist, void *data)
{
  Contact *contact =(Contact*) mylist->data;
  printf("%10i| %-20s|%-25s|\n",contact->index, contact->name, contact->telefonnumber);
}

void print_table (GList *mylist){

  printf("================================================================\n");
  printf("Index     | Name                |Tel                      |\n");
  g_list_foreach(mylist,print_contact,mylist->data);
  printf("================================================================\n");

}



