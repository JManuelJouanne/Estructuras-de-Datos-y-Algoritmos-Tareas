#pragma once

typedef struct quadtree_node
{
    struct quadtree_node* father;
    struct quadtree_node* child_1;
    struct quadtree_node* child_2;
    struct quadtree_node* child_3;
    struct quadtree_node* child_4;
    int x1;
    int x2;
    int y1;
    int y2;
    double prom_L;
    double desv_L;
    double s_cuad_L;
    double prom_A;
    double desv_A;
    double s_cuad_A;
    double prom_B;
    double desv_B;
    double s_cuad_B;
    double prom_desv;
    int size;
    int deepness;
    int is_leaf;
} QT_Node;

QT_Node* create_node(QT_Node* father, int deepness, int size);

void divide_node();

