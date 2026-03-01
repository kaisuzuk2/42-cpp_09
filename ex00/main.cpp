/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 09:58:31 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/03/01 13:41:07 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "BitcoinExchange.hpp"

int main(int argc, char *argv[]) {
	if (argc != 2 || !argv[1][0]) {
		std::cerr << "Usage: ./btc [file]" << std::endl;
		return (1);
	}		
	
}