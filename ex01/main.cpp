/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 09:19:40 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/03/12 10:31:42 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

// long_max 6 9 * 7 + 9 * 4 + 9 * 0 + 9 * 4 + 9 * 2 + 9 * 8 + 9 * 3 + 9 * 1 + 9 * 7 + 9 * 2 + 9 * 1 + 9 * 0 + 9 * 7 + 9 * 8 + 9 * 1 + 9 * 1 + 9 * 8 + 9 * 2 + 9 * 7 +
// long min 6 9 * 7 + 9 * 4 + 9 * 0 + 9 * 4 + 9 * 2 + 9 * 8 + 9 * 3 + 9 * 1 + 9 * 7 + 9 * 2 + 9 * 1 + 9 * 0 + 9 * 7 + 9 * 8 + 9 * 1 + 9 * 1 + 9 * 8 + 9 * 2 + 9 * 7 + 0 1 - * 1 -

void header(int id, const std::string &title) {
    std::cout << "========== " << id << ") " << title << " ==========" << std::endl;
}

void testSec(const std::string &input) {
    long int res;
    try {
        res = rpn(input);
        std::cout << "res = " <<  res << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void printInput(const std::string &input) {
    std::cout << "input = " << input << std::endl;
}

void test() {
    std::string input;
    long int res;
    {
        header(0, "PDF");
        input = "8 9 * 9 - 9 - 9 - 4 - 1 +";
        printInput(input);
        testSec(input);

        input = "7 7 * 7 -";
        printInput(input);
        testSec(input);
        
        input = "1 2 * 2 / 2 * 2 4 - +";
        printInput(input);
        testSec(input);

        input = "(1 + 1)";
        printInput(input);
        testSec(input);
    }

    {
        header(1, "no space(Error)");
        input = "11+";
        printInput(input);
        testSec(input);
        
        input = "11 +";
        printInput(input);
        testSec(input);

        input = "1 1+";
        printInput(input);
        testSec(input);
    }  

    {
        header(2, "many space");
        input = "1       1       +";
        printInput(input);
        testSec(input);

        input = "          1 1 +";
        printInput(input);
        testSec(input);

        input = "1      1 +         ";
        printInput(input);
        testSec(input);
    }

    {
        header(3, "zero div");
        input = "1 1 + 0 /";
        printInput(input);
        testSec(input);
    }

    {
        header(4, "over flow");
        std::cout << "LONG_MAX : ";
        input = "6 9 * 7 + 9 * 4 + 9 * 0 + 9 * 4 + 9 * 2 + 9 * 8 + 9 * 3 + 9 * 1 + 9 * 7 + 9 * 2 + 9 * 1 + 9 * 0 + 9 * 7 + 9 * 8 + 9 * 1 + 9 * 1 + 9 * 8 + 9 * 2 + 9 * 7 +";
        printInput(input);
        testSec(input);

        std::cout << "LONG_MAX + 1 : ";
        input = "6 9 * 7 + 9 * 4 + 9 * 0 + 9 * 4 + 9 * 2 + 9 * 8 + 9 * 3 + 9 * 1 + 9 * 7 + 9 * 2 + 9 * 1 + 9 * 0 + 9 * 7 + 9 * 8 + 9 * 1 + 9 * 1 + 9 * 8 + 9 * 2 + 9 * 7 + 1 +";
        printInput(input);
        testSec(input);

        std::cout << "LONG_MIN : ";
        input = "6 9 * 7 + 9 * 4 + 9 * 0 + 9 * 4 + 9 * 2 + 9 * 8 + 9 * 3 + 9 * 1 + 9 * 7 + 9 * 2 + 9 * 1 + 9 * 0 + 9 * 7 + 9 * 8 + 9 * 1 + 9 * 1 + 9 * 8 + 9 * 2 + 9 * 7 + 0 1 - * 1 -";
        printInput(input);
        testSec(input);

        std::cout << "LONG_MIN * -1 : ";
        input = "6 9 * 7 + 9 * 4 + 9 * 0 + 9 * 4 + 9 * 2 + 9 * 8 + 9 * 3 + 9 * 1 + 9 * 7 + 9 * 2 + 9 * 1 + 9 * 0 + 9 * 7 + 9 * 8 + 9 * 1 + 9 * 1 + 9 * 8 + 9 * 2 + 9 * 7 + 0 1 - * 1 - 0 1 - *";
        printInput(input);
        testSec(input);
    }
}

int main(int argc, char *argv[]) {
    std::string expr;
    long int res;

    if (argc != 2 || !argv[1][0]) {
        std::cerr << "Usage: ./RPN <expr>" << std::endl;
        std::cerr << "Test: ./RPN test" << std::endl;
        return (1);
    }
    expr = argv[1];
    if (expr == "test") {
        test();
        return (0);
    }
    try {
        res = rpn(expr);
        std::cout << res << std::endl;    
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}