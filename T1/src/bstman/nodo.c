#include "nodo.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


Node* create_node(int value){
    Node* node = calloc(1, sizeof(Node));
    *node = (Node){
        .value = value,
        .left_child = NULL,
        .right_child = NULL,
    };
    return node;
}

void insert_node(Node* root, Node* node){
    if (root->value > node->value){
        if (root->left_child){
            insert_node(root->left_child, node);
        }
        else{
            root->left_child = node;
        }
    }
    else{
        if (root->right_child){
            insert_node(root->right_child, node);
        }
        else{
            root->right_child = node;
        }
    }
}

Node* is_in(Node* root, Node* node){
    if (root->value == node->value){
        return root;
    }
    else if (root->value > node->value){
        if (root->left_child){
            return is_in(root->left_child, node);
        }
        else{
            return NULL;
        }
    }
    else{
        if (root->right_child){
            return is_in(root->right_child, node);
        }
        else{
            return NULL;
        }
    }
}

void path_node(Node* root, int value, FILE* file){
    Node* actual_node = root;
    bool searching = true;
    fprintf(file, "%d", actual_node->value);
    while (searching){
      if (actual_node->value == value){
        fprintf(file, "\n");
        searching = false;
      }
      else if (actual_node->value > value){
        if (actual_node->left_child){
          actual_node = actual_node->left_child;
          fprintf(file, " %d", actual_node->value);
        }
        else{
          fprintf(file, " X\n");
          searching = false;
        }
      }
      else if (actual_node->value < value){
        if (actual_node->right_child){
          actual_node = actual_node->right_child;
          fprintf(file, " %d", actual_node->value);
        }
        else{
          fprintf(file, " X\n");
          searching = false;
        }
      }  
    }
}

int deep_node(Node* root, int value){
    int deep = 0;
    Node* actual_node = root;
    while (actual_node->value) {
        if (actual_node->value == value){
            return deep;
        }
        else if (actual_node->value > value){
            actual_node = actual_node->left_child;
        }
        else{
            actual_node = actual_node->right_child;
        }
        deep += 1;
    }
    return deep;
}

void order_tree(Node* node, FILE* file){
    if (node->left_child){
        order_tree(node->left_child, file);
    }
    fprintf(file, "%d ", node->value);
    if (node->right_child){
        order_tree(node->right_child, file);
    }
}

int subtree(Node* node1, Node* node2){
    int equal_value = 0;
    int left_tree = 1;
    int right_tree = 1;
    if (node1->left_child && node2->left_child){
        left_tree = subtree(node1->left_child, node2->left_child);
    }
    else if (node1->left_child || node2->left_child){
        left_tree = 0;
    }
    if (node1->value == node2->value){
        equal_value = 1;
    }
    if (node1->right_child && node2->right_child){
        right_tree = subtree(node1->right_child, node2->right_child);
    }
    else if (node1->right_child || node2->right_child){
        right_tree = 0;
    }
    if (equal_value + left_tree + right_tree == 3){
        return 1;
    }
    else{
        return 0;
    }
}

void destroy_tree(Node* node){
    if (node->left_child){
        destroy_tree(node->left_child);
    }
    if (node->right_child){
        destroy_tree(node->right_child);
    }
    free(node);
}
