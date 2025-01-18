#pragma warning(push)
#pragma warning(disable : 26495) 
#include "pch.h"
#pragma warning(pop)
#include "../Static_Graph/src/DynamicGraph.hpp"
#include "../Static_Graph/src/Algorithms.hpp"

template<std::size_t V>
void traverse(const DynamicGraph<V>& graph, VertexType v_start) {
	std::vector<VertexType> dfs_result = {};
	dfs_result.reserve(V);
	dfs_util(graph, v_start, [&dfs_result](VertexType v) mutable {
		dfs_result.push_back(v);
		});
	if(v_start>=V) {
		EXPECT_TRUE(dfs_result.empty());
		return;
	}
	std::set<VertexType> expected_visited_vertices = {};
#pragma warning(push)
#pragma warning(disable : 6294) //disable ill-defined loop warnings
	for (VertexType i = 0; i < V; i++) {
		expected_visited_vertices.insert(i);
	}
	for (std::size_t i = 0; i < V; i++) {
		EXPECT_TRUE(expected_visited_vertices.contains(dfs_result[i]));
	}
#pragma warning(pop)
}

TEST(TraverseAllVerticesDFS, DynamicGraph_dfs_test) {
	const std::size_t V = 11;
	DynamicGraph<V> graph({ {1, 2}, {3, 0, 7}, {0}, {4, 5}, {3}, {6}, {5}, {}, {0, 2}, {8}, {9} });
	traverse(graph, 10);
}

TEST(EmptyGraphDFS, DynamicGraph_dfs_test) {
	const std::size_t V = 0;
	DynamicGraph<V> graph({});
	EXPECT_THROW(traverse(graph, 3), std::invalid_argument);
}
