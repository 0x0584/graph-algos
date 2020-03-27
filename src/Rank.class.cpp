// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Rank.class.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/03/27 16:34:19 by archid-           #+#    #+#             //
//   Updated: 2020/03/27 16:49:22 by archid-          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Rank.class.hpp"

template<class V, class W> void Rank<V, W>::update() {
    r_old = r_new;
    r_new = 0.0;
}

template<class V, class W> void Rank<V, W>::update(double random_jump) {
    r_new = random_jump + (1 - decay_rate) / N;
    for (auto v : self->radj)
        r_new += (decay_rate * ranks[v.second].r_old)
            / v.second->adj.size();
    unstable &= abs(r_new - r_old) < epsilon;
}


template<class V, class W> bool Rank<V, W>::init(map<V, Vertex<V, W> *> g) {
    unstable = true;
    if (!(N = g.size()))
        return false;
    for (auto e : g)
        ranks[e.second] = {e.second, N};
    return true;
}

template<class V, class W> double Rank<V, W>::randomJumpFactor() {
    double rj = 0.0;

    for (auto pg : ranks)
        if (pg.first->adj.size() == 0)
            rj += decay_rate * (pg.second.r_old / N);
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
    unstable ^= true;
}

template<class T, class W> typename Rank<T, W>::RankMap Rank<T, W>::ranks = {};
template<class T, class W> const double Rank<T, W>::decay_rate = 0.85;
template<class T, class W> const double Rank<T, W>::epsilon = 1e-5;
template<class T, class W> bool Rank<T, W>::unstable = false;
template<class T, class W> int Rank<T, W>::N = 1;

template struct Rank<int, int>;
template struct Rank<char, int>;
template struct Rank<string, int>;
