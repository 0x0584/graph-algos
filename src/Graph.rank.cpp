// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Graph.rank.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/03/25 13:12:23 by archid-           #+#    #+#             //
//   Updated: 2020/03/27 15:09:05 by archid-          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Graph.class.hpp"

template<class T, class W> map<T, W> Graph<T, W>::rankByEdges(bool out) {
	map<T, W> m;

	for (auto itr = g.begin(); itr != g.end(); itr++) {
		auto size = out ? itr->second->adj.size()
			: itr->second->radj.size();
		if (size != 0) m[itr->first] = size;
	}
	return m;
}

template<class T, class W>
set<pair<double, T>, greater<pair<double, T>>> Graph<T, W>::pageRank() {
	set<pair<double, T>, greater<pair<double, T>>> s;

    if (!Rank::init(g)) return {};
    while (Rank::unstable) {
        cout << " ============ " << endl;
        Rank::rankPages();
        Rank::updateRanks();
    }
    for (auto e : Rank::ranks) s.insert({e.second.r_old, e.first->self});
	return s;
}

template<class T, class W> const double Graph<T, W>::Rank::decay_rate = 0.85;
template<class T, class W> const double Graph<T, W>::Rank::epsilon = 1e-5;
template<class T, class W> bool Graph<T, W>::Rank::unstable = false;
template<class T, class W> int Graph<T, W>::Rank::N = 1;
template<class T, class W>
typename Graph<T, W>::Rank::RankMap Graph<T,W>::Rank::ranks = {};

template class Graph<int, int>;
template class Graph<char, int>;
template class Graph<string, int>;
