#pragma once
#include <array>
#include <initializer_list>
#include <stdexcept>
#include <span>

using VertexType = std::size_t;

template<size_t V>
class DynamicGraph {
private:
	std::array<std::array<VertexType, V+1>, V> _neighbourhoods_list;
	const std::size_t _edge_count;
public:
	DynamicGraph(std::initializer_list<std::initializer_list<VertexType>> init)
		: _neighbourhoods_list{initialize_neighbourhoods(init)}
		, _edge_count{ initialize_edge_count(init)}
	{}

	void add_neighbour(VertexType vertex, VertexType neighbour) {
		if (!has_oriented_edge(vertex, neighbour)&&(neighbour < V)) {
			VertexType& array_size = _neighbourhoods_list[vertex][V];
			_neighbourhoods_list[vertex][array_size] = neighbour;
			array_size++;
		}
	}

	const std::span<const VertexType> neighbourhoods(VertexType vertex) const {
		if (V <= vertex)  throw std::invalid_argument("not existing vertex");
		return std::span(_neighbourhoods_list[vertex].begin(), _neighbourhoods_list[vertex][V]);
	}

	bool has_oriented_edge(VertexType v_out, VertexType v_in) const {
		for (auto& neighbour : neighbourhoods(v_out)) if (v_in == neighbour) return true;
		return false;
	}

	const std::size_t deg(VertexType vertex) const {
		if (V <= vertex)  throw std::invalid_argument("not existing vertex");
		return _neighbourhoods_list[vertex][V];
	}

	std::size_t vertex_count() const {
		return V;
	}

	std::size_t edge_count() const {
		return _edge_count;
	}

private:
	static std::array<std::array<VertexType, V + 1>, V> initialize_neighbourhoods
	(std::initializer_list<std::initializer_list<VertexType>> init) {
		std::array<std::array<VertexType, V + 1>, V> neighbourhoods_list{};

		for (std::size_t i = 0; i < init.size(); i++) {
			if (i + 1 > V) throw std::invalid_argument("initializer_list dosen`t fit into array");
			const auto nested_init = init.begin() + i;

			for (std::size_t j = 0; j < nested_init->size(); j++) {
				if (j + 1 > V - 1) throw std::invalid_argument("initializer_list dosen`t fit into array");
				neighbourhoods_list[i][j] = *(nested_init->begin() + j);
			}

			neighbourhoods_list[i][V] = nested_init->size();
		}

		return neighbourhoods_list;
	}
	
	static std::size_t initialize_edge_count(std::initializer_list<std::initializer_list<VertexType>> init) {
		std::size_t edge_count = 0;

		for (const auto& nested_init : init) {
			edge_count += nested_init.size();
		}

		return edge_count;
	}
};


