// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Graph.class.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/03/16 00:48:27 by archid-           #+#    #+#             //
//   Updated: 2020/03/27 16:10:14 by archid-          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef GRAPH_CLASS_HPP
# define GRAPH_CLASS_HPP

# include "Vertex.class.hpp"

// represents a graph data structure, and provides basic graph manipulation
// functions such as adding vertices and edges, as well as some standard
// algorithms such as BFS, Dijkstra and Trajans SCC.
template<class V, class W>
class Graph
{
    // representing the graph as a map helps to the efficiency of retrieving
    // and manipulating vertices
    map<V, Vertex<V, W> *> g;

    // internal method to add an edge to both vertices, to ease of
    // vertex and removal, altought this is doesn't mean that it's
    // undirected! it's just a copy stored in the other vertex.
    void set_edge(const V& from, const V& to, W w);

    // internal method to remove an edge from adjacency list
    void unset_edge(const V& from, const V& to);

    // internal protocol to trace back a path starting from the destination
    // vertex up until the source vertex
    list<V> construct_path(map<V, V>& parent, const V &s, const V &t);

public:

    Graph(); ~Graph();

    // output every vertex and edge
    void dumpGraph();

    // used for testing
    pair<V, V> getSampleVertexPair();

    // return a vector of all the vertices of the graph
    vector<V> getVertices();

    // return all the edges of the graph, if the graph an edge is
    // undirected, both directions are included
    vector<tuple<V, V, W>> getEdges();

    // add the vertex s to the graph, if it's not already there
    bool addVertex(const V& s);

    // removes teh vertex s, and all it's edges
    void removeVertex(const V& s);

    // add an edge between the two given vertices, weight and direction
    // could be specified as well
    void addEdge(const V& from, const V& to, W w = 1, bool directed = false);

    // remove the edge (from, to)
    void removeEdge(const V& from, const V& to, bool directed = false);

    // Breadth First Search
    list<V> BFS(const V& s, const V& t);

    // Apply fn on all vertices starting at vertex s
    void BFS(V& s, V (*fn)(V& e, int layer));

    // Dijkstra Shortest Path
    list<V> Dijkstra(const V& s, const V& t);

    // Trajans Strong Connected Components
    vector<vector<V>> SCC();

    // rank vertices based on many desired properties
    set<pair<double, V>, greater<pair<double, V>>> rankByEdges(bool out = true);

    // implementation of the Google's PageRank algorithm to rank pages
    set<pair<double, V>, greater<pair<double, V>>> pageRank();
};

#endif
