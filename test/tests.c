#include <stdio.h>
#include "../include/dijkstra_shortest_path.h"

void test_small() {
    node_t n1 = {1, NULL};
    node_t n2 = {2, NULL};
    node_t n4 = {2, NULL};
    node_t n5 = {1, NULL};

}

int main() {
    //list all test which fail program when failing
    test_small();

    printf("test successfully done!");
    return 0;
}