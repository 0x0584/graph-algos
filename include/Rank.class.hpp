// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Rank.class.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/03/27 15:36:17 by archid-           #+#    #+#             //
//   Updated: 2020/03/27 16:49:08 by archid-          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef RANK_CLASS_H
# define RANK_CLASS_H

# include "common.hpp"
# include "Vertex.class.hpp"

template<class V, class W>
struct Rank
{
    // binding every vertex with its rank
    typedef map<Vertex<V, W> *, Rank> RankMap;

    static const double decay_rate; // rate of browsing all links
    static const double epsilon;    // minimum variation of rank
    static RankMap ranks;           // the ranks of all vertices
    static bool unstable;           // false if ranks stoped varying
    static int N;                   // Number of vertices

    Vertex<V, W> *self;
    double r_old, r_new;

    Rank(Vertex<V, W> *v = nullptr, int n = 1)
        : self(v), r_old(1.0 / n), r_new(0.0) {}

    // replacing old rank with the new one
    void update();

    // compute the rank by summing all the old ranks of all vertices
    // that has self vertex as adjacent
    void update(double random_jump);

    // fills `ranks` with all vertices from the `g`
    static bool init(map<V, Vertex<V, W> *> g);

    // computes the random surfing factor for all vertices that has
    // no adjacent vertices
    static double randomJumpFactor();

    // rank all vertices in `ranks`
    static void rankPages();

    // calls update() for all vertices in `ranks`
    static void updateRanks();
};

#endif
