#include <iostream>
#include <vector>
#include "DynamicGraph.hpp"
#include "Algorithms.hpp"
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

void algo_test() {

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

    for (auto& neighbourhood : graph1.neighbourhoods(8))
        cout << neighbourhood << " ";

    cout << endl;
}

// program to find strongly connected components in a
// given directed graph using Tarjan's algorithm (single
// DFS)
#include <algorithm>
#include <iostream>
#include <list>
#include <stack>
#include <vector>

#define NIL -1
using namespace std;

// A class that represents a directed graph
template<int V>
class Graph {
    list<int>* adj; // A dynamic array of adjacency lists

    // A Recursive DFS based function used by SCC()
    std::vector<std::vector<int>> SCCUtil(int u, int disc[], int low[],
        stack<int>* st, bool stackMember[], std::vector<std::vector<int>>& SCCs);
    bool cycle(int v, int q, stack<int>* st, int A[V][V + 1],
        std::vector<std::vector<int>> B, bool mark[], bool reach[], int position[], std::vector<std::vector<int>>& cycles);
    void no_cycle(int v, int w, int A[V][V + 1], std::vector<std::vector<int>> B);
    void unmark(int v, bool mark[], int A[V][V + 1], std::vector<std::vector<int>> B);

public:
    Graph(); // Constructor
    void
        addEdge(int v,
            int w); // function to add an edge to the graph
    std::vector<std::vector<int>> SCC(); // prints strongly connected components
    std::vector<std::vector<int>> cycle_finding();
};
template<int V>
Graph<V>::Graph()
{
    adj = new list<int>[V];
}

template<int V>
void Graph<V>::addEdge(int v, int w) { adj[v].push_back(w); }

// A recursive function that finds and prints strongly
// connected components using DFS traversal
template<int V>
std::vector<std::vector<int>> Graph<V>::SCCUtil(int u, int disc[], int low[],
    stack<int>* st, bool stackMember[], std::vector<std::vector<int>>& SCCs)
{
    std::vector<int> SCC;
    // A static variable is used for simplicity, we can
    // avoid use of static variable by passing a pointer.
    static int time = 0;

    // Initialize discovery time and low value
    disc[u] = low[u] = ++time;
    st->push(u);
    stackMember[u] = true;

    // Go through all vertices adjacent to this
    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i) {
        int v = *i; // v is current adjacent of 'u'

        // If v is not visited yet, then recur for it
        if (disc[v] == -1) {
            SCCUtil(v, disc, low, st, stackMember, SCCs);

            // Check if the subtree rooted with 'v' has a
            // connection to one of the ancestors of 'u'
            low[u] = min(low[u], low[v]);
        }
        // Update low value of 'u' only if 'v' is still in
        // stack (i.e., it's a back edge, not a cross edge)
        else if (stackMember[v] == true)
            low[u] = min(low[u], disc[v]);
    }

    // Head node found, pop the stack and print an SCC
    int w = 0; // To store stack extracted vertices
    if (low[u] == disc[u]) {
        SCC.clear();
        while (st->top() != u) {
            w = (int)st->top();
            cout << w << " ";
            stackMember[w] = false;
            st->pop();
            SCC.push_back(w);
        }
        w = (int)st->top();
        cout << w << "\n";
        stackMember[w] = false;
        st->pop();
        SCC.push_back(w);
        SCCs.push_back(SCC);
    }
    return SCCs;
}

// The function to do DFS traversal. It uses SCCUtil()
template<int V>
std::vector<std::vector<int>> Graph<V>::SCC()
{
    int* disc = new int[V];
    int* low = new int[V];
    bool* stackMember = new bool[V];
    stack<int>* st = new stack<int>();
    std::vector<std::vector<int>> SCCs;

    // Initialize disc and low, and stackMember arrays
    for (int i = 0; i < V; i++) {
        disc[i] = NIL;
        low[i] = NIL;
        stackMember[i] = false;
    }

    // Call the recursive helper function to find strongly
    // connected components in DFS tree with vertex 'i'
    for (int i = 0; i < V; i++)
        if (disc[i] == NIL)
            SCCs = SCCUtil(i, disc, low, st, stackMember, SCCs);

    // Free allocated memory
    delete[] disc;
    delete[] low;
    delete[] stackMember;
    delete st;
    return SCCs;
}

template<int V>
std::vector<std::vector<int>> Graph<V>::cycle_finding() {
    std::vector<std::vector<int>> cycles(V);
    int A[V][V + 1]{};
    std::vector<std::vector<int>> B(V);
    stack<int>* st = new stack<int>();
    bool* reach = new bool[V];
    bool* mark = new bool[V];
    int* position = new int[V];
    fill(reach, reach + V, false);
    fill(mark, mark + V, false);
    fill(position, position + V, NIL);
    std::vector<std::vector<int>> SCCs = SCC();
    int s;
    for (const auto& SCC : SCCs) {
        if (SCC.size() > 1) {
            s = -1;
            for (auto i = SCC.begin(); i != SCC.end(); i++) {
                int v = *i;
                fill(&A[v][0], &A[v][0] + V, NIL);
                A[v][V] = 0;
                list<int>::iterator j;
                for (j = adj[v].begin(); j != adj[v].end(); ++j) {
                    int w = *j;
                    if (std::find(SCC.begin(), SCC.end(), w) != SCC.end()) {
                        A[v][w] = w;
                        A[v][V]++;
                    }
                }
                if (A[v][V] > s) s = v;
            }
            cycles.push_back(std::vector<int>());
            cycle(s, 0, st, A, B, mark, reach, position, cycles);
            cout << endl;
        }
    }
    return cycles;
}

template<int V>
void Graph<V>::no_cycle(int v, int w, int A[V][V + 1], std::vector<std::vector<int>> B) {
    B[w].push_back(v);
    A[v][w] = NIL;
}

template<int V>
void Graph<V>::unmark(int v, bool mark[], int A[V][V + 1], std::vector<std::vector<int>> B) {
    mark[v] = false;
    for (auto i = B[v].begin(); i != B[v].end(); i++) {
        A[*i][v] = v;
        if (mark[*i]) unmark(*i, mark, A, B);
    }
    B[v].clear();
}

template<int V>
bool Graph<V>::cycle(int v, int q, stack<int>* st, int A[V][V + 1], std::vector<std::vector<int>> B, bool mark[], bool reach[],
    int position[], std::vector<std::vector<int>>& cycles) {
    bool f = false;
    int w;
    mark[v] = true;
    st->push(v);
    int t = (int)st->size();
    position[v] = t;
    if (!reach[v]) q = t;
    for (int i = 0; i < V; i++) {
        if (A[v][i] != NIL) {
            if (!mark[i]) {
                if (cycle(i, q, st, A, B, mark, reach, position, cycles)) f = true;
                else no_cycle(v, i, A, B);
            }
            else {
                if (position[i] <= q) {
                    cout << endl;
                    if (!cycles.back().empty()) {
                        std::reverse(cycles.back().begin(), cycles.back().end());
                        cycles.push_back(std::vector<int>());
                    }

                    std::stack<int> bar = *st;
                    // To store stack extracted vertices

                   //cycles.back().push_back(v);
                    cycles.back().push_back((int)bar.top());
                    bar.pop();
                    w = (int)bar.top();
                    while (w != i) {
                        cycles.back().push_back(w);
                        cout << w << " ";
                        bar.pop();
                        w = (int)bar.top();
                    }

                    cycles.back().push_back(i);
                    cycles.back().push_back(v);
                    f = true;
                }
                else no_cycle(v, i, A, B);
            }
        }
    }
    w = (int)st->top();
    cout << w;
    //cycles.back().push_back(w);
    st->pop();
    if (f) unmark(v, mark, A, B);
    reach[v] = true;
    position[v] = V + 1;
    return f;
}

// Driver program to test above function
int main_SCC()
{
    cout << "\nSCCs in first graph \n";
    Graph<5> g1;
    g1.addEdge(1, 0);
    g1.addEdge(0, 2);
    g1.addEdge(2, 1);
    g1.addEdge(0, 3);
    g1.addEdge(3, 4);
    //g1.SCC();
    g1.cycle_finding();

    cout << "\nSCCs in second graph \n";
    Graph<4> g2;
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 3);
    //g2.SCC();
    g2.cycle_finding();

    cout << "\nSCCs in third graph \n";
    Graph<7> g3;
    g3.addEdge(0, 1);
    g3.addEdge(1, 2);
    g3.addEdge(2, 0);
    g3.addEdge(1, 3);
    g3.addEdge(1, 4);
    g3.addEdge(1, 6);
    g3.addEdge(3, 5);
    g3.addEdge(4, 5);
    //g3.SCC();
    g3.cycle_finding();

    cout << "\nSCCs in fourth graph \n";
    Graph<11> g4;
    g4.addEdge(0, 1);
    g4.addEdge(0, 3);
    g4.addEdge(1, 2);
    g4.addEdge(1, 4);
    g4.addEdge(2, 0);
    g4.addEdge(2, 6);
    g4.addEdge(3, 2);
    g4.addEdge(4, 5);
    g4.addEdge(4, 6);
    g4.addEdge(5, 6);
    g4.addEdge(5, 7);
    g4.addEdge(5, 8);
    g4.addEdge(5, 9);
    g4.addEdge(6, 4);
    g4.addEdge(7, 9);
    g4.addEdge(8, 9);
    g4.addEdge(9, 8);
    //g4.SCC();
    std::vector<std::vector<int>> c4 = g4.cycle_finding();
    for (const auto& c : c4) {
        for (int v : c) {
            std::cout << v << " ";
        }
        std::cout << std::endl; // Newline after each row
    }



    cout << "\nSCCs in fifth graph \n";
    Graph<5> g5;
    g5.addEdge(0, 1);
    g5.addEdge(1, 2);
    g5.addEdge(2, 3);
    g5.addEdge(2, 4);
    g5.addEdge(3, 0);
    g5.addEdge(4, 2);
    //g5.SCC();
    g5.cycle_finding();
    std::vector<std::vector<int>> c5 = g5.cycle_finding();
    for (const auto& c : c5) {
        for (int v : c) {
            std::cout << v << " ";
        }
        std::cout << std::endl; // Newline after each row
    }

    cout << "\nSCCs in sixth graph \n";
    Graph<6> g6;
    g6.addEdge(0, 5);
    g6.addEdge(5, 4);
    g6.addEdge(4, 0);
    g6.addEdge(1, 0);
    g6.addEdge(1, 3);
    g6.addEdge(3, 2);
    g6.addEdge(2, 1);
    g6.addEdge(3, 0);
    //g6.SCC();
    g6.cycle_finding();

    return 0;
}