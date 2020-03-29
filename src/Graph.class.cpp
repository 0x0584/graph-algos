// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Graph.class.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/03/16 00:49:43 by archid-           #+#    #+#             //
//   Updated: 2020/03/29 13:55:42 by archid-          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Graph.class.hpp"

template<class V, class W> Graph<V, W>::Graph() : g() {}
template<class V, class W> Graph<V, W>::~Graph() {
    for (auto itr = g.begin(); itr != g.end(); itr++)
        // vertices were allocated dynamically so they must be free'd
        delete itr->second;
}

template<class V, class W>
void Graph<V, W>::dumpGraph() {
    for (auto u: g) {
        cout << "Vertex: " << u.first << " ";
        for (auto e: u.second->adj)
            cout << "(" << e.first << "," << e.second->self << ") ";
        cout << endl;
    }
    cout << endl;
}

template<class V, class W>
pair<V, V> Graph<V, W>::getSampleVertexPair() {
    return make_pair(g.begin()->first, g.rbegin()->first);
}

template<class V, class W>
vector<V> Graph<V, W>::getVertices() {
    vector<V> v;

    for (auto u: g)
        v.push_back(u.first);
    return v;
}

template<class V, class W>
vector<tuple<V, V, W>> Graph<V, W>::getEdges() {
    vector<tuple<V, V, W>> v;

    for (auto u: g)
        for (auto e: u.second->adj)
            v.push_back({u.first, e.second->self, e.first});
    return v;
}

template<class V, class W>
bool Graph<V, W>::addVertex(const V& s) {
    if (g.find(s) != g.end())
        return false;
    g[s] = new Vertex<V, W>(s);
    return true;
}

template<class V, class W>
void Graph<V, W>::removeVertex(const V& s) {
    for (auto nei: g[s]->adj)
        nei.second->radj.erase(
            find_if(nei.second->radj.begin(),
                    nei.second->radj.end(),
                    [&s](const pair<W, Vertex<V, W> *>& e) {
                        return s == e.second->self;
                    }));
    for (auto nei: g[s]->radj)
        nei.second->adj.erase(
            find_if(nei.second->adj.begin(),
                    nei.second->adj.end(),
                    [&s](const pair<W, Vertex<V, W> *>& e) {
                        return s == e.second->self;
                    }));
    delete g[s];
    g.erase(s);
}

template<class V, class W>
void Graph<V, W>::set_edge(const V& from, const V& to, W w) {
    g[from]->adj.insert({w, g[to]});
    g[to]->radj.insert({w, g[from]});
}

template<class V, class W>
void Graph<V, W>::addEdge(const V& from, const V& to, W w,
                          bool directed) {
    addVertex(from); addVertex(to);
    set_edge(from, to, w);
    if (!directed) set_edge(to, from, w);
}

template<class V, class W>
void Graph<V, W>::unset_edge(const V& from, const V& to) {
    g[from]->adj.erase(
        find_if(g[from]->adj.begin(), g[from]->adj.end(),
                [&to](const pair<W, Vertex<V, W> *>& e) {
                                           return to == e.second->self;
                                       }));
    g[to]->radj.erase(
        find_if(g[to]->radj.begin(), g[to]->radj.end(),
                [&from](const pair<W, Vertex<V, W> *>& e) {
                                          return from == e.second->self;
                                      }));
}

template<class V, class W>
void Graph<V, W>::removeEdge(const V& from, const V& to, bool directed) {
    if (g.find(from) == g.end() || g.find(to) == g.end())
        return ;
    unset_edge(from, to);
    if (!directed)
        unset_edge(to, from);
}

template<class V, class W>
list<V> Graph<V, W>::construct_path(map<V, V>& parent, const V& s, const V& t) {
    list<V> path;
    V walk = t;

    // destination not have no parent, thus it hasn't been reached
    if (parent.find(t) == parent.end())
        return path;
    // keep tracing back the parents until we arrive.
    while (true) {
        // pushing vertices before testing on arrival
        // to include source and destination nodes
        path.push_front(walk);
        if (walk == s)
            break;
        walk = parent[walk];
    }
    return path;
}

template class Graph<int, int>;
template class Graph<char, int>;
template class Graph<string, int>;
