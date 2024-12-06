#include <stdio.h>
#include <stdlib.h>
#include "nodo.h"

int main(int argc, char** argv)
{
  if(argc != 3)
  {
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
  if(!input_stream)
  {
    printf("El archivo %s no existe o no se puede leer\n", argv[1]);
    return 2;
  }
  if(!output_stream)
  {
    printf("El archivo %s no se pudo crear o no se puede escribir\n", argv[2]);
    printf("Recuerda que \"fopen\" no puede crear carpetas\n");
    fclose(input_stream);
    return 3;
  }

  // [Aqui va tu tarea]
  int nodes, edges, start_node, last_node;
  fscanf(input_stream, "%d", &nodes);
  fscanf(input_stream, "%d %d", &start_node, &last_node);
  fscanf(input_stream, "%d", &edges);

  Node** nodes_list = malloc(nodes * sizeof(Node*));
  for (int i=0; i<nodes; i++) {
    nodes_list[i] = create_node(i);
  }

  int from, to, cost;

  for (int i=0; i<edges; i++){
    fscanf(input_stream, "%d %d %d", &from, &to, &cost);
    create_road(nodes_list[from], nodes_list[to], cost);
  }
  
  int min_distance = dijkstra(nodes_list, nodes_list[start_node], last_node);

  clean_graph(nodes_list, nodes);

  fprintf(output_stream, "%d", min_distance);
  // Cerrar archivo de input
  fclose(input_stream);

  // Cerrar archivo de output
  fclose(output_stream);

  return 0;
}
