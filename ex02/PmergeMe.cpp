/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 14:01:12 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/03/14 16:24:29 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int vecCount = 0;
int listCount = 0;

bool cmpNodeVec(Node *a, Node *b) {
    vecCount++;
    return (*a < *b);
}

bool cmpNodeList(Node *a, Node *b) {
    listCount++;
    return (*a < *b);   
}

std::vector<int> makeOrder(size_t size) {
    std::vector<int> order;
    size_t k = 1;
    while (jacobsthal(k) < size) {
        size_t j = jacobsthal(k);
        size_t prev = jacobsthal(k -1);
        for (size_t idx = j; idx > prev; --idx)
            order.push_back(idx - 1);
        k++;
    }
    for (size_t i = order.size(); i < size; i++) 
        order.push_back(i);
    return (order);
}

/************************************************************** */
//                     VECTOR
/************************************************************** */

void sortInternal(std::vector<Node *> &v) {
    std::vector<Node *> winners;
    bool hasStraggler = false;
    Node *straggler;
    std::vector<Node *> mainChain;
    
    if (v.size() <= 1)
        return ;
    for (size_t i = 0; i + 1 < v.size(); i += 2) {
        if (*v[i] < *v[i + 1]) {
            v[i + 1]->losers.push_back(v[i]);
            winners.push_back(v[i + 1]);
            vecCount++;
        } else {
            v[i]->losers.push_back(v[i + 1]);
            winners.push_back(v[i]);
            vecCount++;
        }
    }
    if (v.size() % 2 != 0) {
        hasStraggler = true;
        straggler = v.back();
    }

    sortInternal(winners);
    mainChain = winners;
    
    std::vector<int> order = makeOrder(winners.size());

    Node *toInsert = winners[0]->losers.back();
    mainChain.insert(mainChain.begin(), toInsert);
    winners[0]->losers.pop_back();
    
    for (size_t i = 1; i < winners.size(); i++) {
        Node *toInsert = NULL;
        if (!winners[order[i]]->losers.empty())
            toInsert = winners[order[i]]->losers.back();
        if (!toInsert)
            continue ;
        winners[order[i]]->losers.pop_back();
        std::vector<Node *>::iterator bound = mainChain.begin() + order[i] + i;
        std::vector<Node *>::iterator pos = std::lower_bound(mainChain.begin(), bound, toInsert, cmpNodeVec);
        mainChain.insert(pos, toInsert);
    }

    if (hasStraggler) {
        std::vector<Node *>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), straggler, cmpNodeVec);
        mainChain.insert(pos, straggler);
    }
    v = mainChain;
}

void sort(std::vector<int> &v) {
    std::vector<Node> nodes;
    std::vector<Node *>nodesPtr;
    std::vector<int> res;

    nodes.reserve(v.size());
    nodesPtr.reserve(v.size());

    for (size_t i = 0; i < v.size(); i++) 
        nodes.push_back(Node(v[i]));
    for (size_t i = 0; i < nodes.size(); i++) 
        nodesPtr.push_back(&nodes[i]);
    sortInternal(nodesPtr);
    for (size_t i = 0; i < nodesPtr.size(); i++) 
        res.push_back(nodesPtr[i]->value);
    v = res;
}

/************************************************************** */
//                     LIST
/************************************************************** */

void sortInternal(std::list<Node *> &l) {
    std::list<Node *> winners;
    bool hasStraggler = false;
    Node *straggler;
    std::list<Node *> mainChain;

    if (l.size() <= 1)
        return ;
    std::list<Node *>::iterator it = l.begin();
    while (it != l.end()) {
        Node *a = *it;
        it++;
        if (it == l.end()) {
            hasStraggler = true;
            straggler = a;
            break;
        }
        Node *b = *it;
        it++;
        if (*a < *b) {
            b->losers.push_back(a);
            winners.push_back(b);
            listCount++;
        } else {
            a->losers.push_back(b);
            winners.push_back(a);
            listCount++;
        }
    }
    sortInternal(winners);
    mainChain = winners;

    std::vector<int> order = makeOrder(winners.size());

    Node *toInsert = (*winners.begin())->losers.back();
    mainChain.insert(mainChain.begin(), toInsert);
    (*winners.begin())->losers.pop_back();

    for (size_t i = 1; i < winners.size(); i++) {
        std::list<Node *>::iterator winnerIt = winners.begin();
        std::advance(winnerIt, order[i]);
        if ((*winnerIt)->losers.empty())
            continue ;
        Node *toInsert = (*winnerIt)->losers.back();
        (*winnerIt)->losers.pop_back();
        std::list<Node *>::iterator bound = mainChain.begin();
        std::advance(bound, order[i] + i);
        std::list<Node *>::iterator pos = std::lower_bound(mainChain.begin(), bound, toInsert, cmpNodeList);
        mainChain.insert(pos, toInsert);
    }

    if (hasStraggler) {
        std::list<Node *>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), straggler, cmpNodeList);
        mainChain.insert(pos, straggler);
    }
    l = mainChain;
}

void sort(std::list<int> &l) {
    std::list<Node> nodes;
    std::list<Node *> nodesPtr;
    std::list<int> res;

    for (std::list<int>::iterator it = l.begin(); it != l.end(); it++) 
        nodes.push_back(*it);
    for (std::list<Node>::iterator it = nodes.begin(); it != nodes.end(); it++) 
        nodesPtr.push_back(&(*it));
    sortInternal(nodesPtr);
    for (std::list<Node *>::iterator it = nodesPtr.begin(); it != nodesPtr.end(); it++)    
        res.push_back((*it)->value);
    l = res;
}

void PmergeMe(const int *arr, const size_t size) {
    std::vector<int> v(arr, arr + size);
    std::list<int> l(arr, arr + size);
    std::cout << "Before: ";
    printData(arr, arr + size);
    unsigned long vecStart = getTime();
    sort(v);
    unsigned long vecEnd = getTime();
    unsigned long listStart = getTime();
    sort(l);
    unsigned long listEnd = getTime();
    std::cout << "After : ";
    printData(l.begin(), l.end());
    

    std::cout << "Time to process a range of " << size 
        <<  " elements with std::vector : " 
        << vecEnd - vecStart 
        <<" us" << std::endl;
    std::cout << "Time to process a range of " << size 
        <<  " elements with std::list   : " 
        << listEnd - listStart 
        <<" us" << std::endl;
    // std::cout << "vector count : " << vecCount << std::endl;
    // std::cout << "list   count : " << listCount << std::endl;
}

/*
4 3 2 1 

[4 3] [2 1]

[4 3] [2 1]

[4 2]

[4]

2 4
1 3

1 2 4 
    3
*/

// 0 1 1 3 5 