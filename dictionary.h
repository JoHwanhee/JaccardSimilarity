#pragma once
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

Dictionary* createDicionary();
Item* createItem(unsigned char* key, int value);
Item* get(Dictionary *dictionary, unsigned char* key);
int exist(Dictionary *dictionary, unsigned char* key);
void put(Dictionary *dictionary, Item* item);
void addTail(Dictionary *dictionary, Item* item);
int count(Dictionary *dictionary, int(*method)(int));