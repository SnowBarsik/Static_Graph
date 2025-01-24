#pragma once
#include <array>
#include <initializer_list>
#include <stdexcept>
#include <span>

using VertexType = std::size_t;

template<size_t V>
class DynamicGraph {
private:
	const std::array<std::array<VertexType, V+1>, V> _neigbourhoods_list;
	const std::size_t _edge_count;
public:
	DynamicGraph(std::initializer_list<std::initializer_list<VertexType>> init)
		: _neigbourhoods_list{initialize_neigbourhoods(init)}
		, _edge_count{ initialize_edge_count(init)}
	{}

	const std::span<const VertexType> neigbourhoods(VertexType vertex) const {
		if (V < vertex || 0 > vertex)  throw std::invalid_argument("not existing vertex");
		return std::span(_neigbourhoods_list[vertex].begin(), _neigbourhoods_list[vertex][V]);
	}

	bool hasOrientedEdge(VertexType v_out, VertexType v_in) const {
		for (auto& neigbourhood : neigbourhoods(v_out)) if (v_in == neigbourhood) return true;
		return false;
	}

	std::size_t vertex_count() const {
		return V;
	}

	std::size_t edge_count() const {
		return _edge_count;
	}

private:
	static std::array<std::array<VertexType, V + 1>, V> initialize_neigbourhoods
	(std::initializer_list<std::initializer_list<VertexType>> init) {
		std::array<std::array<VertexType, V + 1>, V> neigbourhoods_list;

		for (std::size_t i = 0; i < init.size(); i++) {
			if (i + 1 > V) throw std::invalid_argument("initializer_list dosen`t fit into array");
			const auto nested_init = init.begin() + i;

			for (std::size_t j = 0; j < nested_init->size(); j++) {
				if (j + 1 > V - 1) throw std::invalid_argument("initializer_list dosen`t fit into array");
				neigbourhoods_list[i][j] = *(nested_init->begin() + j);
			}

			neigbourhoods_list[i][V] = nested_init->size();
		}

		return neigbourhoods_list;
	}
	
	static int initialize_edge_count(std::initializer_list<std::initializer_list<VertexType>> init) {
		std::size_t edge_count = 0;

		for (const auto& nested_init : init) {
			edge_count += nested_init.size();
		}

		return edge_count;
	}
};
