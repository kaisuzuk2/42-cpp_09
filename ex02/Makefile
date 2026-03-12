# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/07 13:55:03 by kaisuzuk          #+#    #+#              #
#    Updated: 2026/03/07 13:55:18 by kaisuzuk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	=	PmergeMe
CXX		=	c++
CXXFLAG	=	-Wall -Werror -Wextra -std=c++98

SRCS	=	main.cpp \
			PmergeMe.cpp
OBJS	=	$(SRCS:%.cpp=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(FLAG) -o $(NAME) $(OBJS)

%.o: %.cpp	
	$(CXX) $(FLAG) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re all