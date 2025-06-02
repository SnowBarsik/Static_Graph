#include <iostream>
#include <vector>
#include "DynamicGraph.hpp"
#include "CycleFindingAlgorithm.hpp"
#include "Diagram.hpp"
#include "HierarchyToGraphConverter.hpp"
#include "ExampleOfHierarchy.hpp"

using namespace std;

static const auto graph = Converter2::graph_of_hierarchy();

void SCC_and_cycle(){
    for (VertexType i = 0; i < graph.vertex_count(); i++) {
        cout << "[";
        for (auto& neigbourhood : graph.neighbourhoods(i))
            cout << neigbourhood << " ";
        cout << "]" << endl;
    }

    SzwarcfiterLauerCycleFinder finder(graph);
    std::vector<std::vector<VertexType>> cycles = finder.find_cycles();

    std::cout << "Cycles found:" << std::endl;
    for (const auto& cycle : cycles) {
        for (VertexType node : cycle) {
            std::cout << node << " ";
        }
        std::cout << std::endl;
    }

    //main_SCC();

    SCCFinder finder_SCC(graph);
    std::vector<std::vector<VertexType>> SCCs = finder_SCC.find_SCCs_iterative();

    std::cout << "SCCs found:" << std::endl;
    for (const auto& SCC : SCCs) {
        for (VertexType node : SCC) {
            std::cout << node << " ";
        }
        std::cout << std::endl;
    }
}