// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   graph_algorithms.cc                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/03/16 00:26:34 by archid-           #+#    #+#             //
//   Updated: 2020/03/16 02:58:24 by archid-          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <queue>

using namespace std;

class Graph
{
public:

    Graph() : g() {}

    ~Graph() {
        for (auto itr = g.begin(); itr != g.end(); itr++)
            delete itr->second;
    }

    void graphDump() {
        cout << "vertcies count: " << g.size() << endl;
        for (auto itr = g.begin(); itr != g.end(); itr++)
            itr->second->to_str();
    }

    bool addVertex(const string &s) {
        if (g.find(s) != g.end())
            return false;
        g[s] = new Vertex(s);
        return true;
    }

    void addEdge(const string &from, const string &to, int w = 1,
                 bool directed = false) {
        addVertex(from); addVertex(to);
        g.find(from)->second->adj.push_back(make_pair(w, g.find(to)->second));
        if (!directed)
            g.find(to)->second->adj.push_back(make_pair(w, g.find(from)->second));
    }

    // Breadth First Search is an elemnetary Graph algorithm that's perfect
    // for finding the shortest path in an "unweighted graph".
    list<string> BFS(const string &s, const string &t) {
        map<string, string> parent;
        queue<string> q;

        q.push(s);
        parent[s] = "";
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
        return bfs_helper_parent_path(parent, s, t);
    }

    list<string> Dijkstra(const string &s, const string &t) {

    }

    vector<list<string>> SCC() {

    }

private:

    struct Vertex
    {
        string self;
        vector<pair<int, Vertex *>> adj;

        Vertex(string s) : self(s) {};

        void to_str() {
            cout << "Vertex: " << self << endl;
            for (auto itr = adj.begin(); itr != adj.end(); itr++) {
                cout << itr->second->self << ": " << itr->first << endl;
            }
            cout << endl;
        }
    };

    map<string, Vertex *> g;
    list<string> bfs_helper_parent_path(map<string, string>& parent,
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
};

int main(int argc, char *argv[])
{
    Graph g;

    g.addEdge("a", "b");
    g.addEdge("a", "c");
    g.addEdge("c", "d");
    g.addEdge("b", "c");

    auto l = g.BFS("a", "d");

    cout << "PATH: ";

    for (auto itr = l.begin(); itr != l.end(); itr++) {
        cout << *itr << " ";
    }
    cout << endl;
    return 0;
}
