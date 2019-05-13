#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "printing.h"
#include "adding.h"
#include "deleting.h"
#include "save_to_file.h"
#include "read_from_file.h"
#include "search.h"
#include <stdio.h>

void menu(); //!< funkcja, ktora sprawdza, jaka operacje uzytkownik chce aktualnie wykonac

const char* contactsFilename = "contacts.txt"; /*!< sciezka pliku do zapisu/odczytu danych */
contact* contactHead = NULL; /*!< glowa listy kontaktow */

int main()
{
    contactHead = loadContactsFromAFile(contactsFilename);
    menu();

    return 0;
}

void menu(){
    while(1){
        printf("Wybierz co chcesz zrobic:\n");
        printf("1) Wyswietl kontakty\n");
        printf("2) Dodaj kontakt\n");
        printf("3) Usun kontakt\n");
        printf("4) Edytuj kontakt\n");
        printf("5) Szukaj \n");
        printf("0) Wyjdz\n");
        printf("Wybor: ");
        int wybor;
        scanf("%d", &wybor);

        getchar();

        if(wybor == 1)
            printAllContacts(contactHead);
        else if(wybor == 2){
            contactHead = addContact(contactHead);
            saveContacts(contactsFilename, contactHead);
        }
        else if(wybor == 3){
            contactHead = deleteContact(contactHead);
            saveContacts(contactsFilename, contactHead);
        }
        else if(wybor == 4){
            contactHead = edit(contactHead);
            saveContacts(contactsFilename, contactHead);
        }
        else if(wybor == 5){
        search_sth(contactHead);
        }
        else if(wybor == 0)
            return;
        else printf("Wybrales niewlasciwa opcje!");

        printf("\n\n");
    }
}
