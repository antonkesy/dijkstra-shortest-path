#ifndef DIJKSTRA_SHORTEST_PATH_PRIORITY_QUEUE_P_H
#define DIJKSTRA_SHORTEST_PATH_PRIORITY_QUEUE_P_H

#include <stdint.h>
#include "priority_queue.h"

#define PARENT(i)(((uint64_t)i-1U)/2U)
#define LEFT(i)(2U*(uint64_t)i+1U)
#define RIGHT(i)(2U*(uint64_t)i+2U)

typedef struct {
    uint64_t key;
    void *value;
} node_t;


typedef struct {
    node_t *elements;
    uint64_t capacity;
    uint64_t heap_size;
} priority_queue_p_t;

void heapify(priority_queue_p_t *queue, uint64_t index);

void swap(node_t *a, node_t *b);

void decrease_key(priority_queue_p_t *queue, uint64_t index, uint64_t new_value);

#endif //DIJKSTRA_SHORTEST_PATH_PRIORITY_QUEUE_P_H
