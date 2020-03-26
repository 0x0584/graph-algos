// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Graph.BFS.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/03/25 13:09:26 by archid-           #+#    #+#             //
//   Updated: 2020/03/26 15:28:01 by archid-          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Graph.class.hpp"

template<class T, class W>
list<T> Graph<T, W>::BFS(const T& s, const T& t) {
	map<T, T> parent;
	queue<T> q;

	if (g.find(s) == g.end())
		return {};
	q.push(s);
	while (!q.empty() && q.front() != t)
	{
		for (auto nei: g[q.front()]->adj) {
			// this plays the role of marking vertices as seen, since we
			// only set the parent once, thus we can ignore vertices that
			// already have a parent
			if (parent.find(nei.second->self) != parent.end())
				continue;
			q.push(nei.second->self);
			parent[nei.second->self] = q.front();
		}
		q.pop();
	}
	return construct_path(parent, s, t);
}

template<class T, class W>
void Graph<T, W>::BFS(T& s, T (*callback)(T& e, int layer)) {
    queue<pair<Vertex *, int>> call_q; // modification callback queue
    queue<T> q;                        // traversing vertices queue
    deque<int> nei_q;                  // neighbors counting queue
    set<T> v;                          // already visited vertices
    int layer = 0;                     // BFS layering

    q.push(s);
    v.insert(s);
    call_q.push({g[s], layer++});
    nei_q.push_back(g[s]->adj.size());
    nei_q.push_back(1);
    while (!q.empty()) {
        for (auto nei : g[q.front()]->adj) {
            if (nei_q.front())
                nei_q.front() -= 1;
            else {
                layer++;
                nei_q.pop_front();
                nei_q.push_back(1);
            }
            if (v.find(nei.second->self) != v.end())
                continue;
            v.insert(nei.second->self);
            q.push(nei.second->self);
            call_q.push({g[nei.second->self], layer});
            nei_q.back() += nei.second->adj.size();
        }
        q.pop();
    }
    while (!call_q.empty()) {
        auto e = call_q.front(); call_q.pop();
        g.erase(e.first->self);
        g[callback(e.first->self, e.second)] = e.first;
    }
}

template class Graph<int, int>;
template class Graph<char, int>;
template class Graph<string, int>;
