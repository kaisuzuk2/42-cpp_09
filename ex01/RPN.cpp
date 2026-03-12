/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 07:49:51 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/03/12 11:11:59 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

static bool isOperator(const char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

static long int safe_add(long int a, long int b) {
    if (b > 0 && a > std::numeric_limits<long>::max() - b)
        throw std::runtime_error("Error: over flow");
    if (b < 0 && a < std::numeric_limits<long>::min() - b)
        throw std::runtime_error("Error: over flow");
    return (a + b);
}

static long int safe_sub(long int a, long int b) {
    if (b == std::numeric_limits<long>::min())
        throw std::runtime_error("Error: over flow");
    return (safe_add(a, -b));
}

static long int safe_div(long int a, long int b) {
    if (b == 0)
        throw std::runtime_error("Error");
    if (a == std::numeric_limits<long>::min() && b == -1)
        throw std::runtime_error("Error: over flow");
    return (a / b);
}

static long int safe_mul(long int a, long int b) {
    if (a == -1 && b == std::numeric_limits<long>::min())
        throw std::runtime_error("Error: over flow");
    if (b == -1 && a == std::numeric_limits<long>::min())
        throw std::runtime_error("Error: over flow");
    
    if (a > 0) {
        if (b > 0) {
            if (a > std::numeric_limits<long>::max() / b)
                throw std::runtime_error("Error: over flow");
        } else {
            if (b < std::numeric_limits<long>::min() / a)
                throw std::runtime_error("Error: over flow");
        }
    } else {
        if (b > 0) {
            if (a < std::numeric_limits<long>::min() / b)
                throw std::runtime_error("Error: over flow");
        } else {
            if (a < std::numeric_limits<long>::max() / b)
                throw std::runtime_error("Error: over flow");
        }
    }
    return (a * b);
}



static void calc(std::stack<long> &st, const char c) {
    long a;
    long b;
    long res;

    if (st.size() < 2)
        throw std::runtime_error("Error");
    b = st.top();
    st.pop();
    a = st.top();
    st.pop();

    if (c == '+') 
        res = safe_add(a, b);
    else if (c == '-')
        res = safe_sub(a, b);
    else if (c == '*')
        res = safe_mul(a, b);
    else {
        res = safe_div(a, b);
    }
    st.push(res);
}

long int rpn(const std::string &input) {
    std::stack<long> st;
    std::stringstream ss(input);
    std::string token;

    while (getline(ss, token, ' ')) {
        if (token.empty())
            continue ;
        else if (token.size() == 1 && std::isdigit(token[0])) 
            st.push(token[0] - '0');
        else if (token.size() == 1 && isOperator(token[0])) {
            calc(st, token[0]);
        } else 
            throw std::runtime_error("Error");
    }
    if (st.size() != 1)
        throw std::runtime_error("Error");
    return (st.top());
}