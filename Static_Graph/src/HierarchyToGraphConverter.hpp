#pragma once
#include <string>
#include <optional>
#include <array>
#include <utility>
#include "DynamicGraph.hpp"
#include "Diagram.hpp"

using VertexType = std::size_t;

template<typename... Entries>
struct List {};

template<VertexType... Vertices>
struct VList {};

template<typename InputList>
struct SizeOfList;

template<typename... Entries>
struct SizeOfList<List<Entries...>> {
    static constexpr std::size_t value = sizeof...(Entries);
};

template<typename InputList>
constexpr std::size_t size_of_list_v = SizeOfList<InputList>::value;

template<typename... Lists>
struct MaxSize;

template<typename LastList>
struct MaxSize<LastList> {
    static constexpr std::size_t value = size_of_list_v<LastList>;
};

template<typename FirstList, typename... OtherLists>
struct MaxSize<FirstList, OtherLists...> {
    static constexpr std::size_t v1 = size_of_list_v<FirstList>;
    static constexpr std::size_t v2 = MaxSize<OtherLists...>::value;
    static constexpr std::size_t value = v1 > v2 ? v1 : v2;
};

template<typename... List>
constexpr std::size_t max_size_v = MaxSize<List...>::value;

template<typename Vertex_, typename Neighbours_>
struct AdjacencyEntry {
    using Vertex = Vertex_;
    using Neighbours = Neighbours_;
};


template<std::size_t Index, typename EntryVertex, typename... Entries>
struct IndexOfAdjacencyEntry;

template<std::size_t Index, typename EntryVertex>
struct IndexOfAdjacencyEntry<Index, EntryVertex> {
    static constexpr std::size_t value = static_cast<std::size_t>(-1);
};

template<std::size_t Index, typename EntryVertex, typename CurrentEntry, typename... OtherEntries>
struct IndexOfAdjacencyEntry<Index, EntryVertex, CurrentEntry, OtherEntries...> {
    static constexpr std::size_t value = 
        std::is_same_v<EntryVertex, typename CurrentEntry::Vertex> 
        ? Index 
        : IndexOfAdjacencyEntry<Index + 1, EntryVertex, OtherEntries...>::value;
};

template<typename EntryVertex, typename... Entries>
constexpr std::size_t index_of_adj_entry = IndexOfAdjacencyEntry<0, EntryVertex, Entries...>::value;

template<typename... AdjEntries>
struct HierarchyToGraphConverter {
private:
    using SubSubList = std::array<VertexType, max_size_v<typename AdjEntries::Neighbours...>>;
    using Sublist = std::pair<std::size_t, SubSubList>;

private:
    template<typename Entry>
    struct AdjacencyEntryToVertex {
        static constexpr std::size_t value = index_of_adj_entry<Entry, AdjEntries...>;
    };

    template<typename Entry>
    static constexpr std::size_t adj_entry_to_vertex_v = AdjacencyEntryToVertex<Entry>::value;

    template<typename Entry>
    struct Indexise;

    template<typename Vertex_, typename... Neighbours>
    struct Indexise<AdjacencyEntry<Vertex_, List<Neighbours...>>> {
        using NeighboursVList = VList< adj_entry_to_vertex_v<Neighbours>... >;
    };

    template<typename VList>
    struct FromVList;

    template<VertexType... Vertices>
    struct FromVList<VList<Vertices...>> {
        static constexpr SubSubList value = { Vertices... };
    };

    template<typename VList>
    static constexpr SubSubList from_vlist_v = FromVList<VList>::value;

    template<typename... InnerAdjEntries>
    struct ConverterImpl
    {
        static constexpr std::array<Sublist, sizeof...(InnerAdjEntries)> value = {
            { Sublist{size_of_list_v<typename InnerAdjEntries::Neighbours>, from_vlist_v<typename Indexise<InnerAdjEntries>::NeighboursVList>}... }
        };
    };

public:
    /*constexpr HierarchyToGraphConverter()
        : _input(ConverterImpl<AdjEntries...>::value)
    {
    }*/
    static DynamicGraph<sizeof...(AdjEntries)> graph_of_hierarchy() {
        std::array<Sublist, V> intermediate_graph_representation = ConverterImpl<AdjEntries...>::value;
        DynamicGraph<V> converted_graph{};
        for (std::size_t vertex = 0; vertex < V; vertex++) {
            const auto& [size, subsublist] = intermediate_graph_representation[vertex];
            for (std::size_t neighbour = 0; neighbour < size; neighbour++) {
                converted_graph.add_neighbour(vertex, subsublist[neighbour]);
            }
        }
        return converted_graph;
    }

    static constexpr auto cb_graph_of_hierarchy() {
        std::array<Sublist, V> intermediate_graph_representation = ConverterImpl<AdjEntries...>::value;
        ConstexprBasedGraph<V, max_size_v<typename AdjEntries::Neighbours...>> converted_graph(intermediate_graph_representation);
        return converted_graph;
    }

    static constexpr const char* name_by_id(const VertexType v){
        if (v >= V) return; //throw std::invalid_argument("not existing vertex");
        return typeid(ConverterImpl<AdjEntries...>::value[v]).name();
    }

    static constexpr std::size_t V = sizeof...(AdjEntries);
};
