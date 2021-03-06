#ifndef DIJKSTRA_SHORTEST_PATH_H
#define DIJKSTRA_SHORTEST_PATH_H

#include <stdint.h>

struct node;

typedef struct {
    struct node *to; //from is clear since via is from a node
    uint64_t cost; //sum of cost should not overflow!
} edge_t;

typedef struct {
    uint64_t count;
    edge_t *edges;
} edges_t;

typedef struct node {
    void *value; //if nodes should represent something
    edges_t edges;
} node_t;

typedef struct path_ {
    struct path_ *from;
    edge_t *via;
} path_t;

typedef struct {
    uint64_t count; //count of paths
    path_t *paths;
} shortest_paths_t;

typedef struct {
    uint64_t size;
    node_t *nodes;
} graph_t;

shortest_paths_t *get_shortest_paths(node_t *src, graph_t *graph);

uint64_t get_path_cost(const path_t *path);

void delete_shortest_paths(shortest_paths_t *paths);

#endif //DIJKSTRA_SHORTEST_PATH_H
