#ifndef DIJKSTRA_SHORTEST_PATH_DIJKSTRA_SHORTEST_PATH_P_H
#define DIJKSTRA_SHORTEST_PATH_DIJKSTRA_SHORTEST_PATH_P_H

#include "../include/dijkstra_shortest_path.h"

shortest_paths_t *create_shortest_paths(const graph_t *graph) ;

uint64_t get_path_costs(shortest_paths_t *paths, node_t *node);

path_t *get_path(shortest_paths_t *paths, node_t *node);

#endif //DIJKSTRA_SHORTEST_PATH_DIJKSTRA_SHORTEST_PATH_P_H
