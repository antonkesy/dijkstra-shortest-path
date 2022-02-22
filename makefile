all: directories DIJKSTRA_SHORTEST_PATH_LIB_STATIC
BIN_DIR = bin
TEST_BIN_DIR = ${BIN_DIR}/tests
LIB_DIR = lib
DIRS=${BIN_DIR} ${LIB_DIR} ${TEST_BIN_DIR}

DIJKSTRA_SHORTEST_PATH_LIB_STATIC= ${LIB_DIR}/libdijkstrashortest_path.a
SHORTEST_PATH_O = ${BIN_DIR}/dijkstra_shortest_path.o
PRIORITY_QUE_O = ${BIN_DIR}/priority_queue.o
TESTS = ${TEST_BIN_DIR}/tests

.PHONY: directories clean

DIJKSTRA_SHORTEST_PATH_LIB_STATIC: SHORTEST_PATH_O PRIORITY_QUE_O
	ar rcs ${$@} ${SHORTEST_PATH_O} ${PRIORITY_QUE_O}

SHORTEST_PATH_O: include/dijkstra_shortest_path.h src/dijkstra_shortest_path.c
	gcc src/dijkstra_shortest_path.c -c -o ${$@}

PRIORITY_QUE_O: src/priority_queue/priority_queue.h src/priority_queue/priority_queue.c
	gcc src/priority_queue/priority_queue.c -c -o ${$@}

TESTS: test/tests.c DIJKSTRA_SHORTEST_PATH_LIB_STATIC
	gcc $< ${DIJKSTRA_SHORTEST_PATH_LIB_STATIC} -o ${$@}
	./${TESTS}

directories:
	mkdir -p ${DIRS}

clean:
	-rm ${DIRS} -drf