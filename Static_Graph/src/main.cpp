#include <cstddef>

// Constexpr graphs

template<std::size_t V>
class ConstexprBasedGraph
{
public:
	constexpr ConstexprBasedGraph() = default;

public:
	constexpr bool has_edge(VertexType v1, VertexType v2) const {
		return true;
	}

	constexpr std::size_t deg(VertexType vertex) const {
		return 0;
	}

	constexpr std::size_t vertices_count() const {
		return 0;
	}

	constexpr std::size_t edges_count() const {
		return 0;
	}

	constexpr void add_edge(VertexType v1, VertexType v2) const {}
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

template<typename Graph>
struct EdgesCount {};

template<typename Graph>
struct VerticesCount {};
