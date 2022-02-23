#ifndef DIJKSTRA_SHORTEST_PATH_PRIORITY_QUEUE_P_H
#define DIJKSTRA_SHORTEST_PATH_PRIORITY_QUEUE_P_H

#include <stdint.h>
#include "priority_queue.h"

#define PARENT(i)((uint64_t)i-2)/2
#define LEFT(i)(2*(uint64_t)i+(uint64_t)i)
#define RIGHT(i)(2*(uint64_t)i+2)

typedef struct {
    uint64_t key;
    void *value;
} node_t;

typedef struct {
    node_t *elements;
    uint64_t capacity;
    uint64_t heap_size;
} priority_queue_p_t;

void heapify(priority_queue_p_t *queue);

#endif //DIJKSTRA_SHORTEST_PATH_PRIORITY_QUEUE_P_H
