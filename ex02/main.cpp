/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 12:34:48 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/03/13 07:33:33 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int ft_stoi(char *str) {
    char *endptr;
    long res;

    res = std::strtol(str, &endptr, 10);
    if (errno || str == endptr || *endptr || 
        res > std::numeric_limits<int>::max() || \
        res < std::numeric_limits<int>::min()) 
        throw std::runtime_error("Error");
    return (res);
}

int main(int argc, char *argv[]) {
    if (argc <= 2) {
        std::cerr << "Usage: ./PmergeMe <num> <num> ..." << std::endl;
        return (EXIT_FAILURE);
    }
    size_t size = argc - 1;
    int arr[size];
    try {
        for (size_t i = 0; i < size; i++) {
            if ((arr[i] = ft_stoi(argv[i + 1])) <= 0)
                throw std::runtime_error("Error");
        }
        PmergeMe(arr, size);
        return (EXIT_SUCCESS);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return (EXIT_FAILURE);
    }
}