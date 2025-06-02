#pragma once
#include <cstddef>
#include <optional>
#include <span>
#include <stdexcept>

using VertexType = std::size_t;

constexpr std::size_t BUFFER_SIZE = 10000;

template<typename T>
struct Slice
{
	T* data;
	std::size_t size;
};

// Constexpr graphs

template<std::size_t V, std::size_t M>
class ConstexprBasedGraph
{
private:
	using AdjList = std::array<VertexType, M>;

private:
	std::array<std::pair<std::size_t, std::array<VertexType, M>>, V> adj_lists_;

public:
	constexpr explicit ConstexprBasedGraph(std::array<std::pair<std::size_t, std::array<VertexType, M>>, V> adj_lists)
		: adj_lists_{ adj_lists }
	{
	}

public:
	constexpr bool has_edge(VertexType v1, VertexType v2) const {
		if (!validate_vertex(v1) || !validate_vertex(v2)) {
			return false;
		}

		const auto& [_, list] = adj_lists_[v1];
		return std::find(list.cbegin(), list.cend(), v2) != list.cend();
	}

	constexpr std::size_t vertex_count() const {
		return V;
	}

	constexpr std::size_t edges_count() const {
		return 0;
	}

	constexpr const std::span<const VertexType> neighbourhoods(VertexType vertex) const {
		if (!validate_vertex(vertex)) {
			throw std::invalid_argument("Non-existent vertex");
		}

		auto& [size, list] = adj_lists_[vertex];
		return std::span(list.begin(), size);
	}

private:
	static constexpr bool validate_vertex(VertexType v) {
		return v < V;
	}
};

// Template-based metaprogramming

template<std::size_t V1, std::size_t V2>
struct Edge {};

template<std::size_t V, typename... Edges>
struct TemplateBasedGraph {};

template<std::size_t Vertex1, std::size_t Vertex2, typename Graph>
struct HasEdgeUtility {};

template<std::size_t Vertex, typename Graph>
struct DegUtility {};

template<std::size_t Vertex, typename Graph>
struct AdjacentUtility {};

template<typename Graph>
struct EdgesCount {};

template<typename Graph>
struct VerticesCount {};

// Algorithms

template<
	typename Graph,
	template<typename> typename F
>
struct BFS {};

template<
	typename Graph,
	template<typename> typename F
>
struct DFS {};

template<typename Graph>
struct FindCyclesUtility {};

using Path = std::array<VertexType, BUFFER_SIZE>;

struct ConstexprGraphAlgorithm
{
	template<std::size_t V, std::size_t M, typename F>
	static auto dfs(ConstexprBasedGraph<V, M>& graph, VertexType v_start, F&& f) {
		std::optional<Slice<VertexType>> opt = Slice<VertexType>{ nullptr, 0 };
		return opt;
	}

	template<std::size_t V, std::size_t M, typename F>
	static auto bfs(ConstexprBasedGraph<V, M>& graph, VertexType v_start, F&& f) {
		return std::nullopt;
	}

	template<std::size_t V, std::size_t M>
	static std::array<Path, BUFFER_SIZE> find_cycles(ConstexprBasedGraph<V, M>& graph) {
		return false;
	}
};



//int run_example() {
//	ConstexprBasedGraph<10> graph{};
//
//	//std::optional<int>
//
//	VertexType v_start = 0;
//	VertexType v_end = 10;
//
//	Slice<VertexType> found_path = *ConstexprGraphAlgorithm::dfs(
//		graph,
//		v_start,
//		[v_end](VertexType v, Slice<VertexType> current_path) -> std::optional<Slice<VertexType>> {
//			if (v == v_end) {
//				return current_path;
//			}
//
//			return std::nullopt;
//		}
//	);
//
//
//	static constexpr ConstexprBasedGraph<10> graph_constexpr_1{};
//	static constexpr bool some_bubble = graph_constexpr_1.has_edge(0, 1);
//
//	return 0;
//}