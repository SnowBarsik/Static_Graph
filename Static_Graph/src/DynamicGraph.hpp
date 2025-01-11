#pragma once
#include <array>
#include <initializer_list>
#include <stdexcept>
#include <span>

template<size_t V>
class DynamicGraph {
private:
	std::array<std::array<int, V+1>, V> _neigbourhoods;
	int _edge_count;
public:
	DynamicGraph(std::initializer_list<std::initializer_list<int>> init)
		: _neigbourhoods{}
		, _edge_count{ 0 }
	{
		int i = 0;
		int j = 0;
		for (auto& nested_init : init) {
			if (i + 1 > V) throw std::invalid_argument("initializer_list dosen`t fit into array");
			for (auto& elem : nested_init) {
				if (j + 1 > V - 1) throw std::invalid_argument("initializer_list dosen`t fit into array");
				_neigbourhoods[i][j] = elem;
				j++;
			}
			_neigbourhoods[i][V] = nested_init.size();
			_edge_count += nested_init.size();
			i++;
			j = 0;
		}
	};

	const std::span<const int> neigbourhoods(int vertex) const {
		if (V < vertex || 0 > vertex)  throw std::invalid_argument("not existing vertex");
		return std::span(_neigbourhoods[vertex].begin(), _neigbourhoods[vertex][V]);
	};

	const int vertex_count() const {
		return V;
	}

	const int edge_count() const {
		return _edge_count;
	}

};




