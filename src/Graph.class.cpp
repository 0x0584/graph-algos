// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Graph.class.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/03/16 00:49:43 by archid-           #+#    #+#             //
//   Updated: 2020/03/23 08:31:33 by archid-          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <fstream>
#include <cstdlib>
#include <ctime>

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
    for (auto itr = g.begin(); itr != g.end(); itr++) {
        cout << "Vertex: " << itr->first << " " << itr->second->self << endl;
        auto adj = itr->second->adj;
        for (auto jtr = adj.begin(); jtr != adj.end(); jtr++)
            cout << jtr->first << " " << jtr->second->self << endl;
        cout << endl;
    }
}

pair<string, string> Graph::getVertexPair() {
    return make_pair(g.begin()->first, g.rbegin()->first);
}

bool Graph::addVertex(const string& s) {
	if (g.find(s) != g.end())
		return false;
	g[s] = new Vertex(s);
	return true;
}

void Graph::addEdge(const string& from, const string& to, int w,
					bool directed) {
	addVertex(from); addVertex(to);
	g.find(from)->second->adj.push_back(make_pair(w, g.find(to)->second));
	if (!directed)
		g.find(to)->second->adj.push_back(make_pair(w, g.find(from)->second));
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
        // pushing vertices before testing on arrival to include
        // source and destination nodes
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
	while (!q.empty())
	{
		if (q.front() == t) break;
		auto neighbors = g.find(q.front())->second->adj;
		for (auto itr = neighbors.begin(); itr != neighbors.end(); itr++) {
            // this plays the role of marking vertices as seen, since we
            // only set the parent once, thus we can ignore vertices that
            // already have a parent
			if (parent.find(itr->second->self) != parent.end())
				continue;
			q.push(itr->second->self);
			parent[itr->second->self] = q.front();
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
		auto neighbors = g.find(e.second)->second->adj;
		for (auto iter = neighbors.begin(); iter != neighbors.end(); iter++) {
            // initialize all undiscovered vertices to infinity
            if (dist.find(iter->second->self) == dist.end())
                 dist[iter->second->self] = numeric_limits<int>::max();
            // computing the new distance and perform the edges relaxation
            // simply by choosing the min distance
			int cost = dist[e.second] + iter->first;
			if (cost < dist[iter->second->self]) {
				parent[iter->second->self] = e.second;
				dist[iter->second->self] = cost;
                // update the best distance by enqueuing the new
                // distance. Although this might cause duplication
				pq.push({cost, iter->second->self});
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

void Graph::sccDFS(Vertex *e, vector<list<string>>& scc, vector<string>& v,
                   int& id, map<string, pair<int, int>>& links) {
    // we push all vertices to the vector, so that we can tell which
    // vertices we're currently following
	v.push_back(e->self);
	links[e->self] = {id, id};
	id++;

    // Traverse all the adjacent vertices in a DFS fashion
	for (auto itr = e->adj.begin(); itr != e->adj.end(); itr++) {
		if (links.find(itr->second->self) == links.end())
			sccDFS(itr->second, scc, v, id, links);
        // on the callback, we set the lowest_id to be the min between
        // the neighbors lowest, and self's lowest.
        // this process happens recursively so that all the vertices
        // that belong to the same connected component have same lowest id
		if (find(v.begin(), v.end(), itr->second->self) != v.end())
			links[e->self].second = min(links[e->self].second,
                                        links[itr->second->self].second);
	}

    // once we return finish the recursive DFS, and return to the
    // initial callback, we pop from the visiting vector all the
    // vertices that belong to the connected component
	if (links[e->self].first == links[e->self].second) {
		list<string> lst;
		for (auto node = v.back(); ; node = v.back()) {
			v.pop_back();
			lst.push_back(node);
			if (node == e->self)
				break;
		}
        scc.push_back(lst);
	}
}

vector<list<string>> Graph::SCC() {
	map<string, pair<int, int>> links; // a pair of <id, lowest_id>
	vector<string> visiting;
	vector<list<string>> scc;
	int id = 0;

	for (auto itr = g.begin(); itr != g.end(); itr++)
        // each time we start at a different node, but only if it's
        // not a part of an already found connected component
		if (links.find(itr->first) == links.end())
            sccDFS(itr->second, scc, visiting, id, links);
	return scc;
}
