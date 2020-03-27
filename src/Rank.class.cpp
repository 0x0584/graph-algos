// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Rank.class.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/03/27 16:34:19 by archid-           #+#    #+#             //
//   Updated: 2020/03/27 17:53:56 by archid-          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Rank.class.hpp"

template<class V, class W>
bool Rank<V, W>::init(map<V, Vertex<V, W> *> g, int n_intrs) {
    unstable = true;
    n_iterations = n_intrs;
    if (!g.size()) return false;
    for (auto e : g)
        ranks[e.second] = {e.second, static_cast<int>(g.size())};
    return true;
}

template<class V, class W> double Rank<V, W>::randomJumpFactor() {
    double rj = 0.0;

    // technically, this is to balance the the ranking, since is a page
    // has no out-going edges, then we suppose the browsing came randomly
    // from outside, thus this value added up to the new rank of all vertices
    for (auto pg : ranks)
        if (pg.first->adj.size() == 0)
            rj += decay_rate * (pg.second.r_old / ranks.size());
    return rj;
}

template<class V, class W> void Rank<V, W>:: rankPages() {
    double rj = randomJumpFactor();

    for (auto pg = ranks.begin(); pg != ranks.end(); pg++)
        pg->second.update(rj);
}

template<class V, class W> void Rank<V, W>:: updateRanks() {
    for (auto pg = ranks.begin(); pg != ranks.end(); pg++)
        pg->second.update();
    if (n_iterations > 0) n_iterations--;
    else if (n_iterations == -1) unstable ^= true;
    else if (n_iterations == 0) unstable = false;
}

template<class V, class W> void Rank<V, W>::update() {
    r_old = r_new; r_new = 0.0;
}

template<class V, class W> void Rank<V, W>::update(double random_jump) {
    // all vertices are initialized with a sum of, the first value represent
    // the rank of a random jump between the links, due to no having in
    // out-going edges, the other value is to balance the probality distribution
    // after applying the decay factor
    r_new = random_jump + (1 - decay_rate) / ranks.size();

    // the rank (or probability) of a vertex is the sum of the probability
    // of all all vertices that have self as adjacent vertex, where the
    // probability of a single vertex u is as following:
    //
    //         decay_rate * u.old_rank / u.adjs.count()
    //
    // namely, the old rank over the number of out-going edges times the
    // decay factor
    for (auto v : self->radj)
        r_new += (decay_rate * ranks[v.second].r_old)
            / v.second->adj.size();

    // unless we have to apply a specific nyumber of iterations, we need to
    // keep going until the ranks converge
    if (n_iterations == -1)
        unstable &= abs(r_new - r_old) < epsilon;
}

template<class T, class W> typename Rank<T, W>::RankMap Rank<T, W>::ranks = {};

// 0.85 represent a percentage, as if 85% of the browsing is successful
template<class T, class W> const double Rank<T, W>::decay_rate = 0.85;

// a measure of convergence
template<class T, class W> const double Rank<T, W>::epsilon = 1e-5;
template<class T, class W> bool Rank<T, W>::unstable = false;
template<class T, class W> int Rank<T, W>::n_iterations = 0;

template struct Rank<int, int>;
template struct Rank<char, int>;
template struct Rank<string, int>;
