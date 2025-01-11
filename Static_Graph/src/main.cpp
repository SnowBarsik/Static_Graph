#include "DynamicGraph.hpp"
#include <iostream>

using namespace std;


int main() {
	//[[1,2],[3],[0],[4,5],[3],[6],[5],[1],[0,2],[8],[9]]
	DynamicGraph<11> graph1({ {1, 2}, {3}, {0}, {4, 5}, {3}, {6}, {5}, {1}, {0, 2}, {8}, {9} });

	cout << graph1.vertex_count() << endl;
	cout << graph1.edge_count() << endl;

	for (auto& neigbourhood : graph1.neigbourhoods(8))
		cout << neigbourhood << " ";

	cout << endl;
	return 0;
}
