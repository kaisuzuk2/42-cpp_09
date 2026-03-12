// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   PmergeMe.cpp                                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2026/03/07 12:33:29 by kaisuzuk          #+#    #+#             */
// /*   Updated: 2026/03/11 16:18:10 by kaisuzuk         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "PmergeMe.hpp"

size_t jacobsthal(size_t n) {
    if (n == 0)
        return (0);
    if (n == 1)
        return (1);
    return (jacobsthal(n - 1) + 2 * jacobsthal(n - 2));
}

// bool cmpPair(const std::pair<int, int> &a, const std::pair<int, int> &b) {
//     return (a.second < b.second);
// }

void sort(std::vector<int> &v) {
    std::vector< std::pair<int, int> > pairs;
    bool hasStraggler = false;
    int straggler = 0;

    if (v.size() <= 1)
        return ;
    for (size_t i = 0; i + 1 < v.size(); i += 2) 
        pairs.push_back(std::make_pair(v[i], v[i + 1]));
    if (v.size() % 2 != 0) {
        hasStraggler = true;
        straggler = v[v.size() - 1];
    }

    for (size_t i = 0; i < pairs.size(); i++) {
        if (pairs[i].first > pairs[i].second) 
            std::swap(pairs[i].first, pairs[i].second);
    }

    std::vector<int> small;
    std::vector<int> large;
    for (size_t i = 0; i < pairs.size(); i++) {
        small.push_back(pairs[i].first);
        large.push_back(pairs[i].second);
    }
    sort(large);
    std::vector<int> mainChain = large;

    std::vector< std::pair<int, int> > pend;
    for (size_t i = 0; i < pairs.size(); i++)
        pend.push_back(pairs[i]);
    std::vector<int> order;
    size_t k = 1;
    while (jacobsthal(k) < pend.size()) {
        size_t j = jacobsthal(k);
        size_t prev = jacobsthal(k - 1);
        for (size_t idx = j; idx > prev; --idx) {
            size_t pos = idx - 1;
            order.push_back(pos);
        }
        k++;
    }
    for (size_t i = order.size(); i < pend.size(); i++)
        order.push_back(i);

    for (size_t i = 0; i < pend.size(); i++) {
        std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), std::find(mainChain.begin(), mainChain.end(), pend[order[i]].second), pend[order[i]].first);
        mainChain.insert(pos, pend[order[i]].first);
    }

    if (hasStraggler) {
        std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), straggler);
        mainChain.insert(pos, straggler);
    }
    v = mainChain;
}

// std::list<std::pair<int, int> >::iterator getPairAt(
//     std::list<std::pair<int, int> > &pairs, size_t index
// ) {
//     std::list<std::pair<int, int> >::iterator it = pairs.begin();
//     std::advance(it, index);
//     return (it);
// }

// void sort(std::list<int> &l) {
//     std::list<std::pair <int, int> > pairs;
//     bool hasStraggler = false;
//     int straggler = 0;

//     if (l.size() <= 1)
//         return ;
    
//     std::list<int>::iterator it = l.begin();
//     while (it != l.end()) {
//         int a = *it;
//         it++;
//         if (it == l.end()) {
//             hasStraggler = true;
//             straggler = a;
//             break;
//         }
//         int b = *it;
//         it++;
//         if (a > b)
//             std::swap(a, b);
//         pairs.push_back(std::make_pair(a, b));
//     }
//     pairs.sort(cmpPair);

//     std::list<int> large;
//     for (std::list<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); it++) {
//         large.push_back(it->second);
//     }
//     sort(large);

//     std::list<int> mainChain = large;

//     std::vector<int> order;
//     size_t k = 1;
//     while (jacobsthal(k) < pairs.size()) {
//         size_t j = jacobsthal(k);
//         size_t prev = jacobsthal(k - 1);
//         for (size_t idx = j; idx > prev; --idx)
//             order.push_back(idx - 1);
//         k++;
//     }
//     for (size_t i = order.size(); i < pairs.size(); i++) 
//         order.push_back(i);
//     for (size_t i = 0; i < order.size(); ++i) {
//         std::list<std::pair<int, int> >::iterator it = getPairAt(pairs, order[i]);
//         std::list<int>::iterator pos = std::lower_bound(mainChain.begin(), std::find(mainChain.begin(), mainChain.end(), it->second), it->first);
//         mainChain.insert(pos, it->first);
//     }
//     if (hasStraggler) {
//         std::list<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), straggler);
//         mainChain.insert(pos, straggler);
//     }
//     l = mainChain;
// }



void PmergeMe(const int *arr, const size_t size) {
    std::vector <int> v(arr, arr + size);
    std::list<int> l(arr, arr + size);
    std::cout << "Before: ";
    printData(arr, arr + size);
    sort(v);
    // sort(l);
    std::cout << "After: ";
    printData(v.begin(), v.end());
    // printData(l.begin(), l.end());
}
