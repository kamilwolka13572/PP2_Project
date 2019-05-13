#include "read_from_file.h"

#include <stdlib.h>
#include <stddef.h>

contact* loadContactsFromAFile(char* filename){

    FILE* file = fopen(filename, "r");

    if(file == NULL)
        return NULL;

    contact* head = malloc(sizeof(contact));
    contact* currentContact = head;
    char buffer;
    int id;

    if(fscanf(file, "%d%c", &id, &buffer) != EOF){
        head->ID = id;

        int nPhoneNumbers, nEmails;

        fscanf(file,"%[^\n]\n", head->name);

        fscanf(file,"%[^\n]\n", head->surname);
        head->address = loadAddress(file);

        fscanf(file, "%d%c", &(nPhoneNumbers), &buffer);
        head->phoneHead = loadPhoneNumbers(file, nPhoneNumbers);

        fscanf(file, "%d%c", &(nEmails), &buffer);
        head->emailHead = loadEmails(file, nEmails);
    }else{
        free(head);
        return NULL;
    }

    while(fscanf(file, "%d%c", &id, &buffer) != EOF){
        contact* contactBuffer = malloc(sizeof(contact));
        contactBuffer->ID = id;

        int nPhoneNumbers, nEmails;

        fscanf(file,"%[^\n]\n", contactBuffer->name);
        fscanf(file,"%[^\n]\n", contactBuffer->surname);
        contactBuffer->address = loadAddress(file);

        fscanf(file, "%d%c", &nPhoneNumbers, &buffer);
        contactBuffer->phoneHead = loadPhoneNumbers(file, nPhoneNumbers);

        fscanf(file, "%d%c", &nEmails, &buffer);
        contactBuffer->emailHead = loadEmails(file, nEmails);

        currentContact->next = contactBuffer;
        currentContact = currentContact->next;
    }

    fclose(file);

    return head;
}

address_t* loadAddress(FILE* file){

    address_t* address = malloc(sizeof(address));
    char buffer;

    fscanf(file,"%[^\n]\n", address->city);
    fscanf(file,"%d%c", &(address->houseNumber), &buffer);
    fscanf(file,"%[^\n]\n", address->postOffice);
    fscanf(file,"%[^\n]\n", address->street);
    fscanf(file,"%[^\n]\n", address->zipCode);

    return address;
}

phone_t* loadPhoneNumbers(FILE* file, int nPhoneNumbers){

    phone_t* head = malloc(sizeof(phone_t));
    phone_t* currentPhone = head;
    char buffer;

    if(nPhoneNumbers < 1)
        return NULL;

    fscanf(file, "%d%c", &(head->phoneNumber), &buffer);

    int i = 1;
    for(; i < nPhoneNumbers; i++){
        phone_t* phoneBuffer = malloc(sizeof(phone_t));
        fscanf(file, "%d%c", &(phoneBuffer->phoneNumber), &buffer);
        currentPhone->next = phoneBuffer;
        currentPhone = currentPhone->next;
    }

    currentPhone->next = NULL;

    return head;
}

email_t* loadEmails(FILE* file, int nEmails){

    email_t* emailHead = malloc(sizeof(email_t));
    email_t* currentEmail = emailHead;

    if(nEmails < 1)
        return NULL;

    fscanf(file,"%[^\n]\n", emailHead->emailAddress);

    int i = 1;
    for(; i < nEmails; i++){
        email_t* emailBuffer = malloc(sizeof(email_t));
        fscanf(file, "%[^\n]\n", emailBuffer->emailAddress);
        currentEmail->next = emailBuffer;
        currentEmail = currentEmail->next;
    }

    currentEmail->next = NULL;

    return emailHead;
}

