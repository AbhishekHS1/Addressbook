#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "contact.h"
#include "validate.h"
#include "file.h"
#include "populate.h"
// Function to display all contacts in the address book
void listContacts(AddressBook *addressBook)
{ 
    if (addressBook->contactCount == 0) // Check if there are any contacts
    {
        printf("\nNo contacts available.\n");
        return;
    }

    printf("\n---- CONTACT LIST ----\n");

    for (int i = 0; i < addressBook->contactCount; i++)  // Loop through all contacts
    {
        printf("\nContact Info %d:\n", i + 1);
        printf("Name: %s\n", addressBook->contacts[i].name);
        printf("Phone_no: %s\n", addressBook->contacts[i].phone);
        printf("Email: %s\n", addressBook->contacts[i].email);
    }
}
// Function to initialize the address book
void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;

    // First add dummy contacts
    populateAddressBook(addressBook);

    // Then add saved contacts from file
    loadContactsFromFile(addressBook);
}

// Function to save contacts to file and exit program
void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program
}

// Function to create and add a new contact
void createContact(AddressBook *addressBook)
{
    if (addressBook->contactCount >= 100)  // Check address book capacity
    {
        printf("Address book is full. Cannot add more contacts!\n");
        return;
    }
    char temp_name[35];
    char temp_phone[15];
    char temp_email[35];
    // Input and validate name
    while(1)
    {
        printf("Enter the Name: ");
        scanf(" %[^\n]",temp_name);
        getchar();

        if(!is_valid_name(temp_name))  // Validate the Name
        {
            printf("\nName not valid. Use only letters and spaces.\n");

        }
        else
        {
            break;
        }
    }
    strcpy(addressBook->contacts[addressBook->contactCount].name, temp_name);  // create the name by using strcpy()

    while(1)
    {
        printf("Enter the Phone_No: ");
        scanf(" %[^\n]",temp_phone);
        getchar();

        if(!is_valid_phone(temp_phone))  // Validate the Phone_no
        {
            printf("\nInvalid number. Please enter exactly 10 digits.\n");

        }
        else if(!is_unique_phone(addressBook,temp_phone))  // check wheather the number is unique or not
        {
            printf("\nThis name already exists. Please enter a unique one.\n");
        }
        else
        {
            break;
        }
    }
    strcpy(addressBook->contacts[addressBook->contactCount].phone, temp_phone);  // create the phone_no by using strcpy()

    while(1)
    {
        printf("Enter the Email: ");
        scanf(" %[^\n]",temp_email);
        getchar();

        if(!is_valid_email(temp_email))  // Validate the email
        {
          printf("\nInvalid email! Use lowercase letters, numbers before '@', and only one '.' after it.\n");
        }
        else if(!is_unique_email(addressBook,temp_email))  // check wheather the email is unique or not
        {
            printf("\nThis email already exists. Please use a different one.\n");
        }
        else
        {
            break;
        }
    }
    strcpy(addressBook->contacts[addressBook->contactCount].email, temp_email);  // create the email by using strcpy()

    addressBook->contactCount++; // Increment contact count
    printf("\n----Contact created Successfully----\n");      
}
 // Function to search for a contact
void searchContact(AddressBook *addressBook)
{
    int choice;
    int found;
    char temp_name[35];
    char temp_phone[15];
    char temp_email[35];
    do
    {           
        // Display search menu
        printf("\nSearch Menu:\n");
        printf("1. Search by Name\n");
        printf("2. Search by Phone_no\n");
        printf("3. Search by Email\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1: // Search by name
            while(1)
            {
                printf("\nEnter the name you want to search: ");
                scanf(" %[^\n]",temp_name);
                getchar();

                if(!is_valid_name(temp_name))  // Validate the Name
                {
                    printf("\nInvalid name! Use only letters and spaces.\n");
                }
                else
                {
                    break;
                }
            }

            found = 0;
            for(int i = 0 ; i < addressBook->contactCount ; i++)
            {
                if(strcmp(addressBook->contacts[i].name,temp_name) == 0)
                {
                    printf("\nName: %s\n",addressBook->contacts[i].name);
                    printf("Phone_no: %s\n",addressBook->contacts[i].phone);
                    printf("Email: %s\n",addressBook->contacts[i].email);
                    found = 1;
                    choice = 4; // Exit after finding
                }
            }
            if(found == 0)
            {
                printf("\nThe requested contact could not be located in the directory.\n");
            }
            break; 
        case 2: // Search by phone
            while(1)
            {
                printf("\nEnter the phone number to search: ");
                scanf(" %[^\n]",temp_phone);
                getchar();

                if(!is_valid_phone(temp_phone))  // Validate the Phone_no
                {
                    printf("\nInvalid number! Please enter exactly 10 digits.\n");
                }
                else
                {
                    break;
                }
            }

            found = 0;
            for(int i = 0 ; i < addressBook->contactCount ; i++)
            {
                if(strcmp(addressBook->contacts[i].phone,temp_phone) == 0)
                {
                    printf("\nName: %s\n",addressBook->contacts[i].name);
                    printf("Phone_no: %s\n",addressBook->contacts[i].phone);
                    printf("Email: %s\n",addressBook->contacts[i].email);
                    found = 1;
                    choice = 4;
                }
            }
            if(found == 0)
            {
                printf("\nSearched contact is not found\n");
            }
            break;
        case 3: // Search by email
            while(1)
            {
                printf("\nType the email you want to find: ");
                scanf(" %[^\n]",temp_email);
                getchar();

                if(!is_valid_email(temp_email))  // Validate the email
                {
                     printf("\nInvalid email! Use lowercase letters, digits before '@', and only one '.' after '@'.\n");
                }
                else
                {
                    break;
                }
            }

            found = 0;
            for(int i = 0 ; i < addressBook->contactCount ; i++)
            {
                if(strcmp(addressBook->contacts[i].email,temp_email) == 0)
                {
                    printf("\nName: %s\n",addressBook->contacts[i].name);
                    printf("Phone_no: %s\n",addressBook->contacts[i].phone);
                    printf("Email: %s\n",addressBook->contacts[i].email);
                    found = 1;
                    choice = 4;
                }
            }
            if(found == 0)
            {
                printf("\nSearched contact is not found\n");
            }
            break;
        case 4: // Exit search menu
            break;
        default:
            printf("\nInvalid choice. Please try again.\n");
        }
    } while (choice != 4);
    
}
// Function to edit an existing contact
void editContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0) // Check if contacts exist
    {
        printf("\nNo contacts available to edit.\n");
        return;
    }

    int Searchchoice;
    int INDEX = -1;
    char key[50];

    // Step 1: Search for the contact to edit
    do
    {
        printf("\nSearch contact to edit by:\n");
        printf("1. Name\n");
        printf("2. Phone Number\n");
        printf("3. Email\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &Searchchoice);
        getchar();

        switch (Searchchoice)
        {
        case 1: // Search by name
            printf("Enter the name: ");
            scanf(" %[^\n]", key);
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].name, key) == 0)
                {
                    INDEX = i;
                    break;
                }
            }
            break;   

        case 2: // Search by phone
            printf("Enter the phone number: ");
            scanf(" %[^\n]", key);
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].phone, key) == 0)
                {
                    INDEX = i;
                    break;
                }
            }
            break;

        case 3: // Search by email
            printf("Enter the email: ");
            scanf(" %[^\n]", key);
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].email, key) == 0)
                {
                    INDEX = i;
                    break;
                }
            }
            break;

        case 4:
            printf("Returning to main menu...\n");
            return;

        default:
            printf("Invalid choice. Try again.\n");
        }

        if (INDEX == -1 && Searchchoice != 4)
            printf("\nNo matching contact found.\n");

    } while (INDEX == -1 && Searchchoice != 4);

    if (INDEX == -1)
        return;

    // Step 2: Edit selected contact
    int editChoice;
    do
    {
        printf("\nEdit Contact Details:\n");
        printf("Name: %s\n", addressBook->contacts[INDEX].name);
        printf("Phone: %s\n", addressBook->contacts[INDEX].phone);
        printf("Email: %s\n", addressBook->contacts[INDEX].email);

        printf("\n1. Edit Name\n");
        printf("2. Edit Phone Number\n");
        printf("3. Edit Email\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &editChoice);
        getchar();

        switch (editChoice)
        {
        case 1: // Edit name
        {
            char newName[35];
            printf("Enter new name: ");
            scanf(" %[^\n]", newName);
            if (is_valid_name(newName))
            {
                strcpy(addressBook->contacts[INDEX].name, newName);
                printf("Name has been updated successfully.\n");
            }
            else
                printf("Name not valid. Use letters and spaces only.\n");
            break;
        }

        case 2: // Edit phone number
        {
            char newPhone[15];
            printf("Enter new phone number: ");
            scanf(" %[^\n]", newPhone);
            if (is_valid_phone(newPhone) && is_unique_phone(addressBook, newPhone))
            {
                strcpy(addressBook->contacts[INDEX].phone, newPhone);
                printf("Phone number has been updated successfully.\n");
            }
            else
                printf("Phone number not valid or already used.\n");
            break;
        }

        case 3: // Edit email
        {
            char newEmail[35];
            printf("Enter new email: ");
            scanf(" %[^\n]", newEmail);
            if (is_valid_email(newEmail) && is_unique_email(addressBook, newEmail))
            {
                strcpy(addressBook->contacts[INDEX].email, newEmail);
                printf("Email has been updated successfully.\n");
            }
            else
                printf("Email not valid or already used.\n");
            break;
        }

        case 4: // Exit edit menu
            printf("Returning to main menu...\n");
            break;

        default:
            printf("Invalid choice. Try again.\n");
        }

    } while (editChoice != 4);
}
// Function to delete a contact
void deleteContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0) // Check if list is empty
    {
        printf("\nThere are no contacts to delete.\n");
        return;
    }

    int Choice, flag = 0;
    char temp_name[35], temp_phone[15], temp_email[35];
// Display delete options
    printf("\nDelete contact using:\n");
    printf("1. Name\n");
    printf("2. Phone Number\n");
    printf("3. Email\n");
    printf("4. Exit\n");
    printf("Enter your Choice: ");
    scanf("%d", &Choice);
    getchar();

    switch (Choice)
    {
    case 1: // Delete by Name
        printf("\nEnter the Name to delete: ");
        scanf(" %[^\n]", temp_name);
        getchar();

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].name, temp_name) == 0)
            {
                flag = 1;
                for (int j = i; j < addressBook->contactCount - 1; j++)
                {
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                }
                addressBook->contactCount--;
                printf("\nContact deleted successfully.\n");
                break;
            }
        }
        break;  

    case 2: // Delete by Phone Number
        printf("\nEnter the Phone Number to delete: ");
        scanf(" %[^\n]", temp_phone);
        getchar();

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].phone, temp_phone) == 0)
            {
                flag = 1;
                for (int j = i; j < addressBook->contactCount - 1; j++)
                {
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                }
                addressBook->contactCount--;
                printf("\nContact has been deleted successfully.\n");
                break;
            }
        }
        break;

    case 3: // Delete by Email
        printf("\nEnter the Email to delete: ");
        scanf(" %[^\n]", temp_email);
        getchar();

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].email, temp_email) == 0)
            {
                flag = 1;
                for (int j = i; j < addressBook->contactCount - 1; j++)
                {
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                }
                addressBook->contactCount--;
                printf("\nContact has been deleted successfully.\n");
                break;
            }
        }
        break;

    case 4: // Exit delete menu
        printf("\nReturning to main menu...\n");
        return;

    default:
        printf("\nInvalid choice.\n");
        return;
    }

    if (!flag)
    {
        printf("\nContact not found.\n");
    }
}