/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 08:52:34 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/02/28 11:03:30 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

const char *BitcoinExchange::kName = "data.csv";

BitcoinExchange::BitcoinExchange() {
	this->_loadDatabase(kName);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) {
	*this = other;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
	if (this != &other) 
		this->_map = other._map;
	return (*this);
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::_loadDatabase(const std::string &name) {
	std::string s;
	std::ifstream ifs(name.c_str());

	if (!ifs.is_open()) 
		throw std::runtime_error("Error: could not open database file");
	if (std::getline(std::cin, s))
	ifs.close();
}