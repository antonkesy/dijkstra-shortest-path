#include "priority_queue.h"
#include "priority_queue_p.h"
#include <malloc.h>

priority_queue_ptr_t create_queue(uint64_t capacity) {
    priority_queue_p_t *q = malloc(sizeof(priority_queue_p_t));

    q->elements = malloc(sizeof(node_t) * capacity);
    if (q->elements == NULL) {
        free(q);
        return NULL;
    }

    q->capacity = capacity;
    q->heap_size = 0;

    return (priority_queue_ptr_t) q;
}

void *extract_min(priority_queue_ptr_t queue) {
    priority_queue_p_t *q = (priority_queue_p_t *) queue;

    if (q->heap_size == 0) {
        return NULL;
    }

    //has values -> always decreased
    --(q->heap_size);

    //only 1 element
    if (q->heap_size == 0) {
        return q->elements[0].value;
    }

    //multiple elements
    void *root_value = q->elements[0].value;
    q->elements[0] = q->elements[q->heap_size];
    heapify(q, 0);

    return root_value;
}

bool insert(priority_queue_ptr_t queue, uint64_t key, void *value) {
    priority_queue_p_t *q = (priority_queue_p_t *) queue;
    if (q->capacity == q->heap_size) return false;

    uint64_t index = q->heap_size;
    ++(q->heap_size);

    q->elements[index].value = value;

    decrease_key(q, index, key);

    return true;
}

bool update_key(priority_queue_ptr_t queue, uint64_t key, uint64_t new_value) {
    priority_queue_p_t *q = (priority_queue_p_t *) queue;

    for (uint64_t i = 0U; i < q->heap_size; ++i) {
        if (q->elements[i].key == key) {
            q->elements[i].key = new_value;
            //TODO really need to go from root?
            heapify(q, 0);
            return true;
        }
    }


    return false;
}

void heapify(priority_queue_p_t *queue, uint64_t index) {
    uint64_t left = LEFT(index);
    uint64_t right = RIGHT(index);
    uint64_t smallest = index;
    if (left < queue->heap_size && queue->elements[left].key < queue->elements[index].key)
        smallest = left;
    if (right < queue->heap_size && queue->elements[right].key < queue->elements[smallest].key)
        smallest = right;
    if (smallest != index) {
        swap(&queue->elements[index], &queue->elements[smallest]);
        heapify(queue, smallest);
    }
}

void swap(node_t *a, node_t *b) {
    node_t t = *a;
    *a = *b;
    *b = t;
}

void decrease_key(priority_queue_p_t *queue, uint64_t index, uint64_t new_value) {
    queue->elements[index].key = new_value;

    while (index != 0 && queue->elements[PARENT(index)].key > queue->elements[index].key) {
        swap(&queue->elements[index], &queue->elements[PARENT(index)]);
        index = PARENT(index);
    }

}

void delete_queue(priority_queue_ptr_t queue) {
    priority_queue_p_t *q = (priority_queue_p_t *) queue;
    free(q->elements);
    free(q);
}
