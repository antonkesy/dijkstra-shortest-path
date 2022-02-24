#include <stddef.h>
#include <malloc.h>
#include "../include/dijkstra_shortest_path.h"
#include "priority_queue/priority_queue.h"
#include "dijkstra_shortest_path_p.h"

shortest_paths_t *get_shortest_paths(node_t *src, graph_t *graph) {
    //prepare return values;
    shortest_paths_t *paths = create_shortest_paths(graph);
    if (paths == NULL) return NULL;

    priority_queue_ptr_t queue = create_queue(graph->size);
    if (queue == NULL) {
        delete_shortest_paths(paths);
        return NULL;
    }


    node_t *next_node = src;
    while (next_node != NULL) {
        uint64_t self_cost = get_path_costs(paths, next_node);
        for (size_t neighbours = 0; neighbours < next_node->edges.count; ++neighbours) {
            node_t *neighbour = next_node->edges.edges[neighbours].to;
        }
        next_node = (node_t *) extract_min(queue);
    }



    return paths;
}

void update_paths(shortest_paths_t paths, node_t node) {

}

uint64_t get_path_costs(shortest_paths_t *paths, node_t *node) {
    path_t *path = get_path(paths, node);

    //add new
    if (path == NULL) {
    }

}

path_t *get_path(shortest_paths_t *paths, node_t *node) {
    for (int i = 0; i < paths->count; ++i) {
        if (paths->paths[i].dest == node) {
            return &paths->paths[i];
        }
    }
    return NULL;
}

shortest_paths_t *create_shortest_paths(const graph_t *graph) {
    shortest_paths_t *paths = malloc(sizeof(shortest_paths_t));
    if (paths == NULL) return NULL;
    path_t *path_array = malloc(sizeof(path_t) * graph->size);
    if (path_array == NULL) return NULL;
    paths->paths = path_array;
    paths->count = graph->size;

    //fill all paths with inf (MAX)
    for (uint64_t i = 0U; i < graph->size; ++i) {
        path_t *path = malloc(sizeof(path_t));
        if (path == NULL) {
            delete_shortest_paths(paths);
            return NULL;
        }

        path->dest = &(graph->nodes[i]);
        path->cost = INT64_MAX;
        path->nodes = NULL;
        path->hops = 0U;

        paths->paths = path;
    }

    return paths;
}

void delete_shortest_paths(shortest_paths_t *paths) {
    free(paths->paths);
    free(paths);
}