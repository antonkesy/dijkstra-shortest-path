#include <stdio.h>
#include <stdlib.h>
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

    edge_t n1_e[2];
    //
    n1_e[0].to = &nodes[4];
    n1_e[0].cost = 1;
    //
    n1_e[1].to = &nodes[1];
    n1_e[1].cost = 5;

    edge_t n2_e = {&nodes[3], 1};
    edge_t n4_3 = {&nodes[2], 1};

    edges_t e_n0 = {2, n1_e};
    nodes[0].edges = e_n0;

    edges_t e_n1 = {1, &n2_e};
    nodes[1].edges = e_n1;

    edges_t e_n2 = {1, &n4_3};
    nodes[2].edges = e_n2;

    graph_t graph = {4, nodes};

    shortest_paths_t *paths = get_shortest_paths(&nodes[0], &graph);
    if (paths == NULL) exit(-1);

    //find path to n3 and check correct values
    for (uint64_t i = 0U; i < paths->count; ++i) {
        if (paths->paths[i].dest == &nodes[3]) {
            shortest_path_t path = paths->paths[i];
            if (path.cost != 1 || path.hops != 1 && path.nodes != &nodes[3]) {
                printf("paht n0 -> n3 not correct!\n");
                exit(-1);
            }
        }
    }


    delete_shortest_paths(paths);
}

int main() {
    //list all test which fail program when failing
    test_small();

    printf("test successfully done!");
    return 0;
}