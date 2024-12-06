#pragma once
#include <stdio.h>


typedef struct node
{
    int value;
    struct node* left_child;
    struct node* right_child;
} Node;


Node* create_node(int value);

void insert_node(Node* root, Node* node);

Node* is_in(Node* root, Node* node);

void path_node(Node* root, int value, FILE* file);

int deep_node(Node* root, int value);

void order_tree(Node* node, FILE* file);

int subtree(Node* node1, Node* node2);

void destroy_tree(Node* node);
