#pragma once
#include <array>
#include <initializer_list>
#include <stdexcept>
#include <span>

template<size_t V>
class DynamicGraph {
private:
	const std::array<std::array<int, V+1>, V> _neigbourhoods_list;
	const int _edge_count;
public:
	DynamicGraph(std::initializer_list<std::initializer_list<int>> init)
		: _neigbourhoods_list{initialize_neigbourhoods(init)}
		, _edge_count{ initialize_edge_count(init)}
	{}

	const std::span<const int> neigbourhoods(int vertex) const {
		if (V < vertex || 0 > vertex)  throw std::invalid_argument("not existing vertex");
		return std::span(_neigbourhoods_list[vertex].begin(), _neigbourhoods_list[vertex][V]);
	}

	int vertex_count() const{
		return V;
	}

	int edge_count() const{
		return _edge_count;
	}

private:
	static std::array<std::array<int, V + 1>, V> initialize_neigbourhoods
	(std::initializer_list<std::initializer_list<int>> init) {
		std::array<std::array<int, V + 1>, V> neigbourhoods_list;

		for (int i = 0; i < init.size(); i++) {
			if (i + 1 > V) throw std::invalid_argument("initializer_list dosen`t fit into array");
			const auto nested_init = init.begin() + i;

			for (int j = 0; j < nested_init->size(); j++) {
				if (j + 1 > V - 1) throw std::invalid_argument("initializer_list dosen`t fit into array");
				neigbourhoods_list[i][j] = *(nested_init->begin() + j);
			}

			neigbourhoods_list[i][V] = nested_init->size();
		}

		return neigbourhoods_list;
	}
	
	static int initialize_edge_count(std::initializer_list<std::initializer_list<int>> init) {
		int edge_count = 0;

		for (const auto& nested_init : init) {
			edge_count += nested_init.size();
		}

		return edge_count;
	}
};
