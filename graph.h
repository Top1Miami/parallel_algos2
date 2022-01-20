#include <vector>
#include <cstdint>
#include <iostream>

int64_t getNodeNumberInGraph(int x, int y, int z, int cubeLen) {
	return x + y * cubeLen + z * cubeLen * cubeLen;
}

std::vector<std::vector<int64_t>> buildGraph(int cubeLen) {
	std::vector<std::vector<int64_t>> graph(cubeLen * cubeLen * cubeLen);
	for (int z = 0; z < cubeLen;z++) {
		for (int y = 0; y < cubeLen;y++) {
			for (int x = 0; x < cubeLen;x++) {
				int64_t curNode = getNodeNumberInGraph(x, y, z, cubeLen);
				if (x != 0) { 
					int64_t neighbor = getNodeNumberInGraph(x - 1, y, z, cubeLen);
					graph[curNode].push_back(neighbor);
				}
				if (x != cubeLen - 1) {
					int64_t neighbor = getNodeNumberInGraph(x + 1, y, z, cubeLen);
					graph[curNode].push_back(neighbor);
				}
				if (y != 0) { 
					int64_t neighbor = getNodeNumberInGraph(x, y - 1, z, cubeLen);
					graph[curNode].push_back(neighbor);
				}
				if (y != cubeLen - 1) {
					int64_t neighbor = getNodeNumberInGraph(x, y + 1, z, cubeLen);
					graph[curNode].push_back(neighbor);
				}
				if (z != 0) { 
					int64_t neighbor = getNodeNumberInGraph(x, y, z - 1, cubeLen);
					graph[curNode].push_back(neighbor);
				}
				if (z != cubeLen - 1) {
					int64_t neighbor = getNodeNumberInGraph(x, y, z + 1, cubeLen);
					graph[curNode].push_back(neighbor);
				}
			}
		}
	}
	return graph;
}