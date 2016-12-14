#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>
#include <unistd.h>

#define LENGTH   80
typedef struct contact {
  int index;
  char *name;
  char *telefonnumber;
}Contact;

gint sort_by_name (gconstpointer a, gconstpointer contact2);
void print_table (GList *mylist);
void write_contact (gpointer data, gpointer user_data);

int main(int argc, char *argv[]) {

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
    contact->name = g_strndup (buffer,strlen(buffer)-1);
    printf("Telefonnumber: \n");
    fgets(buffer,LENGTH,stdin);
    contact->telefonnumber = g_strndup (buffer, strlen(buffer)-1);
    printf("Moechten Sie noch einen Contact eingeben? [J/n] \n");
    fgets(buffer,LENGTH,stdin);
    int morecontacts = (!g_strcmp0(buffer,"J\n")) || (!g_strcmp0 (buffer,"j\n")) || (!g_strcmp0 (buffer,"\n"));
    if(!morecontacts)
    {
      break;
    }
    index++;
  }

    //fgets(buffer,LENGTH,stdin);
    mylist = g_list_sort(mylist, sort_by_name);
    FILE *file = fopen(argv[1],"w+");
    g_list_foreach(mylist,write_contact,file);
    fclose (file);

    print_table (mylist);

return (EXIT_SUCCESS);
}
void write_contact (gpointer data, gpointer user_data)
{
  char *name = "Hello\n";
  FILE *file = user_data;
  fwrite(name,strlen(name),1,file);
}
gint sort_by_name (gconstpointer a, gconstpointer b)
{
    Contact *contact1 = (Contact *) a;
    Contact *contact2 = (Contact *) b;
    return g_strcmp0 (contact1->name, contact2->name);
}
void print_contact(gpointer data, gpointer user_data)
{
  Contact *contact =data;
  printf("%10i| %-20s|%-25s|\n",contact->index, contact->name, contact->telefonnumber);
}
void print_table (GList *mylist){

  printf("================================================================\n");
  printf("Index     | Name                |Tel                      |\n");
  g_list_foreach(mylist,print_contact,NULL);
  printf("================================================================\n");

}
