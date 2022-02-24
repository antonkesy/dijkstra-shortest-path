#include <stddef.h>
#include <malloc.h>
#include <memory.h>
#include <assert.h>
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

    //add src to paths first
    path_t src_path = {0, src, 0};
    if (!add_new_path(paths, src_path)) {
        delete_queue(queue);
        delete_shortest_paths(paths);
        return NULL;
    }


    node_t *min_node = src;

    while (min_node != NULL) {
        path_t *min_node_path = get_path(paths, min_node);
        assert(min_node_path);
        for (size_t neighbours = 0; neighbours < min_node->edges.count; ++neighbours) {
            edge_t *edge = &(min_node->edges.edges[neighbours]);
            assert(edge);
            path_t *neighbour_path = get_path(paths, edge->to);
            assert(edge->to);

            if (neighbour_path == NULL) {
                //add new path
                path_t new_path = {min_node_path, edge->to, edge};
                assert(&new_path);
                uint64_t new_path_cost = get_path_cost(&new_path);
                if (!add_new_path(paths, new_path)) {
                    delete_shortest_paths(paths);
                    delete_queue(queue);
                    return NULL;
                }
                insert(queue, new_path_cost, edge->to);
            } else {
                //update path
                uint64_t updated_cost = get_path_cost(min_node_path) + edge->cost;
                if (updated_cost < get_path_cost(neighbour_path)) {
                    neighbour_path->from = min_node_path;
                    neighbour_path->via = edge;
                    update_key_by_value(queue, edge->to, updated_cost);
                }
            }
        }
        min_node = (node_t *) extract_min(queue);
    }

    return paths;
}

bool add_new_path(shortest_paths_t *paths, path_t to_add) {
    uint64_t last_path_index = paths->count;
    ++(paths->count);

    //copy old values in bigger array
    path_t *new_paths = malloc(sizeof(path_t) * paths->count);
    if (new_paths == NULL) {
        return false;
    }
    memcpy(new_paths, paths->paths, last_path_index * sizeof(path_t));
    free(paths->paths);
    paths->paths = new_paths;

    paths->paths[last_path_index] = to_add;
    return true;
}

path_t *get_path(shortest_paths_t *paths, node_t *node) {
    for (int i = 0; i < paths->count; ++i) {
        if (paths->paths[i].to == node) {
            return &paths->paths[i];
        }
    }
    return NULL;
}

shortest_paths_t *create_shortest_paths(const graph_t *graph) {
    shortest_paths_t *paths = malloc(sizeof(shortest_paths_t));
    if (paths == NULL) return NULL;
    paths->paths = NULL;
    paths->count = 0;

    return paths;
}

void delete_shortest_paths(shortest_paths_t *paths) {
    free(paths->paths);
    free(paths);
}

uint64_t get_path_cost(path_t *path) {
    if (path == NULL) {
        return 0U;
    }

    uint64_t cost = 0U;

    if (path->via != NULL) {
        cost += path->via->cost;
    }

    cost += get_path_cost(path->from);

    return cost;
}