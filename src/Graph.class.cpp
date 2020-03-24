// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Graph.class.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/03/16 00:49:43 by archid-           #+#    #+#             //
//   Updated: 2020/03/25 11:09:04 by archid-          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Graph.class.hpp"

template<class T, class W> Graph<T, W>::Graph() : g() {}
template<class T, class W> Graph<T, W>::~Graph() {
	for (auto itr = g.begin(); itr != g.end(); itr++)
		// vertices were allocated dynamically so they must be free'd
		delete itr->second;
}

template<class T, class W>
void Graph<T, W>::dumpGraph() {
	for (auto u: g) {
		cout << "Vertex: " << u.first << " ";
		for (auto e: u.second->adj)
			cout << "(" << e.first << "," << e.second->self << ") ";
		cout << endl;
	}
    cout << endl;
}

template<class T, class W>
pair<T, T> Graph<T, W>::getSampleVertexPair() {
	return make_pair(g.begin()->first, g.rbegin()->first);
}

template<class T, class W>
vector<T> Graph<T, W>::getVertices() {
	vector<T> v;

	for (auto u: g)
		v.push_back(u.first);
	return v;
}

template<class T, class W>
vector<tuple<T, T, W>> Graph<T, W>::getEdges() {
	vector<tuple<T, T, W>> v;

	for (auto u: g)
		for (auto e: u.second->adj)
			v.push_back({u.first, e.second->self, e.first});
	return v;
}

template<class T, class W>
bool Graph<T, W>::addVertex(const T& s) {
	if (g.find(s) != g.end())
		return false;
	g[s] = new Vertex(s);
	return true;
}

template<class T, class W>
void Graph<T, W>::removeVertex(const T& s) {
    for (auto nei: g[s]->adj)
        nei.second->radj.erase(
            find_if(nei.second->radj.begin(),
                    nei.second->radj.end(),
                    [&s](const pair<W, Vertex *>& e) {
                        return s == e.second->self;
                    }));
    for (auto nei: g[s]->radj)
        nei.second->adj.erase(
            find_if(nei.second->adj.begin(),
                    nei.second->adj.end(),
                    [&s](const pair<W, Vertex *>& e) {
                        return s == e.second->self;
                    }));
    delete g[s];
    g.erase(s);
}

template<class T, class W>
void Graph<T, W>::set_edge(const T& from, const T& to, W w) {
	g[from]->adj.push_back({w, g[to]});
	g[to]->radj.push_back({w, g[from]});
}

template<class T, class W>
void Graph<T, W>::addEdge(const T& from, const T& to, W w,
					bool directed) {
	addVertex(from); addVertex(to);
	set_edge(from, to, w);
	if (!directed) set_edge(to, from, w);
}

template<class T, class W>
void Graph<T, W>::unset_edge(const T& from, const T& to) {
    g[from]->adj.erase(
        find_if(g[from]->adj.begin(), g[from]->adj.end(),
                [&to](const pair<W, Vertex *>& e) {
                          return to == e.second->self;
                }));
    g[to]->radj.erase(
        find_if(g[to]->radj.begin(), g[to]->radj.end(),
                [&from](const pair<W, Vertex *>& e) {
                    return from == e.second->self;
                }));
}

template<class T, class W>
void Graph<T, W>::removeEdge(const T& from, const T& to, bool directed) {
    if (g.find(from) == g.end() || g.find(to) == g.end())
        return ;
    unset_edge(from, to);
    if (!directed)
        unset_edge(to, from);
}

template<class T, class W>
list<T> Graph<T, W>::construct_path(map<T, T>& parent,
								   const T &s, const T &t) {
	list<T> path;
	T walk = t;

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

template<class T, class W>
list<T> Graph<T, W>::BFS(const T &s, const T &t) {
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

template<class T, class W>
inline void Graph<T, W>::set_link(map<T, Link>& links, Vertex *u, Vertex *v) {
	links[u->self].low_id = min(links[u->self].low_id, links[v->self].low_id);
}

template<class T, class W>
void Graph<T, W>::sccDFS(Vertex *e, vector<vector<T>>& scc, vector<T>& v,
                         Link& l, map<T, Link>& links) {
	// we push all vertices to the vector, so that we can tell which
	// vertices we're currently following
	v.push_back(e->self);
    links[e->self] = Link(l);

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
			set_link(links, e, nei.second);
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

template<class T, class W>
vector<vector<T>> Graph<T, W>::SCC() {
	map<T, Link> links; // a pair of <id, lowest_id>
	vector<T> visiting;
	vector<vector<T>> scc;
	Link lnk;

	for (auto itr = g.begin(); itr != g.end(); itr++)
		// each time we start at a different node, but only if it's
		// not a part of an already found connected component
		if (links.find(itr->first) == links.end())
			sccDFS(itr->second, scc, visiting, lnk, links);
	return scc;
}

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
    const W n_vertices = g.size();

    for (auto e : g) s.insert({1.0 / n_vertices, e.first});


    return s;
}

template class Graph<int, int>;
template class Graph<char, int>;
template class Graph<string, int>;
