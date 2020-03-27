// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Vertex.class.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/03/27 15:33:28 by archid-           #+#    #+#             //
//   Updated: 2020/03/27 15:42:18 by archid-          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef VERTEX_CLASS_H
# define VERTEX_CLASS_H

#include "common.hpp"

// this is an internal structure that to represent each vertex
// it holds the vertex identity as well as its adjacent vertices
template<class V, class W>
struct Vertex
{
    V self;                         // vertex's identity

    std::set<std::pair<W, Vertex *>> adj;  // out-going edges
    std::set<std::pair<W, Vertex *>> radj; // in-coming edges

    Vertex(V v = 0) : self(v) {}

    friend bool operator<(const Vertex& v, const Vertex& u) {
        return v.self < u.self;
    }
    friend bool operator>(const Vertex& v, const Vertex& u) {
        return v.self > u.self;
    }
    friend bool operator<=(const Vertex& v, const Vertex& u) {
        return v.self <= u.self;
    }
    friend bool operator>=(const Vertex& v, const Vertex& u) {
        return v.self >= u.self;
    }
    friend bool operator==(const Vertex& v, const Vertex& u) {
        return v.self == u.self;
    }
    friend bool operator!=(const Vertex& v, const Vertex& u) {
        return v.self != u.self;
    }
};

#endif /* VERTEX.CLASS_H */
