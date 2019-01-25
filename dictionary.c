#include "dictionary.h"
#include <stdlib.h>
#include <string.h>



Item* get(Dictionary *dictionary, unsigned char* key) {
    Item* temp = dictionary->head;
    for (; temp != NULL; temp = temp->next) {
        if (strcmp(temp->key, key) == 0) {
            return temp;
        }

    }
    return NULL;
}

int exist(Dictionary *dictionary, unsigned char* key)
{
    Item* temp = dictionary->head;
    while (temp != NULL)
    {
        if (strcmp(temp->key, key) == 0) {
            return TRUE;
        }
        temp = temp->next;
    }

    return FALSE;
}

void addTail(Dictionary *dictionary, Item* item)
{
    dictionary->tail->next = item;
    dictionary->tail = item;
}

void put(Dictionary *dictionary, Item* item) {
    if (dictionary->head == NULL) {
        dictionary->head = item;
        dictionary->tail = item;
    }
    else
    {
        Item* existedItem = get(dictionary, item->key);
        if (existedItem) {
            existedItem->value = item->value;
            strcpy(existedItem->key, item->key);
            free(item);
            return;
        }

        addTail(dictionary, item);
    }
}

Item* createItem(unsigned char* key, int value) {
    Item* newNode = malloc(sizeof(Item));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;

    return newNode;
}

Dictionary* createDicionary() {
    Dictionary* dictionary = malloc(sizeof(Dictionary));
    dictionary->head = NULL;
    dictionary->tail = NULL;

    return dictionary;
}

int count(Dictionary *dictionary, int(*method)(int)) {
    Item* temp = dictionary->head;
    int i = 0;
    for (; temp != NULL; temp = temp->next) {
        if (method(temp->value))
        {
            i++;
        }
    }
    return i;
}