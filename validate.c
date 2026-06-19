#include <ctype.h>
#include <string.h>
#include "validate.h"

// Function to validate a name
// Returns 1 if valid, 0 if invalid
// Only allows alphabets and spaces
int is_valid_name(const char* name)
{
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (!isalpha(name[i]) && name[i] != ' ')
        {
            return 0; // Invalid character found
        }
    }
    return 1; // All characters valid
}

// Function to [validate a phone number
// Returns 1 if phone number is exactly 10 digits and all characters are digits
int is_valid_phone(const char* phone)
{
    int count = 0;
    for (int i = 0; phone[i] != '\0'; i++)
    {
        count++;
        if (!isdigit(phone[i]))
        {
            return 0; // Non-digit character found
        }
    }

    // Check if the number is exactly 10 digits
    if (count == 10)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Function to check if a phone number is unique in the address book
// Returns 1 if unique, 0 if duplicate exists
int is_unique_phone(AddressBook* addressBook, const char* phone)
{
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0)
            return 0; // Duplicate phone number found
    }
    return 1; // Phone number is unique
}

// Function to validate an email
// Returns 1 if valid, 0 if invalid

int is_valid_email(const char *email)
{
    if (email == NULL)
        return 0;

    int len = strlen(email);
    int at_index = -1;
    int has_lower_before_at = 0;

    if (len < 10) // minimum like a@gmail.com
        return 0;

    for (int i = 0; i < len; i++)
    {
        char ch = email[i];

        if (ch == '@')
        {
            if (at_index != -1 || i == 0 || i == len - 1)
                return 0;
            at_index = i;
        }
        else if (at_index == -1)
        {
            if (islower(ch))
                has_lower_before_at = 1;

            if (!(islower(ch) || isdigit(ch) || ch == '.'))
                return 0;
        }
    }

    if (at_index == -1 || !has_lower_before_at)
        return 0;

    const char *domain = email + at_index;
    if (strcmp(domain, "@gmail.com") != 0)
        return 0;

    return 1;
}


// Function to check if an email is unique in the address book
// Returns 1 if unique, 0 if duplicate exists
int is_unique_email(AddressBook* addressBook, const char* email)
{
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, email) == 0)
            return 0; // Duplicate email found
    }
    return 1; // Email is unique
} 
