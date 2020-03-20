// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Graph.class.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/03/16 00:49:43 by archid-           #+#    #+#             //
//   Updated: 2020/03/20 21:45:07 by archid-          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Graph.class.hpp"

Graph::Graph() : g() {}

Graph::~Graph() {
    for (auto itr = g.begin(); itr != g.end(); itr++)
        delete itr->second;
}

void Graph::graphDump() {
        cout << "vertcies count: " << g.size() << endl;
        for (auto itr = g.begin(); itr != g.end(); itr++)
            itr->second->to_str();
}

bool Graph::addVertex(const string &s) {
    if (g.find(s) != g.end())
        return false;
    g[s] = new Vertex(s);
    return true;
}

void Graph::addEdge(const string &from, const string &to, double w,
                    bool directed) {
    addVertex(from); addVertex(to);
    g.find(from)->second->adj.push_back(make_pair(w, g.find(to)->second));
    if (!directed)
        g.find(to)->second->adj.push_back(make_pair(w, g.find(from)->second));
}

list<string> bfs_helper_parent_path(map<string, string>& parent,
                                    const string &s, const string &t) {
    list<string> path;
    string walk = t;

    if (parent.find(t) == parent.end())
        return path;
    while (true) {
        path.push_front(walk);
        if (walk == s)
            break;
        walk = parent[walk];
    }
    return path;
}

list<string> Graph::BFS(const string &s, const string &t) {
    map<string, string> parent;
    queue<string> q;

    q.push(s);
    parent[s] = "";
    while (!q.empty())
    {
        if (q.front() == t) break;
        auto neighbors = g.find(q.front())->second->adj;
        for (auto itr = neighbors.begin(); itr != neighbors.end(); itr++) {
            if (parent.find(itr->second->self) != parent.end())
                continue;
            q.push(itr->second->self);
            parent[itr->second->self] = q.front();
        }
        q.pop();
    }
    return bfs_helper_parent_path(parent, s, t);
}

list<string> Graph::Dijkstra(const string &s, const string &t) {
    const double inf = numeric_limits<double>::infinity();


}
