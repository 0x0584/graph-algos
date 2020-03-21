// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Graph.class.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/03/16 00:48:27 by archid-           #+#    #+#             //
//   Updated: 2020/03/21 20:50:09 by archid-          ###   ########.fr       //
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
#include <queue>
#include <algorithm>

using namespace std;

class Graph
{
	struct Vertex
	{
		Vertex(string s) : self(s) {};

		vector<pair<double, Vertex *>> adj;
		string self;
	};
    struct link {
        int id = 0;
        int low = 0;
    };
	map<string, Vertex *> g;
    void sccDFS(Vertex *e, vector<list<string>>& scc, vector<string>& vec,
                int& id, map<string, pair<int, int>>& links);

public:

	Graph();
	~Graph();

	bool addVertex(const string& s);
	void addEdge(const string& from, const string& to,
				 double w = 1.0, bool directed = false);

	// Breadth First Search is an elemnetary Graph algorithm that's perfect
	// for finding the shortest path in an "unweighted graph".
	list<string> BFS(const string& s, const string& t);
	// Dijkstra Shortest Path
	list<string> Dijkstra(const string& s, const string& t);
	// Trajans Strong Connected Components
	vector<list<string>> SCC();
};

#endif
