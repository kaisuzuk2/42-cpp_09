/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 08:52:30 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/02/28 11:03:29 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <fstream>
#include <exception>
#include <iostream>

class BitcoinExchange {
	private:
		std::map<std::string, double> _map;
		const static char *kName;
		void _loadDatabase(const std::string &);
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &);
		BitcoinExchange &operator=(const BitcoinExchange &);
		~BitcoinExchange();
};


#endif