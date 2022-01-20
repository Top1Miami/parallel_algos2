#include <benchmark/benchmark.h>
#include "src/graph.h"
#include "src/bfs.h"

void benchPar(benchmark::State& state) {
	int cubeLen = state.range(0);
	auto graph = buildGraph(cubeLen);
	for (auto _: state) {
		auto dist = parBfs(graph.size(), 0, graph);
		benchmark::ClobberMemory();
	}
}

void benchSeq(benchmark::State& state) {
	int cubeLen = state.range(0);
	auto graph = buildGraph(cubeLen);
	for (auto _: state) {
		auto dist = seqBfs(graph.size(), 0, graph);
		benchmark::ClobberMemory();
	}
}

BENCHMARK(benchPar)
	->DenseRange(100, 200, 50)
	->ArgName("cubeLen")
	->Iterations(5)
	->Unit(benchmark::kSecond);


BENCHMARK(benchSeq)
	->DenseRange(100, 200, 50)
	->ArgName("cubeLen")
	->Iterations(5)
	->Unit(benchmark::kSecond);