#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct item {
    unsigned char* key;
    int value;
    struct item* next;
} Item;

typedef struct dictionary {
    Item* head;
    Item* tail;
} Dictionary;

Item* get(Dictionary *dictionary, unsigned char* key) {
    Item* temp = dictionary->head;
    for (; temp != NULL;  temp = temp->next) {
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

int count(Dictionary *dictionary, int (*method)(int)) {
    Item* temp = dictionary->head;
    int i = 0;
    for (; temp != NULL; temp = temp->next) {
        if(method(temp->value))
        {
            i++;
        }
    }
    return i;
}

int isInterset(int value)
{
    return value == 1;
}

int isUinon(int value)
{
    return TRUE;
}

void loads(Dictionary* dictionary, unsigned char** arr, int start, int end)
{
    for (int i = start; i < end; i++) {
        unsigned char* key = arr[i];
        int value = 0;

        if(exist(dictionary, key))
        {
            value = 1;
        }
        else
        {
            value = 0;
        }
        
        put(dictionary, createItem(key, value));
    }
}

unsigned char** multiset(unsigned char* str, int* ret_size) {
    int size = strlen(str);

    unsigned char** arr = malloc(sizeof(unsigned char**) * size);

    for (int i = 0; i < size - 1; i++)
    {
        arr[i] = malloc(sizeof(unsigned char*) * 3);
        sprintf(arr[i], "%x%x%c", str[i], str[i + 1], '\0');
    }

    arr[size - 1] = NULL;

    *ret_size = (size);
    return arr;
}

double jaccard(unsigned char* str1, unsigned char* str2) {
    Dictionary* dictionary = createDicionary();
    int size1 = 0;
    unsigned char** arr1 = multiset(str1, &size1);
    loads(dictionary, arr1, 0, size1 - 1);
    
    int size2 = 0;
    unsigned char** arr2 = multiset(str2, &size2);
    loads(dictionary, arr2, 0, size2 - 1);

    const double intersetCount = (double)count(dictionary, isInterset);
    const double unionCount = (double)count(dictionary, isUinon);

    return intersetCount / unionCount;
}


unsigned int validateChar(unsigned char ch)
{
    switch (ch)
    {
    case ' ':
        return FALSE;
    case '-':
        return FALSE;
    case '.':
        return FALSE;
    case '*':
        return FALSE;
    case '(':
        return FALSE;
    case ')':
        return FALSE;
    default:
        return TRUE;
    }
}

unsigned char* filter(unsigned char* str)
{
    unsigned char* temp = str;

    int count = 1;
    while(*temp)
    {
        if (validateChar(*temp))
            count++;

        temp++;
    }

    unsigned char* newStr = malloc(sizeof(unsigned char) * count);
    newStr[count - 1] = '\0';
    
    temp = str;
    int i = 0;
    while (*temp)
    {
        if (validateChar(*temp))
            newStr[i++] = *temp;

        temp++;
    }

    return newStr;
}

int main(int argc, char const *argv[]) {
    unsigned char* a = "hello ";
    unsigned char* b = "안녕하세요. 좋은 아침입니다. ";
    printf("A : %s\n", a);
    printf("B : %s\n", b);

    const double simility = jaccard(filter(a),filter(b));
    printf("Simility : %.2f %s", simility * 100, "%");

    return 0;
}