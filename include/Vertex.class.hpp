// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Vertex.class.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/03/27 15:33:28 by archid-           #+#    #+#             //
//   Updated: 2020/03/27 17:39:04 by archid-          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef VERTEX_CLASS_H
# define VERTEX_CLASS_H

#include "common.hpp"

// this is an internal structure that to represent each vertex
// it holds the vertex identity as well as its adjacent vertices
//
// NOTE: this structure is note intented to be used on its own
template<class V, class W>
struct Vertex
{
    V self;                     // vertex's identity

    // This is a representation of adjacency list for both out-going edges
    // and in-coming edges, where adj stores edges from this to others, and
    // radj store edges that have this in their adj
    set<pair<W, Vertex *>> adj, radj;

    Vertex(V v = 0) : self(v) {}
};

#endif
