// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Graph.paths.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/03/25 13:09:57 by archid-           #+#    #+#             //
//   Updated: 2020/03/29 22:53:12 by archid-          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Graph.class.hpp"

// helper class to avoid initializing all entries, new ones are by default set
// to some high numerical value
template<class W> struct Distance
{
    W dist;

    Distance(W init = numeric_limits<W>::max()): dist(init) {}

    Distance& operator=(const W val) {
        dist = val;
        return *this;
    }

    friend Distance operator+(const Distance& u, const Distance& v) {
        return {u.dist + v.dist};
    }

    friend bool operator<(const Distance& u, const Distance& v) {
        return u.dist < v.dist;
    }

    bool operator()(const Distance& u, const Distance& v) {
        return u < v;
    }

    bool isInf() {
        return dist == numeric_limits<W>::max();
    }
};

template<class V, class W>
pair<W, list<V>> Graph<V, W>::BellmanFord(const V& s, const V &t, bool *cycle) {
    map<V, Distance<W>> dist;
    map<V, V> parent;

    if (g.find(s) == g.end())
        return {};
    dist[s] = 0;
    // we keep looping over all edges in the graph as (|V| - 1) times,
    // this will ensure that by the end of the loop, dist will contain
    // the minimum cost to all vertices.
    for (auto i = 0u; i < g.size(); i++) {
        for (auto v : g)
            // this check is to avoid subtracting Inf and negative weights
            if (!dist[v.first].isInf())
                for (auto nei : v.second->adj) {
                    Distance<W> cost = dist[v.first] + nei.first;
                    // relaxing the edge if we've found a better distance
                    if (cost < dist[nei.second->self]) {
                        dist[nei.second->self] = cost;
                        parent[nei.second->self] = v.first;
                    }
                }
    }

    list<V> path;
    V node = t;

    // after the termination of the algorithm, we check once more to see if
    // we have a negative cycle. simply, if we have found a better cost after
    // the termination of the algorithm, then this implies a negative cycle.
    // we simply need to find one vertex in that cycle to trace back it back
    for (auto v : g)
        if (any_of(begin(v.second->adj), end(v.second->adj),
                   [&v, &node, &dist, &t, &cycle](auto &e) {
                       if (dist[v.first] + e.first < dist[e.second->self])
                           node = v.first;
                       return (*cycle = node != t);}))
            break;

    // construct the path or extract the negative cycle
    // since we break on both cases
    for (V curr = node; ; curr = parent[curr]) {
        path.push_front(curr);
        if ((node == curr && path.size() > 1) || curr == s)
            break;
    }
    return {dist[t].dist, path};
}

template<class V, class W>
pair<W, list<V>> Graph<V, W>::Dijkstra(const V& s, const V &t) {
    // Using a an ordered set is a neat optimization since we don't need to
    // keep pushing new distances and thus creating outaed ones int the queue,
    // but rather, teh set will always contains the best found yet.
    set<pair<Distance<W>, V>, less<pair<Distance<W>, V>>> pq;
    map<V, Distance<W>> dist;
    map<V, V> parent;

    if (g.find(s) == g.end())
        return {};
    dist[s] = 0;
    pq.insert({0, s});
    while (!pq.empty()) {
        auto e = pq.begin()->second; pq.erase(pq.begin());

        // since we traverse always the next most promising vertex by
        // dequeuing from the pq, once we reach the destination, it's
        // cost will never change
        if (e == t) break;

        for (auto nei: g[e]->adj) {
            // if any edge has a negative weight, we shall not precede!
            if (nei.first < 0)
                return {dist[t].dist, {}};
            // computing the new distance and perform the edges relaxation
            // simply by choosing the min distance
            Distance<W> cost = dist[e] + nei.first;
            if (cost < dist[nei.second->self]) {
                parent[nei.second->self] = e;
                // removing the old pair
                pq.erase({dist[nei.second->self], nei.second->self});
                dist[nei.second->self] = cost;
                // inserting the new best found distance
                pq.insert({dist[nei.second->self], nei.second->self});
            }
        }
    }
    return {dist[t].dist, construct_path(parent, s, t)};
}

template<class V, class W>
pair<W, list<V>> Graph<V, W>::FloydWarshall(const V& s, const V &t) {
}

template class Graph<int, int>;
template class Graph<char, int>;
template class Graph<string, int>;
