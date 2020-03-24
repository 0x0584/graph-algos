// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Graph.class.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/03/16 00:48:27 by archid-           #+#    #+#             //
//   Updated: 2020/03/24 00:56:25 by archid-          ###   ########.fr       //
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
class Graph
{
    // this is an internal structure that to represent each vertex
    // it holds the vertex identity as well as its adjacent vertices
	struct Vertex
	{
		Vertex(string s) : self(s) {}

        // vertex's identity
		string self;

        // vector of pairs of weight and destination vertices
		vector<pair<int, Vertex *>> adj;
	};

    // representing the graph as a map helps to the efficiency of retrieving
    // and manipulating vertices
	map<string, Vertex *> g;

    // internal protocol to trace back a path starting from the destination
    // vertex up until the source vertex
    list<string> construct_path(map<string, string>& parent,
                                const string &s, const string &t);

    // a custom DFS to set the component's id, used by SCC to find the
    // strongly connected components in the graph
    void sccDFS(Vertex *e, vector<vector<string>>& scc, vector<string>& vec,
                int& id, map<string, pair<int, int>>& links);

public:

	Graph(); ~Graph();

    // output every vertex and edge
    void dumpGraph();

    // used for testing
    pair<string, string> getSampleVertexPair();

    // return a vector of all the vertices of the graph
    vector<string> getVertices();

    // return all the edges of the graph, if the graph an edge is
    // undirected, both directions are included
    vector<tuple<string, string, int>> getEdges();

    // fill a graph with vertices and edges from the given file
    // the graph properties, namely directness and weight could be
    // specified as well.
    static Graph *readGraph(const char *file, bool directed = false,
                            bool weighted = false);

    // add the vertex s to the graph, if it's not already there
	bool addVertex(const string& s);

    // removes teh vertex s, and all it's edges
    void removeVertex(const string& s);

    // add an edge between the two given vertices, weight and direction
    // could be specified as well
	void addEdge(const string& from, const string& to,
				 int w = 1, bool directed = false);

    // remove the edge (from, to)
    void removeEdge(const string& from, const string& to,
                    bool directed = false);

	// Breadth First Search
	list<string> BFS(const string& s, const string& t);

	// Dijkstra Shortest Path
	list<string> Dijkstra(const string& s, const string& t);

	// Trajans Strong Connected Components
	vector<vector<string>> SCC();

    // rank vertices based on many desired properties
    map<string, int> rankByOutEdges();
    map<string, int> rankByInEdges();
};

#endif
