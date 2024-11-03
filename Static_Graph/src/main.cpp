#include <cstddef>
#include <optional>

using VertexType = int;

template<typename T>
struct Slice
{
	T* data;
	std::size_t size;
};

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

	constexpr void adjacent(VertexType v) {}
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
struct IsAcyclicGraph {};

struct ConstexprGraphAlgorithm
{
	template<std::size_t V, typename F>
	static auto dfs(ConstexprBasedGraph<V>& graph, VertexType v_start, F&& f) {
		std::optional<Slice<VertexType>> opt = Slice<VertexType> { nullptr, 0 };
		return opt;
	}

	template<std::size_t V, typename F>
	static auto bfs(ConstexprBasedGraph<V>& graph, VertexType v_start, F&& f) {
		return std::nullopt;
	}

	template<std::size_t V>
	static bool is_acyclic(ConstexprBasedGraph<V>& graph) {
		return false;
	}
};



int main() {
	ConstexprBasedGraph<10> graph;

	//std::optional<int>

	VertexType v_start = 0;
	VertexType v_end = 10;

	Slice<VertexType> found_path = *ConstexprGraphAlgorithm::dfs(
		graph, 
		v_start, 
		[v_end](VertexType v, Slice<VertexType> current_path) -> std::optional<Slice<VertexType>> {
			if (v == v_end) {
				return current_path;
			}

			return std::nullopt;
		}
	);

	return 0;
}
