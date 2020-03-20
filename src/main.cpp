// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   graph_algorithms.cc                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/03/16 00:26:34 by archid-           #+#    #+#             //
//   Updated: 2020/03/20 21:44:03 by archid-          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Graph.class.hpp"

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
