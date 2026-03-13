# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/07 13:55:03 by kaisuzuk          #+#    #+#              #
#    Updated: 2026/03/14 05:36:05 by kaisuzuk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	=	PmergeMe
CXX		=	c++
CXXFLAG	=	-Wall -Werror -Wextra -std=c++98 -g -fsanitize=address

SRCS	=	main.cpp \
			PmergeMe.cpp
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