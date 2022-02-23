#include "priority_queue.h"
#include "priority_queue_p.h"
#include <malloc.h>

priority_queue_t *create_queue(uint64_t capacity) {
    priority_queue_p_t *q = malloc(sizeof(priority_queue_p_t));

    q->elements = malloc(sizeof(node_t) * capacity);
    if (q->elements == NULL) {
        free(q);
        return NULL;
    }

    q->capacity = capacity;
    q->heap_size = 0;

    return (priority_queue_t *) q;
}

void *extract_min(priority_queue_t *queue) {
    priority_queue_p_t *q = (priority_queue_p_t *) queue;
    return 0;
}

bool insert(priority_queue_t *queue, uint64_t key, void *value) {
    priority_queue_p_t *q = (priority_queue_p_t *) queue;
    return true;
}

void *delete(priority_queue_t *queue, uint64_t key) {
    priority_queue_p_t *q = (priority_queue_p_t *) queue;

    return 0;
}

void heapify(priority_queue_p_t *queue) {}
