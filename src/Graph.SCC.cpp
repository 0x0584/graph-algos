// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Graph.SCC.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/03/25 13:10:24 by archid-           #+#    #+#             //
//   Updated: 2020/03/27 16:09:51 by archid-          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Graph.class.hpp"

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

template<class T, class W>
void sccDFS(Vertex<T, W> *e, vector<vector<T>>& scc, vector<T>& v,
            Link& l, map<T, Link>& links) {
    // we push all vertices to the vector, so that we can tell which
    // vertices we're currently following
    v.push_back(e->self);
    links[e->self] = l;

    // Traverse all the adjacent vertices in a DFS fashion
    for (auto nei: e->adj) {
        // recursively keep visiting undiscovered vertices with DFS
        if (links.find(nei.second->self) == links.end())
            sccDFS(nei.second, scc, v, l, links);
        // on the callback, we set the lowest_id to be the min between
        // the neighbors lowest, and self's lowest.
        // this process happens recursively so that all the vertices
        // that belong to the same connected component have same lowest id
        if (find(v.begin(), v.end(), nei.second->self) != v.end())
            links[e->self].setLow(links[nei.second->self]);
    }

    // once we return finish the recursive DFS, and return to the
    // initial callback, we pop from the visiting vector all the
    // vertices that belong to the connected component
    if (links[e->self].id == links[e->self].low_id) {
        vector<T> vect;
        while (true) {
            auto node = v.back(); v.pop_back();
            vect.push_back(node);
            if (node == e->self) break;
        }
        scc.push_back(vect);
    }
}

template<class T, class W> vector<vector<T>> Graph<T, W>::SCC() {
    map<T, Link> links; // a pair of <id, lowest_id>
    vector<T> visiting;
    vector<vector<T>> scc;
    Link lnk = Link();

    for (auto itr = g.begin(); itr != g.end(); itr++)
        // each time we start at a different node, but only if it's
        // not a part of an already found connected component
        if (links.find(itr->first) == links.end())
            sccDFS(itr->second, scc, visiting, lnk, links);
    return scc;
}

template class Graph<int, int>;
template class Graph<char, int>;
template class Graph<string, int>;
