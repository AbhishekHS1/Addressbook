#include <stdio.h>
#include <string.h>
#include "contact.h"
#include "file.h"

#define DUMMY_COUNT 10  // number of dummy contacts

// =============================================================
// Function: saveContactsToFile
// Purpose : Save only user-created contacts (skip dummy)
// =============================================================
void saveContactsToFile(AddressBook *addressBook)
{
    FILE* fptr = fopen("contacts.csv", "w");
    if (fptr == NULL)
    {
        printf("Error opening file for writing");
        return;
    }

    // Save only non-dummy contacts
    int userCount = addressBook->contactCount - DUMMY_COUNT;
    if (userCount < 0)
        userCount = 0;
                                
    fprintf(fptr, "#%d#\n", userCount);

    for (int i = DUMMY_COUNT; i < addressBook->contactCount; i++)
    {
        fprintf(fptr, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fptr);
    printf("\n✅ Contacts saved successfully (only user-added contacts).\n");
}

// =============================================================
// Function: loadContactsFromFile
// Purpose : Load saved contacts *after* dummy contacts
// =============================================================
void loadContactsFromFile(AddressBook *addressBook)
{
    FILE* fptr = fopen("contacts.csv", "r");
    if (fptr == NULL)
    {
        // File doesn't exist yet — not an error, just skip loading
        return;
    }

    int count;
    if (fscanf(fptr, "#%d#\n", &count) != 1)
    {
        fclose(fptr);
        return;
    }

    // Store current number of dummy contacts
    int existingCount = addressBook->contactCount;

    // Load new contacts after dummy ones
    for (int i = 0; i < count; i++)
    {
        if (existingCount + i < MAX_CONTACTS)
        {
            fscanf(fptr, "%[^,],%[^,],%[^\n]\n",
                   addressBook->contacts[existingCount + i].name,
                   addressBook->contacts[existingCount + i].phone,
                   addressBook->contacts[existingCount + i].email);
            addressBook->contactCount++;
        }
    }

    fclose(fptr);
}
