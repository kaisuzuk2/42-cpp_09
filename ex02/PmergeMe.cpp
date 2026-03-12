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

unsigned long getTime() {
    timeval t;
    gettimeofday(&t, NULL);
    return (t.tv_sec * 1000000 + t.tv_usec);
}

size_t jacobsthal(size_t n) {
    if (n == 0)
        return (0);
    if (n == 1)
        return (1);
    return (jacobsthal(n - 1) + 2 * jacobsthal(n - 2));
}

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

    std::vector<int> large;
    for (size_t i = 0; i < pairs.size(); i++) {
        large.push_back(pairs[i].second);
    }
    sort(large);
    std::vector<int> mainChain = large;

    std::vector< std::pair<int, int> > pend;
    std::vector<int> pendLarge;
    std::vector<int> small;
    for (size_t i = 0; i < pairs.size(); i++) {
        pend.push_back(pairs[i]);
        pendLarge.push_back(pairs[i].second);
    }
    for (size_t i = 0; i < mainChain.size(); i++) {
        std::vector<int>::iterator pos = std::find(pendLarge.begin(), pendLarge.end(), mainChain[i]);
        int idx = pos - pendLarge.begin();
        int val = pend[idx].first;
        small.push_back(val);
    }

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

    for (size_t i = 0; i < small.size(); i++) {
        std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), std::find(mainChain.begin(), mainChain.end(), large[order[i]]), small[order[i]]);
        mainChain.insert(pos, small[order[i]]);
    }

    if (hasStraggler) {
        std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), straggler);
        mainChain.insert(pos, straggler);
    }
    v = mainChain;
}

std::list<std::pair<int, int> >::iterator getPairAt(
    std::list<std::pair<int, int> > &pairs, size_t index
) {
    std::list<std::pair<int, int> >::iterator it = pairs.begin();
    std::advance(it, index);
    return (it);
}

std::list<int>::iterator getIntAt(std::list<int> &lst, size_t idx) {
    std::list<int>::iterator it = lst.begin();
    while (idx > 0 && it != lst.end()) {
        it++;
        --idx;
    }
    return (it);
}

void sort(std::list<int> &l) {
    std::list<std::pair <int, int> > pairs;
    bool hasStraggler = false;
    int straggler = 0;

    if (l.size() <= 1)
        return ;
    
    std::list<int>::iterator it = l.begin();
    while (it != l.end()) {
        int a = *it;
        it++;
        if (it == l.end()) {
            hasStraggler = true;
            straggler = a;
            break;
        }
        int b = *it;
        it++;
        if (a > b)
            std::swap(a, b);
        pairs.push_back(std::make_pair(a, b));
    }

    std::list<int> large;
    for (std::list<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); it++) {
        large.push_back(it->second);
    }
    sort(large);

    std::list<int> mainChain = large;

    std::list< std::pair<int, int> > pend;
    std::list<int> pendLarge;
    std::list<int> small;
    for (std::list< std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); it++) {
        pend.push_back(*it);
        pendLarge.push_back(it->second);
    }   
    for (std::list<int>::iterator it = mainChain.begin(); it != mainChain.end(); it++) {
        std::list<int>::iterator pos = std::find(pendLarge.begin(), pendLarge.end(), *it);
        std::list< std::pair<int, int> >::iterator pit = pend.begin();
        std::list<int>::iterator lit = pendLarge.begin();
        while (lit != pos) {
            pit++;
            lit++;
        }
        small.push_back(pit->first);
    }

    std::vector<int> order;
    size_t k = 1;
    while (jacobsthal(k) < pairs.size()) {
        size_t j = jacobsthal(k);
        size_t prev = jacobsthal(k - 1);
        for (size_t idx = j; idx > prev; --idx)
            order.push_back(idx - 1);
        k++;
    }
    for (size_t i = order.size(); i < pairs.size(); i++) 
        order.push_back(i);

    for (size_t i = 0; i < order.size(); i++) {
        std::list<int>::iterator smallIt = getIntAt(small, order[i]);
        std::list<int>::iterator largeIt = getIntAt(large, order[i]);

        if (smallIt == small.end() || largeIt == large.end())
            continue ;
        std::list<int>::iterator bound = std::find(mainChain.begin(), mainChain.end(), *largeIt);
        std::list<int>::iterator pos = std::lower_bound(mainChain.begin(), bound, *smallIt);
        mainChain.insert(pos, *smallIt);
    }
    

    if (hasStraggler) {
        std::list<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), straggler);
        mainChain.insert(pos, straggler);
    }
    l = mainChain;
}



void PmergeMe(const int *arr, const size_t size) {
    std::vector <int> v(arr, arr + size);
    std::list<int> l(arr, arr + size);
    std::cout << "Before: ";
    printData(arr, arr + size);
    unsigned long vecStart = getTime();
    sort(v);
    unsigned long vecEnd = getTime();
    unsigned long listStart = getTime();
    sort(l);
    unsigned long listEnd = getTime();
    std::cout << "After: ";
    printData(v.begin(), v.end());
    printData(l.begin(), l.end());
    std::cout << "Time to process a range of " << size 
        <<  " elements with std::vector : " 
        << vecEnd - vecStart 
        <<" us" << std::endl;
    std::cout << "Time to process a range of " << size 
        <<  " elements with std::list : " 
        << listEnd - listStart 
        <<" us" << std::endl;

}
