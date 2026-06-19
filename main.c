#include <stdio.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

int main()
{
    AddressBook addressBook;
    initialize(&addressBook);

    int choice;
    do {
        printf("\n===== ADDRESS BOOK CONTACTS =====\n");
        printf("1. Create Contact\n");
        printf("2. Search Contact\n");
        printf("3. Edit Contact\n");
        printf("4. Delete Contact\n");
        printf("5. List Contacts\n");
        printf("6. Save Contacts\n");
        printf("7. Exit\n");
        printf("=============================\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // clear invalid input
            printf("Invalid input. Try again.\n");
            continue;
        }
        getchar(); // consume newline

        switch (choice)
        {
            case 1:
                createContact(&addressBook);
                break;

            case 2:
                searchContact(&addressBook);
                break;

            case 3:
                editContact(&addressBook);
                break;

            case 4:
                deleteContact(&addressBook);
                break;

            case 5:
                listContacts(&addressBook);
                break;

            case 6:
                saveContactsToFile(&addressBook);
                printf("Contacts saved successfully.\n");
                break;

            case 7:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
                break;
        }

    } while (choice != 7);

    return 0;
}
