#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "nodo.h"


/* Retorna true si ambos strings son iguales */
bool string_equals(char *string1, char *string2) {
  return !strcmp(string1, string2);
}

/* Revisa que los parametros del programa sean válidos */
bool check_arguments(int argc, char **argv) {
  if (argc != 3) {
    printf("Modo de uso: %s INPUT OUTPUT\n", argv[0]);
    printf("Donde:\n");
    printf("\tINPUT es la ruta del archivo de input\n");
    printf("\tOUTPUT es la ruta del archivo de output\n");
    exit(1);
  }

  return true;
}


int main(int argc, char** argv) {
  check_arguments(argc, argv);

  FILE* input_file = fopen(argv[1], "r");
  FILE* output_file = fopen(argv[2], "w");

  int node_count;
  int query_count;

  fscanf(input_file, "%d", &node_count);

  /* leemos Cada nodo */
  int k;
  fscanf(input_file, "%d", &k);
  printf("%d ", k);
  Node* root = create_node(k);
  for (int i=1; i<node_count; i++) {
    fscanf(input_file, "%d", &k);
    printf("%d ", k);
    Node* node = create_node(k);
    insert_node(root, node);
  }
  printf("\n");


  fscanf(input_file, "%d", &query_count);
  /* leemos las consultas */
  char command[32];
  int value;
  for (int i=0; i<query_count; i++) {
    fscanf(input_file, "%s %d", command, &value);
    printf("%s %d\n", command, value);
    if (string_equals(command, "PATH")){
      path_node(root, value, output_file);
    }

    else if (string_equals(command, "DEEP")){
      int deepness;
      deepness = deep_node(root, value);
      fprintf(output_file, "%d\n", deepness);
    }

    else if (string_equals(command, "ORDER")){
      order_tree(root, output_file);
      fprintf(output_file, "\n");
    }

    else if (string_equals(command, "SUBTREE")){
      int c;
      fscanf(input_file, "%d", &c);
      printf("%d ", c);
      Node* node2 = create_node(c);
      Node* start_node = is_in(root, node2);
      for (int i=1; i<value; i++) {
        fscanf(input_file, "%d", &c);
        printf("%d ", c);
        Node* node = create_node(c);
        insert_node(node2, node);
      }
      printf("\n");
      if (start_node){
        int is_subtree = subtree(start_node, node2);
        fprintf(output_file, "%d\n", is_subtree);
      }
      else{
        fprintf(output_file, "0\n");
      }
      destroy_tree(node2);
    }
  }

  destroy_tree(root);
  fclose(input_file);
  fclose(output_file);
  return 0;
}
