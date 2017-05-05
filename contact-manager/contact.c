#include "contact.h"
#include <stdio.h>

void print_contact (Contact *contact) {
  printf ("%i;%s;%s\n", contact->index, contact->name,
          contact->telefonnumber);
}

