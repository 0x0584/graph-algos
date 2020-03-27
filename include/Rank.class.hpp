// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Rank.class.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/03/27 15:36:17 by archid-           #+#    #+#             //
//   Updated: 2020/03/27 17:48:43 by archid-          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef RANK_CLASS_H
# define RANK_CLASS_H

# include "Vertex.class.hpp"

// In order to compute the rank of each vertex following the specifications of
// Google's PageRank algiorithms, this struct hold some constants and prodvides
// functionalities to help doing do so.
//
// NOTE: This is a helper struct, and not intended to be used on its own.
template<class V, class W>
struct Rank
{
    // binding every vertex with its rank
    typedef map<Vertex<V, W> *, Rank> RankMap;

    // decay factor or rate, is a constant that represents the rate of
    // successufly  browsing links, it is used to help the convergence of
    // the ranking proccess.
    static const double decay_rate;

    // generally, we keep computing the ranks until they converge, ie. the
    // difference between the old value and the new value is less that epsilon
    static const double epsilon;

    // if a number iterations is specified, then the epsilon convergence is
    // ignored and n_iterations are performed instead
    static int n_iterations;

    // Binding each vertex with it's rank as a map improves the performance
    static RankMap ranks;

    // this is what indicates the termination of the ranking process, this is
    // set either when the rank converges (new - old < epsilon) or false if
    // ranks stopped varying. or after a spesifice number of oiteration if
    // spesified.
    static bool unstable;

    Vertex<V, W> *self;         // the vertex we're ranking
    double r_old, r_new;        // old and new ranks

    Rank(Vertex<V, W> *v = nullptr, int n = 1)
        : self(v), r_old(1.0 / n), r_new(0.0) {}

    // fills `ranks` with all vertices from the `g`,
    static bool init(map<V, Vertex<V, W> *> g, int iterations = -1);

    // computes the random surfing factor for all vertices that has
    // no adjacent vertices
    static double randomJumpFactor();

    // rank all vertices in `ranks`
    static void rankPages();

    // calls update() for all vertices in `ranks`
    static void updateRanks();

    // replacing old rank with the new one
    void update();

    // compute the rank by summing all the old ranks of all vertices
    // that has self vertex as adjacent
    void update(double random_jump);
};

#endif
