// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Graph.class.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/03/16 00:48:27 by archid-           #+#    #+#             //
//   Updated: 2020/03/25 11:09:00 by archid-          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef GRAPH_CLASS_HPP
# define GRAPH_CLASS_HPP

#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

// represents a graph data structure, and provides basic graph manipulation
// functions such as adding vertices and edges, as well as some standard
// algorithms such as BFS, Dijkstra and Trajans SCC.
template<class T, class W>
class Graph
{
    // this is an internal structure that to represent each vertex
	// it holds the vertex identity as well as its adjacent vertices
	struct Vertex
	{
		T self;                         // vertex's identity

		vector<pair<W, Vertex *>> adj;  // out-going edges
		vector<pair<W, Vertex *>> radj; // in-coming edges

		Vertex(T v) : self(v) {}
	};

    struct Link
    {
        int id, low_id;

        Link() : id(0), low_id(0) {}
        Link(Link& l) : id(l.id), low_id(l.id) {l.id++;}

        Link& operator= (const Link& l) {
            id = low_id = l.id;
            return *this;
        }
    };

	// representing the graph as a map helps to the efficiency of retrieving
	// and manipulating vertices
	map<T, Vertex *> g;

	// internal method to add an edge to both vertices, to ease of
	// vertex and removal, altought this is doesn't mean that it's
	// undirected! it's just a copy stored in the other vertex.
	void set_edge(const T& from, const T& to, W w);

    // internal method to remove an edge from adjacency list
	void unset_edge(const T& from, const T& to);

	// internal protocol to trace back a path starting from the destination
	// vertex up until the source vertex
	list<T> construct_path(map<T, T>& parent, const T &s, const T &t);

	// Sets the low link of u to the min low keys between itself and v
	void set_link(map<T, Link>& links, Vertex *u, Vertex *v);

	// a custom DFS to set the component's id, used by SCC to find the
	// strongly connected components in the graph
	void sccDFS(Vertex *e, vector<vector<T>>& scc, vector<T>& visiting,
				Link& l, map<T, Link>& links);

public:

	Graph(); ~Graph();

	// output every vertex and edge
	void dumpGraph();

	// used for testing
	pair<T, T> getSampleVertexPair();

	// return a vector of all the vertices of the graph
	vector<T> getVertices();

	// return all the edges of the graph, if the graph an edge is
	// undirected, both directions are included
	vector<tuple<T, T, W>> getEdges();

	// add the vertex s to the graph, if it's not already there
	bool addVertex(const T& s);

	// removes teh vertex s, and all it's edges
	void removeVertex(const T& s);

	// add an edge between the two given vertices, weight and direction
	// could be specified as well
	void addEdge(const T& from, const T& to, W w = 1, bool directed = false);

	// remove the edge (from, to)
	void removeEdge(const T& from, const T& to, bool directed = false);

	// Breadth First Search
	list<T> BFS(const T& s, const T& t);

	// Dijkstra Shortest Path
	list<T> Dijkstra(const T& s, const T& t);

	// Trajans Strong Connected Components
	vector<vector<T>> SCC();

	// rank vertices based on many desired properties
	map<T, W> rankByEdges(bool out = true);

    // implementation of the Google's PageRank algorithm to rank pages
    set<pair<double, T>, greater<pair<double, T>>> pageRank();
};

#endif
