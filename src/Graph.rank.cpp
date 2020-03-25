// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Graph.rank.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/03/25 13:12:23 by archid-           #+#    #+#             //
//   Updated: 2020/03/25 18:31:52 by archid-          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Graph.class.hpp"

template<class T, class W>
map<T, W> Graph<T, W>::rankByEdges(bool out) {
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
    map<T, pair<double, double>> m;

    const double decay_rate = 0.85; // rate of successfuly browsing all links

	for (auto e : g) m[e.first] = {1.0 / g.size(), 0.0};

    for (auto e : m)
    {
        auto rank = e.second;
        rank.second = decay_rate * (rank.first / g[e.first]->adj.size());
    }

	return s;
}

template class Graph<int, int>;
template class Graph<char, int>;
template class Graph<string, int>;
