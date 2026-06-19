#ifndef VALIDATE_H
#define VALIDATE_H

#include "contact.h"

int is_valid_name(const char *name);
//int isunique_name(AddressBook *addressBook, const char *name);

int is_valid_phone(const char *phone);
int is_unique_phone(AddressBook *addressBook, const char *phone);

int is_valid_email(const char *email);
int is_unique_email(AddressBook *addressBook, const char *email);

#endif  
