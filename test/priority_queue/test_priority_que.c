#include <stdio.h>
#include <stdlib.h>
#include "../../src/priority_queue/priority_queue.h"

void test_insert_extract_min() {
    const size_t elements = 1000U;
    priority_queue_ptr_t q = create_queue(elements);
    size_t values[elements];
    for (size_t i = 0U; i < elements; ++i) {
        size_t key_value = elements - i - 1;
        values[i] = key_value;
        insert(q, key_value, &values[i]);
    }

    for (size_t i = 0U; i < elements; ++i) {
        size_t min = *(size_t *) extract_min(q);
        if (min != i) {
            printf("insert failed! expected=%zu, but was=%zu not correct!\n", i, min);
            exit(-1);
        }
    }

    delete_queue(q);
}

int main() {
    test_insert_extract_min();
    printf("priority queue tests successfully done!");
    return 0;
}