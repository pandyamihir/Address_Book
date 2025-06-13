/*header file declaration*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

static int z=0;

/*function for list the contact*/
void listContacts(AddressBook *addressBook) 
{
    int index=1;
    printf("Listing Contacts:\n");
    printf("************************************************************\n");
    printf("Index\t   Name\t\t  Number\t   Email-id\t\n");
    printf("************************************************************\n");
    
    /*printing contacts*/
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%-8d%-16s%-15s%-5s\n", index,
        addressBook->contacts[i].name,
        addressBook->contacts[i].phone,
        addressBook->contacts[i].email);
        index++;
    }

    printf("************************************************************\n");
}

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

/*function for save & exit*/
void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

/*function for create contact*/
void createContact(AddressBook *addressBook)
{
    /*variable declaration*/
    Contact add;

    /* Read name from the user */
    printf("Enter name: ");
    scanf(" %[^\n]", add.name);
        
    /* Read number from the user */
    printf("Enter the phone number: ");
    scanf("%s", add.phone);
    
    int l = 0; // String length
    while(add.phone[l] != '\0')
    {
        l++;
    }
    
    /* Check number is valid or not */
    int count = 0;
    if(l == 10)
    {
        for(int i = 0; add.phone[i] != '\0'; i++)
        {
            if(add.phone[i] >= '0' && add.phone[i] <= '9')
            {
                count++;
            }
        }
    }
    else
    {
        printf("Invalid Number.\n");
        return;
    }
        
    /*checking unique number*/
    int u=0;
    if(count == 10)
    {
        for(int i=0; i < addressBook->contactCount; i++)
        {
            if(strcmp(addressBook->contacts[i].phone, add.phone)==0)
            u=1;
        }
    }
    if(u==1)
    {
        printf("Invalid\n");
        return;
    }
        
    /* Read mail id from the user */
    printf("Enter e-mail id: ");
    scanf("%s", add.email);
    
    /* Check email is valid or not */
    int flag = 0;
    for(int i = 0; add.email[i] != '\0'; i++)
    {
        if(add.email[i] == '@')
        {
            for(int j = i + 1; add.email[j] != '\0'; j++)
            {
                if(add.email[j] == '.' && add.email[j + 1] == 'c' && add.email[j + 2] == 'o' && add.email[j + 3] == 'm')
                {
                    flag = 1;
                }
                else if(add.email[j] == '.' && add.email[j + 1] == 'i' && add.email[j + 2] == 'n')
                {
                    flag=1;
                }
            }
        }   
    }
        
    if(flag != 1)
    {
        printf("Invalid Email\n");
        return;
    }
    
    /*storing new contact data*/
    addressBook->contacts[addressBook->contactCount++] = add;
    printf("Contact created successfully.\n");
}

/*function for search the contact*/
void searchContact(AddressBook *addressBook) 
{
    int select; //variable declaration
    
    /*read the choice from the user*/
    printf("1. By name\n2. By number\n3. By email id\n");
    printf("Select : ");
    scanf("%d", &select);
    printf("\n");
        
    switch(select)
    {
        /*seach contact by name*/
        case 1:
        {
            char searchName[50];
            printf("Enter name : ");
            scanf(" %[^\n]", searchName);
                
            int found = 0, j = 0;
            
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strstr(addressBook->contacts[i].name, searchName)!=NULL)
                {
                    if(j == 0)
                    {
                        printf("Contact found:\n");
                        printf("************************************************************\n");
                        printf("Index\t   Name\t\t  Number\t   Email-id\t\n");
                        printf("************************************************************\n");
                        j = 1;
                    }
                    printf("%d\t%s\t%s\t%s\n", i+1,
                    addressBook->contacts[i].name,
                    addressBook->contacts[i].phone,
                    addressBook->contacts[i].email);
                    found = 1;
                }
            }
            if(!found)
            {
                printf("No contact found containing the name.\n");
                z=1;
                return;
            }
            else
            {
                return;
            }
        }
        break;
    
        case 2:
        {
            /*seach contact by number*/
            char searchNum[50];
            printf("Enter number : ");
            scanf(" %[^\n]", searchNum);
                
            int found = 0, j = 0;
            
            int index=1;
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strstr(addressBook->contacts[i].phone, searchNum)!=NULL)
                {
                    if(j == 0)
                    {
                        printf("Contact found:\n");
                        printf("************************************************************\n");
                        printf("Index\t   Name\t\t  Number\t   Email-id\t\n");
                        printf("************************************************************\n");
                        j = 1;
                    }
                    
                    printf("%d\t%s\t%s\t%s\n", i+1,
                    addressBook->contacts[i].name,
                    addressBook->contacts[i].phone,
                    addressBook->contacts[i].email);
                    found = 1;

                    
                }
            }
            if(!found)
            {
                printf("No contact found containing the number.\n");
                z=1;
                return;
            }
            else
            {
                return;
            }
        }
        break;
        
        case 3:
        {
            /*seach contact by email*/
            char searchID[50];
            printf("Enter email : ");
            scanf(" %[^\n]", searchID);
                
            int found = 0;

            int index=1, j = 0;
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strstr(addressBook->contacts[i].email, searchID)!=NULL)
                {
                    if(j == 0)
                    {
                        printf("Contact found:\n");
                        printf("************************************************************\n");
                        printf("Index\t   Name\t\t  Number\t   Email-id\t\n");
                        printf("************************************************************\n");
                        j = 1;
                    }
                    
                    printf("%d\t%s\t%s\t%s\n", i+1,
                    addressBook->contacts[i].name,
                    addressBook->contacts[i].phone,
                    addressBook->contacts[i].email);
                    found = 1;
                }
            }
            if(!found)
            {
                printf("No contact found containing the email.\n");
                z=1;
                return;
            }
            else
            {
                return;
            }
        }
        break;
    
        default:
        printf("Invalid choice. Please try again.\n");
        z=1;
        return;
    }
    getchar();
}

/*function for edit contact*/
void editContact(AddressBook *addressBook)
{
    searchContact(addressBook);

    if(z==0)
    {
        printf("\n");

        int i;

        /*read which index user want to edit*/
        printf("Enter the index you want to edit : ");
        scanf("%d", &i);
                
        switch(i)
        {
            case 1 ... 50:
            {
                int a=0, b=0, c=0;

                printf("Enter the new value : ");//read new value
                char newName[50];
                scanf(" %[^\n]", newName);
            
                if(strlen(newName) == 10)
                {
                    for(int j=0; newName[j] != '\0'; j++)
                    {
                        if(newName[j]>='0' && newName[j]<='9')
                        {
                            if(strcmp(addressBook->contacts[j].phone,newName)==0)
                            b=1;
                        }
                    }
                    if(b!=1)
                    {
                        strcpy(addressBook->contacts[i-1].phone,newName);
                        printf("Contact updated successfully.\n");
                    }
                    else
                    {
                        printf("Already Exist.");
                        return;
                    }
                }
                else if(strlen(newName) > 0)
                {
                    for(int j=0; newName[j] != '\0'; j++)
                    {
                        if(newName[j] == '@')
                        {
                            a=1;
                            for(int k = j + 1; newName[k] != '\0'; k++)
                            {
                                if(newName[k] == '.' && newName[k + 1] == 'c' && newName[k + 2] == 'o' && newName[k + 3] == 'm')
                                {
                                    c=1;
                                }
                                else if(newName[k] == '.' && newName[k + 1] == 'i' && newName[k + 2] == 'n')
                                {
                                    c=1;
                                }
                            }
                            if(c==1)
                            {
                                strcpy(addressBook->contacts[i-1].email, newName);
                                printf("Contact updated successfully.\n");
                            }
                            else
                            {
                                printf("Invalid Email.");
                                return;
                            }
                        }
                    }
                
                    if(a!=1)
                    {
                        for(int k=0; newName[k] != '\0'; k++)
                        {  
                            if(newName[k] >= 'A' || newName[k] <= 'Z' || newName[k] >= 'a' || newName[k] <= 'z')
                            {
                                strcpy(addressBook->contacts[i-1].name, newName);
                                printf("Contact updated successfully.\n");
                            }
                        }
                    }
                }
            }  
            break;

            default:
            printf("Invalid choice. Please try again.\n");
            return;
        }
        getchar();
    }
}

void deleteContact(AddressBook *addressBook)
{
	searchContact(addressBook);

    if(z==0)
    {
        int i;

        /*read which index user want to delete*/
        printf("\n");
        printf("Enter the index you want to delete : ");
        scanf("%d", &i);
        i--;
             
        /*removing the required index and overwrite by next contact*/   
        switch(i)
        {
            case 0 ... 50:
            {
                for(int j=i; j<addressBook->contactCount - 1; j++) 
                {
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                }
                addressBook->contactCount--;

                printf("Contact deleted successfully.\n");
                return;
            }
            break;
        }
        getchar();
    }
}