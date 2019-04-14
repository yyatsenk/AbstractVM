# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/14 17:42:20 by yyatsenk          #+#    #+#              #
#    Updated: 2019/04/14 17:42:26 by yyatsenk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = avm

SRCS := main.cpp 
SRCS +=	myexcept.cpp 

FLAGS =  -Wall -Werror -Wextra 

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@g++ -o $(NAME) -std=c++11 $(FLAGS) *.cpp
	@echo "\033[0;32mAbstractVM done!\033[0m"

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)

re: fclean all