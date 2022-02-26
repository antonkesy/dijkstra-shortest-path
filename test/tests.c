#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/dijkstra_shortest_path.h"

void
test_path(const char *name, const path_t *path, uint64_t expected_cost, uint64_t extra_hop_count, node_t *over,
          ...);

// (n0) - 1 > (n1)
//  |          |
//  9          2
//  Y          Y
// (n3) < 3 - (n2)
//
// less hops -> n1->n3
// less cost -> n1->n2->n4->n3
void test_small() {
    node_t nodes[4];

    edge_t n0_e[2];
    n0_e[0].to = &nodes[1];
    n0_e[0].cost = 1;
    n0_e[1].to = &nodes[3];
    n0_e[1].cost = 9;
    edges_t e_n0 = {2, n0_e};
    nodes[0].edges = e_n0;

    edge_t n1_e = {&nodes[2], 2};
    edges_t e_n1 = {1, &n1_e};
    nodes[1].edges = e_n1;

    edge_t n2_e = {&nodes[3], 3};
    edges_t e_n2 = {1, &n2_e};
    nodes[2].edges = e_n2;

    nodes[3].edges.count = 0U;

    graph_t graph = {4, nodes};

    shortest_paths_t *paths = get_shortest_paths(&nodes[0], &graph);
    if (paths == NULL) exit(1);

    path_t *p_0_to_i_1[3];
    //find path to n3 and check correct values
    for (uint64_t i = 0U; i < paths->count; ++i) {
        for (unsigned int j = 0U; j < 3U; ++j) {
            if (paths->paths[i].via->to == &nodes[j + 1])
                p_0_to_i_1[j] = &paths->paths[i];
        }
    }

    test_path("n0->n1", p_0_to_i_1[0], 1U, 0U, NULL);
    test_path("n0->n2", p_0_to_i_1[1], 3U, 1U, &nodes[1]);
    test_path("n0->n3", p_0_to_i_1[2], 6U, 2U, &nodes[1], &nodes[2]);

}

void
test_path(const char *name, const path_t *path, uint64_t expected_cost, uint64_t extra_hop_count, node_t *over,
          ...) {
    uint64_t cost = get_path_cost(path);
    if (cost != expected_cost) {
        printf("path %s not correct!\n", name);
        printf("should cost %zu but was %zu\n", expected_cost, cost);
        exit(1);
    }

    //walk path backwards and check edges to nodes
    uint64_t it = 0U;
    path_t *path_backwards = path->from;
    while (path_backwards != NULL && path_backwards->from != NULL && over != NULL) {
        if (path_backwards->via->to != &over[extra_hop_count - 1 - it]) {
            printf("path %s not correct at hop %zu \n", name, (extra_hop_count - it));
            exit(1);
        }
        path_backwards = path_backwards->from;
        ++it;
    }
}

void test_get_path_size() {
    node_t nodes[3];

    path_t start = {NULL, NULL};
    get_path_cost(&start);

    path_t empty_next = {&start, NULL};
    get_path_cost(&empty_next);

    edge_t edge_1 = {&nodes[1], 5};
    path_t next_1 = {&empty_next, &edge_1};
    assert(get_path_cost(&next_1) == 5);

    edge_t edge_2 = {&nodes[2], 5};
    path_t next_2 = {&next_1, &edge_2};
    assert(get_path_cost(&next_2) == 10);
}

int main() {
    //list all test which fail program when failing
    test_small();
    test_get_path_size();

    printf("dijkstra tests successfully done!");
    return 0;
}