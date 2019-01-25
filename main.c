#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct node {
    unsigned char* key;
    int value;
    struct node* next;
} Node;

Node* head;
Node* tail;

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

Node* search(unsigned char* key) {
    Node* temp = head;
    for (; temp != NULL;) {
        if (equals(temp->key, key)) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void append(Node* node) {
    Node* existed = search(node->key);
    if (!existed) {
        tail->next = node;
        tail = node;
    }
    else {

        existed->value = 1;
    }
}

Node* createNode(unsigned char* key) {
    Node* newNode = malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = NULL;

    return newNode;
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

int countUnion() {
    Node* temp = head;
    int i = 0;
    for (; temp != NULL; temp = temp->next) {
        i++;
    }
    return i;
}

int countInter() {
    Node* temp = head;
    int i = 0;
    for (; temp != NULL; temp = temp->next) {
        if (temp->value == 1) {
            i++;
        }
    }
    return i;
}

double jaccard(unsigned char* str1, unsigned char* str2) {
    int size1 = 0;
    int size2 = 0;
    unsigned char** arr1 = multiset(str1, &size1);
    unsigned char** arr2 = multiset(str2, &size2);

    for (int i = 0; i < size1 - 1; i++) {
        Node* newNode = createNode(arr1[i]);
        if (head == NULL) {
            head = newNode;
            tail = newNode;
            continue;
        }
        append(newNode);
    }

    for (int i = 0; i < size2 - 1; i++) {
        Node* newNode = createNode(arr2[i]);
        append(newNode);
    }
    return (double)countInter() / (double)countUnion();
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
    unsigned char* a = "안녕하세요. 좋은 아침입니다.";
    unsigned char* b = "안녕하세요. 좋은 아침입니다. ";
    printf("A : %s\n", a);
    printf("B : %s\n", b);

    const double simility = jaccard(filter(a),filter(b));
    printf("Simility : %.2f %s", simility * 100, "%");

    return 0;
}