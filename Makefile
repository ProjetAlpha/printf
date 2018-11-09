# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/10/24 17:57:21 by thbrouss     #+#   ##    ##    #+#        #
#    Updated: 2018/11/08 23:44:21 by thbrouss    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = libftprintf.a
OUT = ft_test
MAKE = make
CC = gcc
FLAGS = -Wall -Wextra -Werror
INCLUDE = ./includes

#------------------------------------FILE--------------------------------------#

FILES=parse_args\

#----------------------------------SOURCE--------------------------------------#

SRC = $(addsuffix .c, $(FILES))
#SRC += libft/*.c

#----------------------------------OBJECT--------------------------------------#

OBJ= $(addsuffix .o, $(FILES))
OBJ += libft/*.o

#-----------------------------------RULE---------------------------------------#

all: $(NAME)

$(NAME): $(OBJ) ./includes/printf.h
		@ar rcs $@ $^

%.o: %.c ./includes/printf.h
	@$(CC) $(FLAGS) -o $@ -c $< -I $(INCLUDE)


%libft/.o: %libft/.c ./includes/libft.h
	@$(CC) $(FLAGS) -o $@ -c $< -I $(INCLUDE)

clean:
	@echo "\033[1m|---------------------------------|\033[0m"
	@echo "\033[1m|-------Supprimer les OBJECT------|\033[0m"
	@echo "\033[1m|---------------------------------|\033[0m"
	@+$(MAKE) -C libft/ clean
	@rm -f $(OBJ)

test:
	@echo "\033[1m|---------------------------------|\033[0m"
	@echo "\033[1m|-------Compilation du prog-------|\033[0m"
	@echo "\033[1m|---------------------------------|\033[0m"
	@echo "\033[1m|---------------------------------|\033[0m"
	@echo "\033[1m|---------Creation du prog--------|\033[0m"
	@echo "\033[1m|---------------------------------|\033[0m"
	@$(CC) $(FLAGS) -g -o $(OUT) $(SRC) -I$(INCLUDE) -L. -lftprintf

fclean: clean
	@echo "\n"
	@echo "\033[1m|---------------------------------|\033[0m"
	@echo "\033[1m|-------Supprimer la libftprintf.a------|\033[0m"
	@echo "\033[1m|---------------------------------|\033[0m"
	@rm -f $(NAME)
	@rm -f libft/libft.a

re: fclean all
