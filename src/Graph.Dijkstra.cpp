// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Graph.Dijkstra.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/03/25 13:09:57 by archid-           #+#    #+#             //
//   Updated: 2020/03/28 05:08:45 by archid-          ###   ########.fr       //
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
};

template<class T, class W>
pair<W, list<T>> Graph<T, W>::Dijkstra(const T& s, const T &t) {
    // Using a an ordered set is a neat optimization since we don't need to
    // keep pushing new distances and thus creating outaed ones int the queue,
    // but rather, teh set will always contains the best found yet.
    set<pair<Distance<W>, T>, less<pair<Distance<W>, T>>> pq;
    map<T, Distance<W>> dist;
    map<T, T> parent;

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

template class Graph<int, int>;
template class Graph<char, int>;
template class Graph<string, int>;
