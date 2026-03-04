/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 08:52:30 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/03/04 10:21:58 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <fstream>
#include <exception>
#include <cmath>
#include <cstring>
#include <iostream>

class BitcoinExchange {
	private:
		std::map<std::string, double> _map;
		const static std::string kName;
		const static std::string kHeader;
		const static int kMaxVal = 1000;
		void _loadDatabase(const std::string &);
		
		void _executeLine(const std::string &) const;
		void _parseHeader(const std::string &) const;
		void _parseInput(const std::string &) const;

		std::string _strtrim(const std::string &) const;
		bool _splitByBar(const std::string &, std::string &, std::string &) const;
		bool _parseValue(const std::string &, double &) const;
		bool _parseDate(const std::string &) const;
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &);
		BitcoinExchange &operator=(const BitcoinExchange &);
		~BitcoinExchange();
		void _run(const std::string &filename) const;

		class InvalidHeaderException: public std::exception {
			const char *what() const throw();
		};
};


#endif