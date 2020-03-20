// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Graph.class.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/03/16 00:48:27 by archid-           #+#    #+#             //
//   Updated: 2020/03/20 21:44:34 by archid-          ###   ########.fr       //
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

using namespace std;

class Graph
{
public:

    Graph();
    ~Graph();

    void graphDump();

    bool addVertex(const string &s);
    void addEdge(const string &from, const string &to,
                 double w = 1.0, bool directed = false);

    // Breadth First Search is an elemnetary Graph algorithm that's perfect
    // for finding the shortest path in an "unweighted graph".
    list<string> BFS(const string &s, const string &t);

    list<string> Dijkstra(const string &s, const string &t);
    vector<list<string>> SCC();

private:

    struct Vertex
    {
        vector<pair<double, Vertex *>> adj;
        string self;

        Vertex(string s) : self(s) {};

        void to_str() {
            cout << "Vertex: " << self << endl;
            for (auto itr = adj.begin(); itr != adj.end(); itr++) {
                cout << itr->second->self << ": " << itr->first << endl;
            }
            cout << endl;
        }
    };

    map<string, Vertex *> g;
};

#endif
