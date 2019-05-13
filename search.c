#include "search.h"
#include "structures.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define LENGTH 128

int search_sth(contact* head)
{
    if(head == NULL)
    {
        printf("No contacts to search!\n");
        return 1;
    }
    int id;
    char search[LENGTH];
    fflush(stdin);
    fgets(search, LENGTH, stdin);
    while(head!=NULL)
    {
        if(strstr(head->name, search))
        {
            id = head->ID;
            printf("Znaleziono w ID = %d", id);
            return id;
        }
        else
        {
            head = head->next;
        }
    }
    return -1;
}
