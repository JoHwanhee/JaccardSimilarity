#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct node {
    unsigned char* key;
    int value;
    struct node* next;
} Node;

typedef struct dictionary {
    Node* head;
    Node* tail;
} Dictionary;

int getLength(unsigned char* str) {
    int cnt = 0;
    unsigned char* tmp = str;
    while (*tmp++)
        cnt++;

    return cnt;
}

int equals(unsigned char* str1, unsigned char* str2) {
    int size1 = getLength(str1);
    int size2 = getLength(str2);

    if (size1 != size2) {
        return FALSE;
    }

    for (int i = 0; i < size1; i++) {
        if (str1[i] != str2[i]) {
            return FALSE;
        }
    }

    return TRUE;
}

Node* search(Dictionary *dictionary, unsigned char* key) {
    Node* temp = dictionary->head;
    for (; temp != NULL;) {
        if (equals(temp->key, key)) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void put(Dictionary *dictionary,  Node* node) {
    if (dictionary->head == NULL) {
        dictionary->head = node;
        dictionary->tail = node;
        return;
    }

    Node* existed = search(dictionary, node->key);
    if (!existed) {
        dictionary->tail->next = node;
        dictionary->tail = node;
    }
    else {
        existed->value = 1;
    }
}

Node* createNode(unsigned char* key) {
    Node* newNode = malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = 0;
    newNode->next = NULL;

    return newNode;
}

Dictionary* createDicionary() {
    Dictionary* dictionary = malloc(sizeof(Dictionary));
    dictionary->head = NULL;
    dictionary->tail = NULL;

    return dictionary;
}

unsigned char** multiset(unsigned char* str, int* ret_size) {
    int size = getLength(str);

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

int count(Dictionary *dictionary, int (*method)(int)) {
    Node* temp = dictionary->head;
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

void loadsDictionary(Dictionary* dictionary, unsigned char** arr, int size)
{
    for (int i = 0; i < size; i++) {
        Node* newNode = createNode(arr[i]);
        put(dictionary, newNode);
    }
}

double jaccard(unsigned char* str1, unsigned char* str2) {
    int size1 = 0;
    int size2 = 0;
    unsigned char** arr1 = multiset(str1, &size1);
    unsigned char** arr2 = multiset(str2, &size2);
    
    Dictionary* dictionary = createDicionary();
    loadsDictionary(dictionary, arr1, size1 - 1);
    loadsDictionary(dictionary, arr2, size2 - 1);

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
    unsigned char* a = "좋은 아침입니다.";
    unsigned char* b = "안녕하세요. 좋은 아침입니다. ";
    printf("A : %s\n", a);
    printf("B : %s\n", b);

    const double simility = jaccard(filter(a),filter(b));
    printf("Simility : %.2f %s", simility * 100, "%");

    return 0;
}