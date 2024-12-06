#include "qt_node.h"

QT_Node* create_node(QT_Node* father, int deepness, int size){
    QT_Node* nodo = calloc(1, sizeof(QT_Node));
    *nodo = (QT_Node){
        .father = father,
        .deepness = deepness,
        .size = size,
    };
    divide_node();
}
