/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 09:58:31 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/03/14 08:29:09 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "BitcoinExchange.hpp"

int main(int argc, char *argv[]) {
	if (argc != 2 || !argv[1][0]) {
		std::cout << "Usage: ./btc [file]" << std::endl;
		return (1);
	}		
	try {
		BitcoinExchange btc;
		btc._run(argv[1]);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}