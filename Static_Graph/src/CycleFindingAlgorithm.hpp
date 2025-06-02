#pragma once
#include <vector>
#include <iostream>
#include <algorithm>

using VertexType = std::size_t;



template <typename GraphType>
class SCCFinder {
public:

    constexpr SCCFinder(const GraphType& graph) : _graph(graph), _num_vertices(graph.vertex_count()), _time(0) {}

    // Iterative version of Tarjan's SCC algorithm.
    // It takes the graph object and references to arrays/stack for disc, low, SCC stack, and stackMember.
    constexpr std::vector<std::vector<VertexType>> find_SCCs_iterative() {
        std::vector<std::vector<VertexType>> all_SCCs;
        std::vector<VertexType> SCC;
        std::size_t V = _num_vertices;
        std::vector<std::size_t> disc(V, V+1);
        std::vector<std::size_t> low(V, V+1);
        std::vector<VertexType> st;
        std::vector<bool> stackMember(V, false);

        _time = 0; // Reset time for each full run of SCC detection.

        std::vector<std::pair<VertexType, std::size_t>> dfs_iter_stack;

        for (VertexType i = 0; i < V; ++i) {
            if (disc[i] == V+1) { // If vertex 'i' has not been visited yet in the overall DFS.
                dfs_iter_stack.push_back({ i, 0 }); // Push starting node with neighbor index 0.

                while (!dfs_iter_stack.empty()) {
                    VertexType u = dfs_iter_stack.back().first;
                    std::size_t & current_neighbor_idx = dfs_iter_stack.back().second;

                    if (disc[u] == V+1) {
                        disc[u] = low[u] = ++_time; // Set discovery time and initial low-link value.
                        st.push_back(u);                // Push vertex onto the SCC stack.
                        stackMember[u] = true;     // Mark as being on the SCC stack.
                    }

                    bool moved_to_child = false;
                    while (current_neighbor_idx < _graph.neighbourhoods(u).size()) {
                        VertexType v = _graph.neighbourhoods(u)[current_neighbor_idx];
                        current_neighbor_idx++; // Increment for the next iteration of this node's neighbors.

                        if (disc[v] == V+1) { // If 'v' is not visited, "recurse" into it.
                            dfs_iter_stack.push_back({ v, 0 }); // Push 'v' to DFS stack for its own DFS.
                            moved_to_child = true;
                            break; // Break from current node's neighbor loop to process child 'v'.
                        }
                        else if (stackMember[v]) { // 'v' is visited and still on the SCC stack (a back edge).
                            low[u] = std::min(low[u], disc[v]); // Update low-link using discovery time of 'v'.
                        }
                    }

                    if (!moved_to_child) {
                        dfs_iter_stack.pop_back();

                        if (!dfs_iter_stack.empty()) {
                            VertexType parent_of_u_in_dfs_tree = dfs_iter_stack.back().first;
                            low[parent_of_u_in_dfs_tree] = std::min(low[parent_of_u_in_dfs_tree], low[u]);
                        }

                        if (low[u] == disc[u]) {
                            VertexType w;
                            if (!SCC.empty()) SCC.clear();
                            do{
                                w = st.back(); // Get top element from SCC stack.
                                st.pop_back();
                                stackMember[w] = false; // Mark as no longer on SCC stack.
                                SCC.push_back(w);
                            } while (w != u); // Stop when 'u' itself is popped.
                            std::reverse(SCC.begin(), SCC.end());
                            all_SCCs.push_back(SCC);
                        }
                    }
                }
            }
        }

        return all_SCCs;
    }
private:
    const GraphType& _graph;
    std::size_t _num_vertices;
    int _time; // Global time counter for discovery times, managed by this class instance.
};

// Assuming V is the number of vertices, which can be obtained from the graph object
template <typename GraphType>
class SzwarcfiterLauerCycleFinder {

private:

    constexpr void no_cycle(VertexType v, VertexType w, std::vector<std::vector<VertexType>>& A, std::vector<std::vector<VertexType>>& B) {
        B[w].push_back(v);
        A[v][w] = V + 1;
    }

    constexpr void unmark(VertexType v, std::vector<bool>& mark, std::vector<std::vector<VertexType>>& A, std::vector<std::vector<VertexType>>& B) {
        mark[v] = false;
        VertexType u;
        for (size_t i = 0; i < B[v].size(); ++i) {
            u = B[v][i];
            A[u][v] = v;
            if (mark[u]) unmark(u, mark, A, B);
        }
        //B[v].clear();
        while (B[v].size()) B[v].pop_back();

    }

    constexpr bool cycle_util(VertexType v, std::size_t q, std::vector<VertexType>* st, std::vector<std::vector<VertexType>>& A,
        std::vector<std::vector<VertexType>>& B, std::vector<bool>& reach, std::vector<bool>& mark,
                            std::vector<std::size_t>& position, std::vector<std::vector<VertexType>>& all_cycles) {
        bool f = false;
        VertexType w;
        mark[v] = true;
        st->push_back(v);
        std::size_t t = st->size();
        position[v] = t;
        if (!reach[v]) q = t;
        for (const auto& i : _graph.neighbourhoods(v)) {
            if (A[v][i] != V+1) {
                if (!mark[i]) {
                    if (cycle_util(i, q, st, A, B, mark, reach, position, all_cycles)) f = true;
                    else no_cycle(v, i, A, B);
                }
                else {
                    if (position[i] <= q && position[i] != V+1){
                        if (!all_cycles.back().empty()) {
                            std::reverse(all_cycles.back().begin(), all_cycles.back().end());
                            all_cycles.push_back(std::vector<VertexType>());
                        }

                        all_cycles.push_back(*st);
                        all_cycles.back().push_back(i);
                        f = true;
                    }
                    else no_cycle(v, i, A, B);
                }
            }
        }
        w = (VertexType)st->back();
        st->pop_back();
        if (f) unmark(v, mark, A, B);
        reach[v] = true;
        position[v] = V + 1;
        return f;
    }

    const GraphType& _graph;
    std::size_t V;

public:
    constexpr SzwarcfiterLauerCycleFinder(const GraphType& graph) : _graph(graph), V(graph.vertex_count()) {}

    constexpr std::vector<std::vector<VertexType>> find_cycles() {
        std::vector<VertexType> st;
        std::vector<std::vector<VertexType>> all_cycles (V);
        SCCFinder<GraphType> finder_SCC(_graph);
        std::vector<std::vector<VertexType>> SCCs = finder_SCC.find_SCCs_iterative();
        std::vector<std::vector<VertexType>> A(V, std::vector<VertexType>(V, V + 1));
        A.push_back(std::vector<VertexType>(V, 0));
        std::vector<std::vector<VertexType>> B(V);
        std::vector<bool> reach(V, false);
        std::vector<bool> mark(V, false);
        std::vector<std::size_t> position(V, V + 1);
        VertexType s;
        for (const auto& SCC : SCCs) {
            if (SCC.size() > 1) {
                s = 0;
                for (size_t i = 0; i < SCC.size(); ++i) {
                    VertexType v = SCC[i];
                    for (const VertexType w : _graph.neighbourhoods(v)) {
                        if (std::find(SCC.begin(), SCC.end(), w) != SCC.end()) {
                            A[v][w] = w;
                            A[V][v]++;
                        }
                    }
                    if (A[V][v] > s) s = v;
                }
                all_cycles.push_back(std::vector<VertexType>());
                std::size_t q = 0;
                cycle_util(s, q, &st, A, B, mark, reach, position, all_cycles);
            }
        }
        return all_cycles;
    }

};
