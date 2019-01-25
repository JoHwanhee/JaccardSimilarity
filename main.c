#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

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