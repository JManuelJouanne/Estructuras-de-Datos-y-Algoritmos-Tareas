#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hashtable.h"

int main(int argc, char** argv) {
  if (argc != 3) {
    printf("Modo de uso: %s input output\nDonde:\n", argv[0]);
    printf("\t\"input\" es la ruta al archivo de input\n");
    printf("\t\"output\" es la ruta al archivo de output\n");
    return 1;
  }

  // Abrimos el archivo de input
  FILE* input_stream = fopen(argv[1], "r");

  // Abrimos el archivo de output
  FILE* output_stream = fopen(argv[2], "w");

  // Si alguno de los dos archivos no se pudo abrir
  if (!input_stream) {
    printf("El archivo %s no existe o no se puede leer\n", argv[1]);
    return 2;
  }
  if (!output_stream) {
    printf("El archivo %s no se pudo crear o no se puede escribir\n", argv[2]);
    printf("Recuerda que \"fopen\" no puede crear carpetas\n");
    fclose(input_stream);
    return 3;
  }

  // [Aqui va tu tarea]///////////////////////////////////////////////////

  int nodes_big_tree, table_size;
  fscanf(input_stream, "%d", &nodes_big_tree);
  if (nodes_big_tree > 1039) {
    table_size = 1039;
  } else {
    table_size = nodes_big_tree;
  }

  char* arbol = malloc(sizeof(char) * (nodes_big_tree+1));
  char bit;
  arbol[0] = '0';
  printf("%i\n", nodes_big_tree);
  for (int i=1; i<nodes_big_tree+1; i++){
    fscanf(input_stream, " %c", &bit);
    arbol[i] = bit;
    printf("%c", arbol[i]);
  }

  int height, nodes_hight, deepness_node, copy_nodes, last_line, nodes_subtree, nodes_last_line;
  height = log10(nodes_big_tree + 1) / log10(2);
  nodes_hight = nodes_big_tree - pow(2, height-1);
  printf("\n--------\n");

  Hashitem** tabla = calloc(table_size, sizeof(Hashitem*));
  char* previous_tree = calloc((pow(2, height)), sizeof(char));
    for (int n=1; n<nodes_hight+1; n++) {
      deepness_node = height - floor(log10(n) / log10(2));
      previous_tree[0] = arbol[n];
      for (int d=2; d<deepness_node+1; d++) {
        nodes_subtree = pow(2, d) - 1;
        char* sub_tree = malloc(sizeof(char) * (nodes_subtree+1));
        copy_nodes = pow(2, d-1) - 1;
        last_line = n * pow(2, d-1);
        for (int c=0; c<copy_nodes; c++) {
          sub_tree[c] = previous_tree[c];
          printf("%c", sub_tree[c]);
        }
        nodes_last_line = nodes_subtree - copy_nodes;
        for (int i=0; i<nodes_last_line; i++) {
          sub_tree[copy_nodes + i] = arbol[last_line + i];
          previous_tree[copy_nodes + i] = arbol[last_line + i];
          printf("%c", sub_tree[copy_nodes+i]);
        }
        sub_tree[nodes_subtree] = '\0';
        insert(tabla, n, nodes_subtree, sub_tree, table_size);
      }
    }
    printf("\n*********\n");
  free(previous_tree);
  free(arbol);

  int query_count;
  fscanf(input_stream, "%d", &query_count);
  for (int i=0; i<query_count; i++) {
    fscanf(input_stream, "%d", &nodes_subtree);
    char* wanted_tree = malloc(sizeof(char) * (nodes_subtree+1));
    for (int a=0; a<nodes_subtree; a++) {
      fscanf(input_stream, " %c", &bit);
      wanted_tree[a] = bit;
      printf("%c", wanted_tree[a]);
    }
    wanted_tree[nodes_subtree] = '\0';
    printf(" --> ");
    fetch_value(tabla, wanted_tree, table_size, output_stream, nodes_subtree);
    free(wanted_tree);
  }

  for (int i=0; i<table_size; i++) {
    if (tabla[i]) {
      clean_item(tabla[i]);
    }
  }
  free(tabla);

  ////////////////////////////////////////////////////////////////////////

  // Cerrar archivo de input
  fclose(input_stream);

  // Cerrar archivo de output
  fclose(output_stream);

  return 0;
}
