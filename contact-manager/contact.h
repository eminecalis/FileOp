//
// Created by sebastiangeiger on 21/04/17.
//

#ifndef FILEOP_CONTACT_H
#define FILEOP_CONTACT_H

typedef struct contact {
  int index;
  char *name;
  char *telefonnumber;
}Contact;

void print_contact (Contact *contact);
#endif //FILEOP_CONTACT_H
