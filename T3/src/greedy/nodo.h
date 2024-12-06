#pragma once

typedef struct node {
    int id;
    int size_neighbors;
    int* neighbors;
    int* cost;
    struct node* previous;
    int distance;
    int color;      //0:blanco - 1:gris - 2:negro
    int neighbors_count;
} Node;

typedef struct heap {
    Node** nodes;
    int size;
    int capacity;
} Heap;

Node* create_node(int id);

void create_road(Node* from, Node* to, int cost);

Heap* create_heap(int size);

void percolate_up(Heap* heap, int index);

void percolate_down(Heap* heap, int index);

void heap_insert(Heap* heap, Node* node);

void heap_reinsert(Heap* heap, Node* node);

Node* heap_extract_min(Heap* heap);

int dijkstra(Node** nodes_list, Node* node, int search);

void clean_graph(Node** list_nodes, int nodes);   //recursiva
