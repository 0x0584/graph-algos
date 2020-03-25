// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Graph.Dijkstra.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/03/25 13:09:57 by archid-           #+#    #+#             //
//   Updated: 2020/03/25 13:14:16 by archid-          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Graph.class.hpp"


template<class T, class W>
list<T> Graph<T, W>::Dijkstra(const T& s, const T &t) {
	map<T, W> dist;
	map<T, T> parent;
	priority_queue<pair<W, T>,
				   vector<pair<W, T>>,
				   greater<pair<W, T>>> pq;

	if (g.find(s) == g.end())
		return {};
	dist[s] = 0;
	pq.push({0, s});
	while (!pq.empty()) {
		auto e = pq.top(); pq.pop();
		// we can ignore vertices that already have a minimal distance,
		// this is a lazy way of getting rid of outdated distances
		if (dist.find(e.second) != dist.end() && dist[e.second] < e.first)
			continue;
		for (auto nei: g[e.second]->adj) {
			// initialize all undiscovered vertices to infinity
			if (dist.find(nei.second->self) == dist.end())
				dist[nei.second->self] = numeric_limits<W>::max();
			// computing the new distance and perform the edges relaxation
			// simply by choosing the min distance
			W cost = dist[e.second] + nei.first;
			if (cost < dist[nei.second->self]) {
				parent[nei.second->self] = e.second;
				dist[nei.second->self] = cost;
				// update the best distance by enqueuing the new
				// distance. Although this might cause duplication
				pq.push({cost, nei.second->self});
			}
		}
		// since we traverse always the next most promising vertex by
		// dequeuing from the pq, once we reach the destination, it's
		// cost will never change
		if (e.second == t)
			break;
	}
	return construct_path(parent, s, t);
}

template class Graph<int, int>;
template class Graph<char, int>;
template class Graph<string, int>;
