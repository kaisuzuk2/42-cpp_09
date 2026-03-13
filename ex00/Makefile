# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/04 10:20:20 by kaisuzuk          #+#    #+#              #
#    Updated: 2026/03/14 05:21:21 by kaisuzuk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	=	btc
CXX		=	c++
CXXFLAG	=	-Wall -Werror -Wextra -std=c++98

SRCS	=	main.cpp \
			BitcoinExchange.cpp
OBJS	=	$(SRCS:%.cpp=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAG) -o $(NAME) $(OBJS)

%.o: %.cpp	
	$(CXX) $(CXXFLAG) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all