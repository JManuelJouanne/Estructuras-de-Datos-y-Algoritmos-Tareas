#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


bool string_equals(char* string1, char* string2) {
    printf("comparación strings: %s %s\n", string1, string2);
    return !strcmp(string1, string2);
}

Node* create_node(int value) {
    Node* node = malloc(sizeof(Node));
    *node = (Node){
        .value = value,
        .next = NULL,
    };
    return node;
}

int hash_function(char* tree, int range, int lenght){
    int hash_value = 0;
    int bits;
    if (lenght>15) {
        bits = 16;
    } else {
        bits = lenght;
    }
    for (int i=0; i<bits; i++) {
        if (tree[i] == '1') {
            hash_value += pow(2, i);
            printf(" +%d ", (int) pow(2, i));
        }
    }
    hash_value = hash_value % range;
    return hash_value;
}

void insert_node(Hashitem* item, int value) {
    Node* node = create_node(value);
    Node* current_node = item->roots;
    while (current_node->next) {
        current_node = current_node->next;
    }
    current_node->next = node;
}

void insert(Hashitem** table, int root, int lenght, char* tree, int table_size){
    int table_index = hash_function(tree, table_size, lenght);
    printf(" --> hash: %d\n", table_index);
    Hashitem* item = table[table_index];
    if (item == NULL) {
        item = malloc(sizeof(Hashitem));
        item->roots = create_node(root);
        item->lenght = lenght;
        item->tree = tree;
        item->next = NULL;
        table[table_index] = item;
    } else {
        while (item->next != NULL){
            if (string_equals(item->tree, tree)) {
                insert_node(item, root);
                free(tree);
                return;
            }
            item = item->next;
        }
        if (string_equals(item->tree, tree)) {
            insert_node(item, root);
            free(tree);
            return;
        }
        item->next = malloc(sizeof(Hashitem));
        item->next->roots = create_node(root);
        item->next->lenght = lenght;
        item->next->tree = tree;
        item->next->next = NULL;
    }
}

void fetch_value(Hashitem** table, char* tree, int table_size, FILE* file, int lenght){
    int table_index = hash_function(tree, table_size, lenght);
    printf("hash: %d  | [ ", table_index);
    Hashitem* item = table[table_index];
    if (item == NULL){
        fprintf(file, "-1\n");
        printf("-1\n");
        return;
    }    
    while (!string_equals(item->tree, tree)){
        item = item->next;
        if (item == NULL){
            fprintf(file, "-1\n");
            printf("-2\n");
            return;
        }
    }
    Node* current_node = item->roots;
    while (current_node){
        fprintf(file, "%d ", current_node->value);
        current_node = current_node->next;
    }
    fprintf(file, "\n");
}

void clean_item(Hashitem* item) {
    if (item->next) {
        clean_item(item->next);
    }
    clean_node(item->roots);
    free(item->tree);
    free(item);
}

void clean_node(Node* node) {
    if (node->next) {
        clean_node(node->next);
    }
    free(node);
}
