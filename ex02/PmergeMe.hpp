/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 12:33:27 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/03/17 08:55:38 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <exception>
#include <sys/time.h>
#include <cerrno>

struct Node {
    int value;
    std::vector<Node *> losers;

    Node(int v);
    bool operator<(const Node &other);
};

struct PendItem {
    Node *node;
    Node *boundWinner;

    PendItem(Node *n, Node *b);
};

void PmergeMe(const int *arr, const size_t size);

template <typename ConstIterator>
void printData(ConstIterator it, ConstIterator last) {
    while (it != last) {
        std::cout << *it;
        it++;
        if (it != last)
            std::cout << " ";
    }
    std::cout << std::endl;
}

#endif