// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   graph_algorithms.cc                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/03/16 00:26:34 by archid-           #+#    #+#             //
//   Updated: 2020/03/27 14:05:09 by archid-          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <fstream>
#include <iomanip>

#include "Graph.class.hpp"

typedef Graph<string, int> sample_graph;

void fillGraph(sample_graph& g, const char *file,
               bool directed = false, bool weighted = false) {
	ifstream in(file);
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
		g.addEdge(u, v, weighted ? stoi(w) : 1 , directed);
	}
}

void testBFS(const char *file) {

    sample_graph g;

    fillGraph(g, file);
	auto p = g.getSampleVertexPair();
	auto l = g.BFS(p.first, p.second);

	cout << "Shortest Path between " << p.first << " and " << p.second
		 << " using BFS is: " << endl;
	for (auto itr = l.begin(); itr != l.end(); itr++)
		cout << *itr << " ";
	cout << endl << endl;

    cout << "Initial Graph" << endl;
    g.dumpGraph();
    g.BFS(p.first, [](string& s, int li) {
                       return s += "[" + to_string(li) + "]";
                   });
    cout << "After Layered BFS Travering" << endl;
    g.dumpGraph();
}

void testSCC(const char *file) {
    sample_graph g;

    fillGraph(g, file, true);
	auto l = g.SCC();

	cout << "Number of Connected Components: " << l.size() << endl;
	for (auto iter = l.begin(); iter != l.end(); iter++) {
		for (auto walk = iter->begin(); walk != iter->end(); walk++)
			cout << *walk << " ";
		cout << endl;
	}
	cout << endl;
}

void testDijkstra(const char *file) {
    sample_graph g;

    fillGraph(g, file, false, true);
	auto p = g.getSampleVertexPair();
	auto l = g.Dijkstra(p.first, p.second);

	cout << "Shortest Path between " << p.first << " and " << p.second
		 << " using Dijkstra is: " << endl;
	for (auto e: l)
		cout << e << " ";
	cout << endl << endl;
}

void testEdgeRank(const char *file) {
    sample_graph g;

    fillGraph(g, file, true, true);
	auto out = g.rankByEdges(true);
	auto in = g.rankByEdges(false);
	auto vers = g.getVertices();

	cout << "ranking vertices by # of in/out edges" << endl;
	for (auto e : vers)
		cout << setw(3) << e << " has in: " << in[e]
			 << " out: " << out[e] << endl;
	cout << endl;
}

void testEdgeVertexManips(const char *file) {
	sample_graph g;

    (void)file;
    cout << "Initial graph" << endl;
    g.dumpGraph();

    g.addEdge("foo", "bar");
    g.addEdge("buzz", "bar");
    g.addEdge("buzz", "foo");
    g.addEdge("fuzz", "bar");
    g.addEdge("foo", "car");

    cout << "adding some vertices and edges" << endl;
    g.dumpGraph();

    cout << "removing some vertices and edges" << endl;
    g.removeVertex("foo");
    g.removeEdge("buzz", "bar", true);
    g.removeEdge("fuzz", "bar");

    cout << "final graph" << endl;
    g.dumpGraph();
}

void testPageRank(const char *file) {
    sample_graph g;

    fillGraph(g, file, true); g.dumpGraph();

    auto s = g.pageRank();

    cout << " >> ranks" << endl;
    for (auto e : s)
        cout << e.second << " " << e.first << endl;
}

int main(int argc, char *argv[])
{
	if (argc == 1)
		exit(-1);

	testBFS(argv[1]);
	testSCC(argv[1]);
	testDijkstra(argv[1]);
	testEdgeRank(argv[1]);
    testEdgeVertexManips(argv[1]);
    testPageRank(argv[1]);

	return 0;
}
