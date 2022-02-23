#ifndef DIJKSTRA_SHORTEST_PATH_PRIORITY_QUEUE_H
#define DIJKSTRA_SHORTEST_PATH_PRIORITY_QUEUE_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {} priority_queue_t;

priority_queue_t *create_queue(uint64_t capacity);

void *extract_min(priority_queue_t *queue);

bool insert(priority_queue_t *queue, uint64_t key, void *value);

void *delete(priority_queue_t *queue, uint64_t key);

#endif //DIJKSTRA_SHORTEST_PATH_PRIORITY_QUEUE_H
