// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Graph.rank.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/03/25 13:12:23 by archid-           #+#    #+#             //
//   Updated: 2020/03/27 16:40:01 by archid-          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Graph.class.hpp"
#include "Rank.class.hpp"

template<class T, class W>
set<pair<double, T>,
    greater<pair<double, T>>> Graph<T, W>::rankByEdges(bool out) {
    set<pair<double, T>, greater<pair<double, T>>> s;

    for (auto itr = g.begin(); itr != g.end(); itr++) {
        auto size = out ? itr->second->adj.size()
            : itr->second->radj.size();
        s.insert({size, itr->second->self});
    }
    return s;
}

template<class T, class W>
set<pair<double, T>,
    greater<pair<double, T>>> Graph<T, W>::pageRank() {
    set<pair<double, T>, greater<pair<double, T>>> s;

    if (!Rank<T, W>::init(g)) return {};
    while (Rank<T, W>::unstable) {
        Rank<T, W>::rankPages();
        Rank<T, W>::updateRanks();
    }
    for (auto e : Rank<T, W>::ranks)
        s.insert({e.second.r_old, e.first->self});
    return s;
}

template class Graph<int, int>;
template class Graph<char, int>;
template class Graph<string, int>;
