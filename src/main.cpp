// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   graph_algorithms.cc                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/03/16 00:26:34 by archid-           #+#    #+#             //
//   Updated: 2020/03/22 17:23:37 by archid-          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Graph.class.hpp"

void testBFS(const char *file) {
    Graph *g = Graph::readGraph(file);

    auto p = g->getVertexPair();
    auto l = g->BFS(p.first, p.second);

    cout << "Shortest Path between " << p.first << " and " << p.second
         << " using BFS is: " << endl;
    for (auto itr = l.begin(); itr != l.end(); itr++) {
        cout << *itr << " ";
    }
    cout << endl;
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
    delete g;
}

void testDijkstra(const char *file) {
    Graph *g = Graph::readGraph(file, false, true);

    auto p = g->getVertexPair();
    auto l = g->Dijkstra(p.first, p.second);

    cout << "Shortest Path between " << p.first << " and " << p.second
         << " using Dijkstra is: " << endl;
    for (auto itr = l.begin(); itr != l.end(); itr++) {
        cout << *itr << " ";
    }
    cout << endl;
    delete g;
}

int main(int argc, char *argv[])
{
	if (argc == 1)
		exit(-1);

    testBFS(argv[1]);
	testSCC(argv[1]);
    testDijkstra(argv[1]);

	return 0;
}
