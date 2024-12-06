#include "nodo.h"
#include <stdio.h>
#include <stdlib.h>

Node* create_node(int id) {
    Node* node = malloc(sizeof(Node));
    *node = (Node) {
        .id = id,
        .size_neighbors = 16,
        .neighbors = malloc(16 * sizeof(int)),
        .cost = malloc(16 * sizeof(int)),
        .previous = NULL,
        .distance = 0,
        .color = 0,      //0:blanco - 1:gris - 2:negro
        .neighbors_count = 0,
    };
    return node;
}

void create_road(Node* from, Node* to, int cost) {
    if (from->neighbors_count == from->size_neighbors) {
        from->size_neighbors = from->size_neighbors*(3/2);
        from->neighbors = (int*) realloc(from->neighbors, from->size_neighbors * (sizeof(int)));
        from->cost = (int*) realloc(from->cost, from->size_neighbors * (sizeof(int)));
    }
    if (to->neighbors_count == to->size_neighbors) {
        to->size_neighbors = to->size_neighbors*(3/2);
        to->neighbors = (int*) realloc(to->neighbors, to->size_neighbors * (sizeof(int)));
        to->cost = (int*) realloc(to->cost, to->size_neighbors * (sizeof(int)));
    }
    from->neighbors[from->neighbors_count] = to->id+1;
    from->cost[from->neighbors_count] = cost;
    from->neighbors_count += 1;

    to->neighbors[to->neighbors_count] = from->id+1;
    to->cost[to->neighbors_count] = cost;
    to->neighbors_count += 1;
//    printf("%d %d\n", from->cost[to->id], to->cost[from->id]);
}

Heap* create_heap(int size) {
    Heap* heap = malloc(sizeof(Heap));
    *heap = (Heap) {
        .nodes = (Node**)calloc(size, sizeof(Node*)),
        .size = size,
        .capacity = 0,
    };
    return heap;
}

void percolate_up(Heap* heap, int index) {
    int parent = (index - 1) / 2;
    Node* node1 = heap->nodes[index];
    Node* node2 = heap->nodes[parent];
//    printf("precolate up: %d: %d --- %d: %d\n", index, node1->id, parent, node2->id);
    if (index > 0 && node1->distance < node2->distance){
        heap->nodes[index] = node2;
        heap->nodes[parent] = node1;
        percolate_up(heap, parent);
    }
}

void percolate_down(Heap* heap, int index) {
    int left = 2*index + 1;
    int right = 2*index + 2;
    int min = index;
    // Road* road_right = heap->roads[right];
    if (left < heap->capacity && heap->nodes[left]->distance < heap->nodes[min]->distance) {
        min = left;
    }
    if (right < heap->capacity && heap->nodes[right]->distance < heap->nodes[min]->distance) {
        min = right;
    }
    if (min != index) {
        Node* temp = heap->nodes[index];
        heap->nodes[index] = heap->nodes[min];
        heap->nodes[min] = temp;
        percolate_down(heap, min);
    }
}

void heap_insert(Heap* heap, Node* node) {
    if (heap->capacity == heap->size) {
        heap->size = (heap->size + 1)*2 - 1;
        heap->nodes = (Node**)realloc(heap->nodes, heap->size * sizeof(Node*));
    }
    heap->nodes[heap->capacity] = node;
    percolate_up(heap, heap->capacity);
    heap->capacity++;
//    printf("inserted - %d: %d\n", node->id, node->cost[node->previous->id]);
}

void heap_reinsert(Heap* heap, Node* node) {
    int i = 0;
    while (heap->nodes[i]->id != node->id) {
        i++;
    }
    heap->nodes[i] = heap->nodes[heap->capacity-1];
    heap->capacity--;
    percolate_down(heap, i);
    heap_insert(heap, node);
}

Node* heap_extract_min(Heap* heap) {
    Node* min = heap->nodes[0];
    heap->nodes[0] = heap->nodes[heap->capacity-1];
    heap->capacity--;
    percolate_down(heap, 0);
    return min;
}

int dijkstra(Node** nodes_list, Node* node, int search) {
    node->color = 1;
    Node* current;
    Heap* heap = create_heap(127);
    Node* neighbor;
    heap_insert(heap, node);
    while (heap->capacity > 0) {
        current = heap_extract_min(heap);
//        printf("current: %d\t --> %d\n", current->id, current->distance); //
        if (current->id == search) {
            free(heap->nodes);
            free(heap);
//            printf("found %d\n", current->id); //
            return current->distance;
        }
//        printf("neghbor 0: %d\n",current->neighbors[1]);
        for (int i=0; i<current->neighbors_count; i++) {
            neighbor = nodes_list[current->neighbors[i]-1];
//            printf("\tneighbor: %d\tcolor: %d\t +%d\n", neighbor->id, neighbor->color, current->cost[i]); //
            if (neighbor->color == 0) {
                neighbor->distance = current->distance + current->cost[i];
                neighbor->previous = current;
                neighbor->color = 1;
                heap_insert(heap, neighbor);
            }
            else if (neighbor->color == 1 && neighbor->distance > current->distance + current->cost[i]) {
                neighbor->distance = current->distance + current->cost[i];
                neighbor->previous = current;
                heap_reinsert(heap, neighbor);
            }
        }
        current->color = 2;
    }
//    printf("not founded\n"); //
    free(heap->nodes);
    free(heap);
    return 0;
}

void clean_graph(Node** list_nodes, int nodes) {
    for (int i=0; i<nodes; i++) {
        free(list_nodes[i]->cost);
        free(list_nodes[i]->neighbors);
        free(list_nodes[i]);
    }
    free(list_nodes);
}

