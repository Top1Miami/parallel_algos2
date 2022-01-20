#include <gtest/gtest.h>

#include "src/bfs.h"
#include "src/graph.h"
#include <cstdint>
#include <iostream>

int manhattanDistance(int x, int y, int z) {
	return x + y + z;
}

TEST(Gen, test1) {
	ASSERT_EQ(111, getNodeNumberInGraph(1, 1, 1, 10));
	ASSERT_EQ(0, getNodeNumberInGraph(0, 0, 0, 10));
	ASSERT_EQ(999, getNodeNumberInGraph(9, 9, 9, 10));
}

TEST(Gen, test2) {
	auto graph = buildGraph(3);
	std::vector<std::vector<int64_t>> baseLineGraph = {
		{1, 3, 9},
		{0, 2, 4, 10},
		{1, 5, 11},
		{4, 0, 6, 12},
		{3, 5, 1, 7, 13},
		{4, 2, 8, 14},
		{7, 3, 15},
		{6, 8, 4, 16},
		{7, 5, 17},
		{10, 12, 0, 18},
		{9, 11, 13, 1, 19},
		{10, 14, 2, 20},
		{13, 9, 15, 3, 21},
		{12, 14, 10, 16, 4, 22},
		{13, 11, 17, 5, 23},
		{16, 12, 6, 24},
		{15, 17, 13, 7, 25},
		{16, 14, 8, 26},
		{19, 21, 9},
		{18, 20, 22, 10},
		{19, 23, 11},
		{22, 18, 24, 12},
		{21, 23, 19, 25, 13},
		{22, 20, 26, 14},
		{25, 21, 15},
		{24, 26, 22, 16},
		{25, 23, 17}
	};
	ASSERT_EQ(baseLineGraph, graph);
}

TEST(SeqBfs, test1) {
	int graphSize = 100;
	auto graph = buildGraph(graphSize);
	auto dist = seqBfs(graph.size(), 0, graph);
	for (int z = 0; z < graphSize;z++) {
		for (int y = 0; y < graphSize;y++) {
			for (int x = 0; x < graphSize;x++) {
				int nodeNumber = getNodeNumberInGraph(x, y, z, graphSize);
				ASSERT_EQ(manhattanDistance(x, y, z), dist[nodeNumber]);
			}
		}
	}
}

TEST(ParBfs, test1) {
	int graphSize = 100;
	auto graph = buildGraph(graphSize);
	auto dist = parBfs(graph.size(), 0, graph);
	for (int z = 0; z < graphSize;z++) {
		for (int y = 0; y < graphSize;y++) {
			for (int x = 0; x < graphSize;x++) {
				int nodeNumber = getNodeNumberInGraph(x, y, z, graphSize);
				ASSERT_EQ(manhattanDistance(x, y, z), dist[nodeNumber]);
			}
		}
	}
}


