#pragma once
#include <stdio.h>
#include <stdbool.h>

bool string_equals(char *string1, char *string2);

typedef struct node {
    int value;
    struct node* next;
} Node;

Node* create_node(int value);

typedef struct hashitem_t {
    int lenght;
    char* tree;
    Node* roots;
    struct hashitem_t* next;
} Hashitem;

int hash_function(char* tree, int range, int lenght);

void insert_node(Hashitem* item, int value);

void insert(Hashitem** table, int root, int lenght, char* tree, int table_size);

void fetch_value(Hashitem** table, char* tree, int table_size, FILE* file, int lenght);

void clean_item(Hashitem* item);

void clean_node(Node* node);



