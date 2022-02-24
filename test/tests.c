#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/dijkstra_shortest_path.h"

// (n0) - 1 > (n1)
//  |          |
//  5          1
//  Y          Y
// (n3) < 1 - (n2)
//
// less hops -> n1->n3
// less cost -> n1->n2->n4->n3
void test_small() {
    node_t nodes[4];

    edge_t n0_e[2];
    n0_e[0].to = &nodes[1];
    n0_e[0].cost = 1;
    n0_e[1].to = &nodes[3];
    n0_e[1].cost = 5;
    edges_t e_n0 = {2, n0_e};
    nodes[0].edges = e_n0;

    edge_t n1_e = {&nodes[2], 1};
    edges_t e_n1 = {1, &n1_e};
    nodes[1].edges = e_n1;

    edge_t n2_e = {&nodes[3], 1};
    edges_t e_n2 = {1, &n2_e};
    nodes[2].edges = e_n2;

    nodes[3].edges.count = 0U;

    graph_t graph = {4, nodes};

    shortest_paths_t *paths = get_shortest_paths(&nodes[0], &graph);
    if (paths == NULL) exit(1);

    //find path to n3 and check correct values
    for (uint64_t i = 0U; i < paths->count; ++i) {
        if (paths->paths[i].to == &nodes[3]) {
            path_t path = paths->paths[i];
            if (get_path_cost(&path) != 3) {
                printf("path n0 -> n3 not correct!\n");
                printf("should cost 3 but was %zu\n", get_path_cost(&path));
                exit(1);
            }
            delete_shortest_paths(paths);
            return;
        }
    }

    printf("couldn't find paths!\n");
    exit(1);
}

void test_get_path_size() {
    node_t nodes[3];

    path_t start = {NULL, &nodes[0], NULL};
    get_path_cost(&start);

    path_t empty_next = {&start, &nodes[1], NULL};
    get_path_cost(&empty_next);

    edge_t edge_1 = {&nodes[1], 5};
    path_t next_1 = {&empty_next, &nodes[3], &edge_1};
    assert(get_path_cost(&next_1) == 5);

    edge_t edge_2 = {&nodes[2], 5};
    path_t next_2 = {&next_1, &nodes[3], &edge_2};
    assert(get_path_cost(&next_2) == 10);
}

int main() {
    //list all test which fail program when failing
//    test_small();
    test_get_path_size();

    printf("test successfully done!");
    return 0;
}