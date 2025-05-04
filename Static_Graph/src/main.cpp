#include "DynamicGraph.hpp"
#include "Algorithms.hpp"
#include <iostream>
//#include <functional>

using namespace std;

template<typename Iterable>
void print(const Iterable& to_print)
{
	for (const auto& item : to_print) {
		std::cout << item << " ";
	}
	cout << endl;
}

void double_plus2(int& num) {
	num = num * 2 + 2;
}

//void map(vector<int>& list, void(*func)(int&) ) {
//	for (int& elem : list) func(elem);
//}

//void map(vector<int>& list, std::function<void(int&)> func) {
//	for (int& elem : list) func(elem);
//}

template<typename Func>
void map(vector<int>& list, Func&& func) {
	for (int& elem : list) func(elem);
}

int main() {
	int multiplier = 4;
	//[[1,2],[3],[0],[4,5],[3],[6],[5],[1],[0,2],[8],[9]]
	//vector<int> v_test = { 1,5,3,8,20,-5 };
	//print(v_test);
	//map(v_test, &double_plus2);
	////map(v_test, nullptr);
	//map(v_test, [](int& num) {
	//	num = num * 2 + 2;
	//	}
	//);
	//map(v_test, [&multiplier](int& num) {
	//	num = num * multiplier + 2;
	//	}
	//);
	//print(v_test);

	DynamicGraph<11> graph1({ {1, 2}, {3, 0}, {0}, {4, 5}, {3}, {6}, {5}, {1}, {0, 2}, {8}, {9} });

	cout << graph1.vertex_count() << endl;
	cout << graph1.edge_count() << endl;
	vector<vector<VertexType>> ways = {};
	vector<VertexType> way = {};

	//first_dfs_way(way, graph1, 1);
	//all_dfs_ways(ways, graph1, 1);

	dfs_util(graph1, 10, [](VertexType v_start) {cout << v_start << " "; });
	cout << endl;
	all_dfs_ways(ways, graph1, 10);

	bfs_util(graph1, 10, [](VertexType v_start) {cout << v_start << " "; });

	cout << endl;

	print(way);

	cout << endl;
	for (auto& elem : ways) print(elem);
	cout << endl;

	for (auto& neigbourhood : graph1.neigbourhoods(8))
		cout << neigbourhood << " ";

	cout << endl;
	return 0;
}
