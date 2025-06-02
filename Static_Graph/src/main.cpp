#include "DynamicGraph.hpp"
#include "Algorithms.hpp"
#include "CycleFindingAlgorithm.hpp"
#include "Diagram.hpp"
#include <iostream>
#include "HierarchyToGraphConverter.hpp"
#include "ExampleOfHierarchy.hpp"

using namespace std;

static const auto graph = Converter4::graph_of_hierarchy();

bool cycle_test_dy() {
    SzwarcfiterLauerCycleFinder finder(graph);
    std::vector<std::vector<VertexType>> cycles = finder.find_cycles();

    return true;
}

//static constexpr auto graph_c = Converter4::cb_graph_of_hierarchy();
//
//
//constexpr bool cycle_test_cb() {
//    SzwarcfiterLauerCycleFinder finder(graph_c);
//    std::vector<std::vector<VertexType>> cycles = finder.find_cycles();
//    return true;
//}


int main()
{
    bool result = cycle_test_dy();
    //static constexpr bool result = cycle_test_cb();
    cout << result;
	return 0;
}
