// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Graph.class.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/03/16 00:49:43 by archid-           #+#    #+#             //
//   Updated: 2020/03/24 03:31:53 by archid-          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <fstream>

#include "Graph.class.hpp"

Graph::Graph() : g() {}

Graph::~Graph() {
	for (auto itr = g.begin(); itr != g.end(); itr++)
		// vertices were allocated dynamically so they must be free'd
		delete itr->second;
}

Graph *Graph::readGraph(const char *file, bool directed, bool weighted) {
	ifstream in(file);
	Graph *g = new Graph();
	string s;

	if (!in) exit(-1);

	// basically each line of the file is u v w
	// so we read line by line and add edges
	while (in && getline(in, s)) {
		string u, v, w;

		u = string(s.substr(0, s.find(" ")));
		s.erase(0, s.find(" ") + 1);
		v = string(s.substr(0, s.find(" ")));
		s.erase(0, s.find(" ") + 1);
		w = string(s.substr(0, s.find(" ")));
		g->addEdge(u, v, weighted ? stoi(w) : 1 , directed);
	}
	return g;
}

void Graph::dumpGraph() {
	for (auto u: g) {
		cout << "Vertex: " << u.first << " ";
		for (auto e: u.second->adj)
			cout << "(" << e.first << "," << e.second->self << ") ";
		cout << endl;
	}
    cout << endl;
}

pair<string, string> Graph::getSampleVertexPair() {
	return make_pair(g.begin()->first, g.rbegin()->first);
}

vector<string> Graph::getVertices() {
	vector<string> v;

	for (auto u: g)
		v.push_back(u.first);
	return v;
}

vector<tuple<string, string, int>> Graph::getEdges() {
	vector<tuple<string, string, int>> v;

	for (auto u: g)
		for (auto e: u.second->adj)
			v.push_back({u.first, e.second->self, e.first});
	return v;
}

bool Graph::addVertex(const string& s) {
	if (g.find(s) != g.end())
		return false;
	g[s] = new Vertex(s);
	return true;
}

void Graph::removeVertex(const string& s) {
    for (auto nei: g[s]->adj)
        nei.second->radj.erase(
            find_if(nei.second->radj.begin(),
                    nei.second->radj.end(),
                    [&s](const pair<int, Vertex *>& e) {
                        return s == e.second->self;
                    }));
    for (auto nei: g[s]->radj)
        nei.second->adj.erase(
            find_if(nei.second->adj.begin(),
                    nei.second->adj.end(),
                    [&s](const pair<int, Vertex *>& e) {
                        return s == e.second->self;
                    }));
    delete g[s];
    g.erase(s);
}

void Graph::set_edge(const string& from, const string& to, int w) {
	g[from]->adj.push_back({w, g[to]});
	g[to]->radj.push_back({w, g[from]});
}

void Graph::addEdge(const string& from, const string& to, int w,
					bool directed) {
	addVertex(from); addVertex(to);
	set_edge(from, to, w);
	if (!directed) set_edge(to, from, w);
}

void Graph::unset_edge(const string& from, const string& to) {
    g[from]->adj.erase(
        find_if(g[from]->adj.begin(), g[from]->adj.end(),
                [&to](const pair<int, Vertex *>& e) {
                          return to == e.second->self;
                }));
    g[to]->radj.erase(
        find_if(g[to]->radj.begin(), g[to]->radj.end(),
                [&from](const pair<int, Vertex *>& e) {
                    return from == e.second->self;
                }));
}

void Graph::removeEdge(const string& from, const string& to, bool directed) {
    if (g.find(from) == g.end() || g.find(to) == g.end())
        return ;
    unset_edge(from, to);
    if (!directed)
        unset_edge(to, from);
}

list<string> Graph::construct_path(map<string, string>& parent,
								   const string &s, const string &t) {
	list<string> path;
	string walk = t;

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

list<string> Graph::BFS(const string &s, const string &t) {
	map<string, string> parent;
	queue<string> q;

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

list<string> Graph::Dijkstra(const string& s, const string &t) {
	map<string, int> dist;
	map<string, string> parent;
	priority_queue<pair<int, string>,
				   vector<pair<int, string>>,
				   greater<pair<int, string>>> pq;

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
				dist[nei.second->self] = numeric_limits<int>::max();
			// computing the new distance and perform the edges relaxation
			// simply by choosing the min distance
			int cost = dist[e.second] + nei.first;
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

inline void Graph::set_link(map<string, pair<int, int>>& links,
							Vertex *u, Vertex *v) {
	links[u->self].second = min(links[u->self].second,
								links[v->self].second);
}

void Graph::sccDFS(Vertex *e, vector<vector<string>>& scc, vector<string>& v,
				   int& id, map<string, pair<int, int>>& links) {
	// we push all vertices to the vector, so that we can tell which
	// vertices we're currently following
	v.push_back(e->self);
	links[e->self] = {id, id};
	id++;

	// Traverse all the adjacent vertices in a DFS fashion
	for (auto nei: e->adj) {
		// recursively keep visiting undiscovered vertices with DFS
		if (links.find(nei.second->self) == links.end())
			sccDFS(nei.second, scc, v, id, links);
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
	if (links[e->self].first == links[e->self].second) {
		vector<string> vect;
		while (true) {
			auto node = v.back(); v.pop_back();
			vect.push_back(node);
			if (node == e->self)
				break;
		}
		scc.push_back(vect);
	}
}

vector<vector<string>> Graph::SCC() {
	map<string, pair<int, int>> links; // a pair of <id, lowest_id>
	vector<string> visiting;
	vector<vector<string>> scc;
	int id = 0;

	for (auto itr = g.begin(); itr != g.end(); itr++)
		// each time we start at a different node, but only if it's
		// not a part of an already found connected component
		if (links.find(itr->first) == links.end())
			sccDFS(itr->second, scc, visiting, id, links);
	return scc;
}

map<string, int> Graph::rankByEdges(bool out) {
	map<string, int> m;

	for (auto itr = g.begin(); itr != g.end(); itr++) {
		auto size = out ? itr->second->adj.size()
			: itr->second->radj.size();
		if (size != 0) m[itr->first] = size;
	}
	return m;
}
