// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   graph_algorithms.cc                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/03/16 00:26:34 by archid-           #+#    #+#             //
//   Updated: 2020/03/24 03:34:05 by archid-          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iomanip>

#include "Graph.class.hpp"

void testBFS(const char *file) {
	Graph *g = Graph::readGraph(file);

	auto p = g->getSampleVertexPair();
	auto l = g->BFS(p.first, p.second);

	cout << "Shortest Path between " << p.first << " and " << p.second
		 << " using BFS is: " << endl;
	for (auto itr = l.begin(); itr != l.end(); itr++) {
		cout << *itr << " ";
	}
	cout << endl << endl;
	delete g;
}

void testSCC(const char *file) {
	Graph *g = Graph::readGraph(file, true);

	auto l = g->SCC();

	cout << "Number of Connected Components: " << l.size() << endl;
	for (auto iter = l.begin(); iter != l.end(); iter++) {
		for (auto walk = iter->begin(); walk != iter->end(); walk++)
			cout << *walk << " ";
		cout << endl;
	}
	cout << endl;
	delete g;
}

void testDijkstra(const char *file) {
	Graph *g = Graph::readGraph(file, false, true);

	auto p = g->getSampleVertexPair();
	auto l = g->Dijkstra(p.first, p.second);

	cout << "Shortest Path between " << p.first << " and " << p.second
		 << " using Dijkstra is: " << endl;
	for (auto itr = l.begin(); itr != l.end(); itr++) {
		cout << *itr << " ";
	}
	cout << endl << endl;
	delete g;
}

void testEdgeRank(const char *file) {
	Graph *g = Graph::readGraph(file, true, true);

	auto out = g->rankByEdges(true);
	auto in = g->rankByEdges(false);
	auto vers = g->getVertices();

	cout << "ranking vertices by # of in/out edges" << endl;
	for (auto e : vers)
		cout << setw(3) << e << " has in: " << in[e]
			 << " out: " << out[e] << endl;
	cout << endl;
	delete g;
}

void testEdgeVertexManips(const char *file) {
	Graph g;

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

int main(int argc, char *argv[])
{
	if (argc == 1)
		exit(-1);

	testBFS(argv[1]);
	testSCC(argv[1]);
	testDijkstra(argv[1]);
	testEdgeRank(argv[1]);
    testEdgeVertexManips(argv[1]);
	return 0;
}
