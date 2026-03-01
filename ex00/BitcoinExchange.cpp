/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 08:52:34 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/03/01 14:21:59 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

const std::string BitcoinExchange::kName = "data.csv";
const std::string BitcoinExchange::kHeader = "date | value";

BitcoinExchange::BitcoinExchange() {
	this->_loadDatabase(kName); // ### TODO: 例外処理
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

const char *BitcoinExchange::InvalidHeaderException::what() const throw() {
	return ("Error: bad header.");
}

void BitcoinExchange::_loadDatabase(const std::string &name) {
	std::string s;
	std::ifstream ifs(name);

	if (!ifs.is_open()) 
		throw std::runtime_error("Error: could not open database file.");
	std::getline(ifs, s);
	while (std::getline(ifs, s)) {
		std::string::size_type pos = s.find(",");
		this->_map[s.substr(0, pos)] = std::strtod(s.substr(pos + 1).c_str(), NULL);
	}
	ifs.close();
}

void BitcoinExchange::_parseHeader(const std::string &header) const {
	if (header != this->kHeader)
		throw BitcoinExchange::InvalidHeaderException();
}

std::string BitcoinExchange::_strtrim(const std::string &input) const {
	size_t start = 0;
	size_t end = input.size();

	while (start < end && std::isspace(input[start]))
		start++;
	while (end > start && std::isspace(input[end - 1]))
		end--;
	return (input.substr(start, end - start));
}

bool BitcoinExchange::_splitByBar(const std::string &input, std::string &left, std::string &right) const {
	size_t bar = input.find('|');
	if (bar == std::string::npos)
		return (false);
	if (input.find('|', bar + 1) != std::string::npos)
		return (false);
	left = this->_strtrim(input.substr(0, bar));
	right = this->_strtrim(input.substr(bar + 1));
	if (left.empty() || right.empty())
		return (false);
	return (true);
}

bool BitcoinExchange::_parseValue(const std::string &s, double &out) const {
	char *endptr;

	out = std::strtod(s.c_str(), &endptr);
	if (endptr == s.c_str() || endptr != '\0' || std::isnan(out)) {
		std::cerr << "Error: not a number." << std::endl;
		return (false);
	}
	if (out < 0) {
		std::cerr << "Error: not a positive number." << std::endl;
		return (false);
	}
	if (out > kMaxVal) {
		std::cerr << "Error: too large a number." << std::endl;
		return (false);
	}
	return (true);
}

bool BitcoinExchange::_parseDate(const std::string &input) const {
	if (input.size() != 10) {
		std::cerr << "Error: bad input => " << input << std::endl;
		return (false);
	}
	if (input[4] != '-' || input[7] != '-') {
		std::cerr << "Error: bad input => " << input << std::endl;
		return (false);
	}
	for (int i = 0; i < input.size(); i++) {
		if (!std::isdigit(input[i]) && (i != 4 || i != 7)) {
			std::cerr << "Error: bad input => " << input << std::endl;
			return (false);
		}
	}
	
}

void BitcoinExchange::_executeLine(const std::string &input) const {
	std::string date;
	std::string val_str;
	double val;
	std::string trim_input;

	trim_input = this->_strtrim(input);
	if (trim_input.empty())
		return ;
	if (!this->_splitByBar(trim_input, date, val_str)) {
		std::cerr << "Error: bad input => " << input << std::endl;
		return ;
	}
	if (!this->_parseValue(val_str, val))
		return ;
	
	
}

void BitcoinExchange::_run(const std::string &filename) const {
	std::string s;

	std::ifstream ifs(filename);
	if (!ifs.is_open())
		throw std::runtime_error("Error: could not open user file.");
	
	std::getline(ifs, s);
	this->_parseHeader(s);
	
	while (std::getline(ifs, s)) {
		this->_executeLine(s);
	}
	ifs.close();
}