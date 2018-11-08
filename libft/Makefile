# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/10/02 13:53:57 by thbrouss     #+#   ##    ##    #+#        #
#    Updated: 2018/11/06 16:59:06 by thbrouss    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all fclean clean re

CC=gcc

NAME=libft.a

FLAGS=-Wall -Werror -Wextra

INCLUDE=../includes/

FILE=ft_atoi\
ft_bzero\
ft_isalnum\
ft_isalpha\
ft_isascii\
ft_isdigit\
ft_isprint\
ft_itoa\
ft_lstadd\
ft_lstdel\
ft_lstdelone\
ft_lstiter\
ft_lstmap\
ft_lstnew\
ft_memalloc\
ft_memccpy\
ft_memchr\
ft_memcmp\
ft_memcpy\
ft_memdel\
ft_memmove\
ft_memset\
ft_putchar\
ft_putchar_fd\
ft_putendl\
ft_putendl_fd\
ft_putnbr\
ft_putnbr_fd\
ft_putstr\
ft_putstr_fd\
ft_strcat\
ft_strchr\
ft_strclr\
ft_strcmp\
ft_strcpy\
ft_strdel\
ft_strdup\
ft_strequ\
ft_striter\
ft_striteri\
ft_strjoin\
ft_strlcat\
ft_strlen\
ft_strmap\
ft_strmapi\
ft_strncat\
ft_strncmp\
ft_strncpy\
ft_strnequ\
ft_strnew\
ft_strnstr\
ft_strrchr\
ft_strsplit\
ft_strstr\
ft_strsub\
ft_strtrim\
ft_tolower\
ft_toupper\
ft_realloc\
ft_strcount\
ft_strrev

SRC=$(addsuffix .c, $(FILE))

OBJ=$(addsuffix .o, $(FILE))

all: $(NAME)

$(NAME): $(OBJ)
		@ar rcs $(NAME) $(OBJ)

%.o: %.c ../includes/libft.h
		@$(CC) $(FLAGS) -o $@ -c $< -I $(INCLUDE)

clean:
		@rm -f $(OBJ)
fclean: clean
		@rm -f $(NAME)

re:	fclean all
