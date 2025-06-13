/*header file inclusion*/
#include <stdio.h>
#include "file.h"

/*function to save the contact*/
void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp;
    fp = fopen("contact.csv", "w+");

    if(fp == NULL)
    {
        printf("File doesn't exist.\n");
        return;
    }

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(i==0)
        {
            fprintf(fp, "#%d#\n", addressBook->contactCount);
        }
        fprintf(fp, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);    
    }
    fclose(fp);
}

/*function to load contacts from the CSV file*/
void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contact.csv", "r+");
    addressBook->contactCount = 0;

    if(fp == NULL)
    {
        printf("File doesn't exist.\n");
        return;
    }

    char str1[500];

    fseek(fp, 1, SEEK_SET); //it is for skipping #
    fread(str1, 2, sizeof(char), fp); //read the contact count
    sscanf(str1, "%d", &addressBook->contactCount); //atoi for contact count
    fseek(fp, 4, SEEK_SET);

    /*extraction of data from CSV file to structure member*/
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fseek(fp, 1, SEEK_CUR); //skipping character
        fscanf(fp, " %[^,]", str1); //read character
        sprintf(addressBook->contacts[i].name, "%s", str1); //print characters

        fseek(fp, 1, SEEK_CUR); //skipping number
        fscanf(fp, " %[^,]", str1); //read number
        sprintf(addressBook->contacts[i].phone, "%s", str1); //print number

        fseek(fp, 1, SEEK_CUR); //skipping element
        fscanf(fp, " %[^\n]", str1); // read element
        sprintf(addressBook->contacts[i].email, "%s", str1); //print element
    }
    fclose(fp);    
    return;
}