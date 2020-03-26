// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Graph.class.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/03/16 00:48:27 by archid-           #+#    #+#             //
//   Updated: 2020/03/27 15:23:59 by archid-          ###   ########.fr       //
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

		set<pair<W, Vertex *>> adj;  // out-going edges
		set<pair<W, Vertex *>> radj; // in-coming edges

		Vertex(T v = 0) : self(v) {}

        friend bool operator<(const Vertex& v, const Vertex& u) {
            return v.self < u.self;
        }
        friend bool operator>(const Vertex& v, const Vertex& u) {
            return v.self > u.self;
        }
        friend bool operator<=(const Vertex& v, const Vertex& u) {
            return v.self <= u.self;
        }
        friend bool operator>=(const Vertex& v, const Vertex& u) {
            return v.self >= u.self;
        }
        friend bool operator==(const Vertex& v, const Vertex& u) {
            return v.self == u.self;
        }
        friend bool operator!=(const Vertex& v, const Vertex& u) {
            return v.self != u.self;
        }
	};

    // internal structure used to track connected components
    struct Link
    {
        int id, low_id;

        Link() : id(0), low_id(0) {}

        Link& operator= (Link& l) {
            id = low_id = l.id++;
            return *this;
        }

        void setLow(const Link &l) {
            low_id = min(low_id, l.low_id);
        }
    };

    struct Rank
    {
        typedef map<Vertex *, Rank> RankMap;

        static const double decay_rate; // rate of browsing all links
        static const double epsilon;    // minimum variation of rank
        static RankMap ranks;           // the ranks of all vertices
        static bool unstable;   // false if ranks stoped varying
        static int N;           // Number of vertices

        double r_old;
        double r_new;

        Rank(int n = 1) : r_old(1.0 / n), r_new(0.0) {}

        void update() {r_old = r_new; r_new = 0.0;}

        void update(Vertex *u, double random_jump) {
            r_new = random_jump + (1 - decay_rate) / N;

            for (auto v : u->radj) {
                double tmp = (decay_rate * ranks[v.second].r_old);
                tmp /= v.second->adj.size();
                cout << " cc >> " << v.second->self << " => " << tmp << endl;
                r_new += tmp;
            }

            unstable &= (abs(r_new - r_old) < epsilon);
            cout << r_old << "\t - \t" << r_new << "\t "
                 << abs(r_new - r_old) << endl;

        }

        static double randomJumpFactor() {
            double rj = 0.0;

            for (auto pg : ranks)
                if (pg.first->adj.size() == 0)
                    rj += decay_rate * (pg.second.r_old / N);
            return rj;
        }

        static void rankPages() {
            double rj = randomJumpFactor();

            for (auto pg = ranks.begin(); pg != ranks.end(); pg++) {
                cout << "site: " << pg->first->self << endl;
                pg->second.update(pg->first, rj);
                getchar();
            }

        }

        static void updateRanks() {
            for (auto pg = ranks.begin(); pg != ranks.end(); pg++)
                pg->second.update();
            unstable ^= true;
        }

        static bool init(map<T, Vertex *> g) {
            unstable = true;
            if (!(N = g.size())) return false;
            for (auto e : g) {
                ranks[e.second] = {N};
                cout << e.second->self << " " << ranks[e.second].r_old << endl;
            }
            return true;
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

    // Apply fn on all vertices starting at vertex s
    void BFS(T& s, T (*fn)(T& e, int layer));

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
