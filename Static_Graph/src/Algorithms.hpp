#pragma once
#include "DynamicGraph.hpp"
#include <vector>
#include <stack>
#include <queue>
#include <span>
//#include <iostream>

template<std::size_t V, typename Func>
void dfs_util(const DynamicGraph<V>& graph, VertexType v_start, Func f) {

    if (v_start >= V) throw std::invalid_argument("v_start is not in graph");

    std::vector<bool> visited(V, false);
    std::stack<VertexType> stack;

    stack.push(v_start);

    while (!stack.empty())
    {
        VertexType v_start = stack.top();
        stack.pop();

        f(v_start);

        if (!visited[v_start])
        {
            visited[v_start] = true;
            //f(v_start);
            //std::cout << v_start << std::endl;
        }

        for (auto i = graph.neighbourhoods(v_start).begin(); i != graph.neighbourhoods(v_start).end(); ++i)
            if (!visited[*i])
                stack.push(*i);
    }
}

template<size_t V, typename Func>
void bfs_util(const DynamicGraph<V>& graph, VertexType v_start, Func f) {

    if (v_start >= V) throw std::invalid_argument("v_start is not in graph");

    std::vector<bool> visited(V, false);
    std::queue<VertexType> queue;

    queue.push(v_start);

    while (!queue.empty())
    {
        VertexType v_start = queue.front();
        queue.pop();

        if (!visited[v_start])
        {
            visited[v_start] = true;
            f(v_start);
        }

        for (auto i = graph.neighbourhoods(v_start).begin(); i != graph.neighbourhoods(v_start).end(); ++i)
            if (!visited[*i])
                queue.push(*i);
    }
}

template<size_t V>
void first_dfs_way(std::vector<VertexType>& way, const DynamicGraph<V>& graph, VertexType v) {
    dfs_util(graph, v, [&way, graph](VertexType v_start) mutable {
        if (way.empty()) 
        {
            way = { v_start };
            return;
        }

        for (VertexType neighbourhood : graph.neighbourhoods(way.back()))
            if (v_start == neighbourhood)
                way.push_back(v_start);

    });
}

template<size_t V>
void all_dfs_ways(std::vector<std::vector<VertexType>>& ways, const DynamicGraph<V>& graph, VertexType v) {
    dfs_util(graph, v, [&ways, graph](VertexType v_start) mutable {
        bool jump = true;
        if (ways.empty()) 
        {
            std::vector<VertexType> way = {};  ways = { way };
        }

        std::vector<VertexType>& last_way = ways.back();
        if (last_way.empty()) 
        {
            last_way = { v_start };
            return;
        }

        const VertexType end = last_way.back();

        for (VertexType neighbourhood : graph.neighbourhoods(end))
            if (v_start == neighbourhood) 
            {
                last_way.push_back(v_start);
                jump = false;
            }

        if (jump) 
        {
            jump = false;
            VertexType i = last_way.size();

            while (!jump) 
            {
                for (VertexType neighbourhood : graph.neighbourhoods(last_way[last_way.size() - i]))
                    if (v_start == neighbourhood || i < 2) jump = true;
                i--;
            }

            const std::span<VertexType> old_way(last_way.begin(), last_way.end() - i);
            std::vector<VertexType> new_way = 
            {
                old_way.begin(),
                old_way.end()
            };
            new_way.push_back(v_start);
            ways.push_back(std::move(new_way));
        }

    });
}
