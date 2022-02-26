#ifndef DIJKSTRA_SHORTEST_PATH_DIJKSTRA_SHORTEST_PATH_P_H
#define DIJKSTRA_SHORTEST_PATH_DIJKSTRA_SHORTEST_PATH_P_H

#include "../include/dijkstra_shortest_path.h"

shortest_paths_t *create_shortest_paths();

path_t *get_path(shortest_paths_t *paths, node_t *node);

bool add_new_path(shortest_paths_t *paths, path_t to_add);

#endif //DIJKSTRA_SHORTEST_PATH_DIJKSTRA_SHORTEST_PATH_P_H
