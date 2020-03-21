// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Graph.class.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/03/16 00:49:43 by archid-           #+#    #+#             //
//   Updated: 2020/03/21 20:50:58 by archid-          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Graph.class.hpp"

Graph::Graph() : g() {}

Graph::~Graph() {
	for (auto itr = g.begin(); itr != g.end(); itr++)
		delete itr->second;
}

bool Graph::addVertex(const string &s) {
	if (g.find(s) != g.end())
		return false;
	g[s] = new Vertex(s);
	return true;
}

void Graph::addEdge(const string& from, const string& to, double w,
					bool directed) {
	addVertex(from); addVertex(to);
	g.find(from)->second->adj.push_back(make_pair(w, g.find(to)->second));
	if (!directed)
		g.find(to)->second->adj.push_back(make_pair(w, g.find(from)->second));
}

list<string> construct_path(map<string, string>& parent,
							const string &s, const string &t) {
	list<string> path;
	string walk = t;

	if (parent.find(t) == parent.end())
		return path;
	while (true) {
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
	map<string, double> dist;
	map<string, string> parent;
	priority_queue<pair<string, double>> pq;

	if (g.find(s) == g.end())
		return {};
	dist[s] = 0.0;
	pq.push({s, 0.0});
	while (!pq.empty()) {
		auto e = pq.top(); pq.pop();
		if (dist.find(e.first) != dist.end() && dist[e.first] < e.second)
			continue;
		auto neighbors = g.find(e.first)->second->adj;
		for (auto iter = neighbors.begin(); iter != neighbors.end(); iter++) {
			if (dist.find(iter->second->self) != dist.end())
				continue;
			double cost = dist[e.first] + iter->first;
			if (dist.find(iter->second->self) == dist.end()
					|| cost < dist[iter->second->self]) {
				parent[iter->second->self] = e.first;
				dist[iter->second->self] = cost;
				pq.push({iter->second->self, cost});
			}
		}
	}
	return construct_path(parent, s, t);
}

void Graph::sccDFS(Vertex *e, vector<list<string>>& scc, vector<string>& vec,
                   int& id, map<string, pair<int, int>>& links) {

	vec.push_back(e->self);
	links[e->self] = {id, id};
	id++;
	for (auto itr = e->adj.begin(); itr != e->adj.end(); itr++) {
		if (links.find(itr->second->self) == links.end())
			sccDFS(itr->second, scc, vec, id, links);
		if (find(vec.begin(), vec.end(), itr->second->self) != vec.end())
			links[e->self].second = min(links[e->self].second,
									 links[itr->second->self].second);
	}
	if (links[e->self].first == links[e->self].second) {
		list<string> lst;
		for (auto node = vec.back(); ; node = vec.back()) {
			vec.pop_back();
			links[node].second = links[node].first;
			lst.push_back(node);
			if (node == e->self)
				break;
		}
        scc.push_back(lst);
	}
}

vector<list<string>> Graph::SCC() {
	map<string, pair<int, int>> links;
	vector<string> vec;
	vector<list<string>> scc;
	int id = 0;

	for (auto itr = g.begin(); itr != g.end(); itr++) {
		if (links.find(itr->first) == links.end()) {
            sccDFS(itr->second, scc, vec, id, links);
        }
	}
	return scc;
}
