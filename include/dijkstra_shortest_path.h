#ifndef DIJKSTRA_SHORTEST_PATH_H
#define DIJKSTRA_SHORTEST_PATH_H

#include <stdint.h>

struct node;

typedef struct {
    uint64_t count;
    struct node *neighbours;
} edges_t;

typedef struct node {
    uint64_t cost;
    void *value;
    edges_t edges;
} node_t;

typedef struct {
    node_t dest;
    uint64_t hops; //amount of nodes/hops from start to dest
    node_t *nodes; //ordered from first to last
} shortest_path_t;

typedef struct {
    uint64_t count; //count of paths
    shortest_path_t *paths;
} shortest_paths_t;

shortest_paths_t* get_shortest_paths(node_t src);

#endif //DIJKSTRA_SHORTEST_PATH_H
