// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   graph_algorithms.cc                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/03/16 00:26:34 by archid-           #+#    #+#             //
//   Updated: 2020/03/21 15:27:16 by archid-          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Graph.class.hpp"

int main(void)
{
    Graph g;

    g.addEdge("a", "b", 4);
    g.addEdge("a", "c", 2);
    g.addEdge("c", "d", 1);
    g.addEdge("b", "c", 1);

    auto l = g.Dijkstra("k", "d");

    cout << "PATH: ";

    for (auto itr = l.begin(); itr != l.end(); itr++) {
        cout << *itr << " ";
    }
    cout << endl;
    return 0;
}
