// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   graph_algorithms.cc                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/03/16 00:26:34 by archid-           #+#    #+#             //
//   Updated: 2020/03/21 20:08:42 by archid-          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Graph.class.hpp"

int main(void)
{
	Graph g;

	g.addEdge("a", "b", 1, true);
	g.addEdge("a", "e", 1, true);
	g.addEdge("b", "f", 1, true);
	g.addEdge("c", "b", 1, true);
	g.addEdge("c", "g", 1, true);
	g.addEdge("c", "d", 1, true);
	g.addEdge("d", "g", 1, true);
	g.addEdge("e", "a", 1, true);
	g.addEdge("e", "f", 1, true);
	g.addEdge("f", "c", 1, true);
	g.addEdge("f", "g", 1, true);
	g.addEdge("g", "h", 1, true);
	g.addEdge("h", "d", 1, true);

	auto l = g.SCC();

	cout << "Number of Connected Components: " << l.size() << endl;

    for (auto iter = l.begin(); iter != l.end(); iter++) {
        for (auto walk = iter->begin(); walk != iter->end(); walk++)
            cout << *walk << " ";
        cout << endl;
    }
	return 0;
}
