#pragma once


#include <vector>
#include <cstdint>
#include <queue>
#include <atomic>
#include <functional>
#include <parray.hpp>
#include <datapar.hpp>
#include <iostream>

#define NOT_VISITED -1

std::vector<int64_t> seqBfs(
	int64_t numberOfNodes, int64_t start,
	std::vector<std::vector<int64_t>> edges) {
	
	std::vector<int64_t> dist(numberOfNodes, NOT_VISITED);
	std::queue<int64_t> q;
	dist[start] = 0;
	q.push(start);

	while (!q.empty()) {
		int64_t cur = q.front();
		q.pop();
		for (auto next : edges[cur]) {
			if (dist[next] == NOT_VISITED) {
				dist[next] = dist[cur] + 1;
				q.push(next);
			}
		}
	}
	return dist;
}

pasl::pctl::parray<int64_t> parBfs(
	int64_t numberOfNodes, int64_t start,
	std::vector<std::vector<int64_t>> edges) {

	pasl::pctl::parray<int64_t> dist(numberOfNodes, static_cast<int64_t>(NOT_VISITED));
	dist[start] = 0;
	pasl::pctl::parray<int64_t> frontier = {static_cast<int64_t>(start)};

	while(frontier.size() != 0) {
		pasl::pctl::parray<int64_t> numberOfNeighbors(frontier.size(), [&frontier, &edges](int64_t i) {
			return edges[frontier[i]].size();
		});
		pasl::pctl::parray<int64_t> scanSum = pasl::pctl::scan(numberOfNeighbors.begin(), numberOfNeighbors.end(), static_cast<int64_t>(0),
			[](int64_t first, int64_t second) {
				return first + second;
			}, pasl::pctl::scan_type::forward_exclusive_scan);
		pasl::pctl::parray<int64_t> nextFrontier(scanSum[scanSum.size() - 1] + numberOfNeighbors[numberOfNeighbors.size() - 1], static_cast<int64_t>(NOT_VISITED));
		pasl::pctl::parallel_for((long) 0, frontier.size(), [&](long i) {
			int64_t curNode = frontier[i];
			std::vector<int64_t> curEdges = edges[curNode];
			for (auto nextNode : curEdges) {
				int64_t ebuchiePlusi = NOT_VISITED;
				int64_t nextDist = __atomic_load_n(&dist[curNode], __ATOMIC_SEQ_CST) + 1;
				if (__atomic_compare_exchange_n(&dist[nextNode], &ebuchiePlusi, nextDist, false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) {
					nextFrontier[scanSum[i]++] = nextNode;
				}
			}
		});
		frontier = pasl::pctl::filter(nextFrontier.begin(), nextFrontier.end(),[](int64_t curNode){
			return curNode != NOT_VISITED;
		});
	}
	return dist;
}