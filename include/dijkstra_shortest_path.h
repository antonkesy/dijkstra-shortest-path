#ifndef DIJKSTRA_SHORTEST_PATH_H
#define DIJKSTRA_SHORTEST_PATH_H

#include <stdint.h>

struct node;

typedef struct {
    struct node *to; //from is clear since edge is from a node
    uint64_t cost;
} edge_t;

typedef struct {
    uint64_t count;
    edge_t *edges;
} edges_t;

typedef struct node {
    void *value;
    edges_t edges;
} node_t;

typedef struct {
    uint64_t size;
    node_t *nodes;
} graph_t;

typedef struct {
    node_t *dest;
    uint64_t hops; //amount of nodes/hops from start to dest
    node_t *nodes; //ordered from first to last
    uint64_t cost;
} path_t;

typedef struct {
    uint64_t count; //count of paths
    path_t *paths;
} shortest_paths_t;

//nodes_count: other_nodes + 1
shortest_paths_t *get_shortest_paths(node_t *src, graph_t *graph);

void delete_shortest_paths(shortest_paths_t *paths);

#endif //DIJKSTRA_SHORTEST_PATH_H
