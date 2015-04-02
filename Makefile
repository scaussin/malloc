# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/02/25 11:50:22 by scaussin          #+#    #+#              #
#    Updated: 2015/04/02 15:39:45 by scaussin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif


NAME =			libft_malloc_$(HOSTTYPE).so

CC =			gcc $(FLAGS) $(INCLUDES)

LINK =			libft_malloc.so

LIBFT =			-L./libft -lft

LIB =			./libft/libft.a

INCLUDES =		-I./includes -I./libft/includes

SRC =			src/main.c src/alloc.c src/dump_hexa.c src/manage_header.c \
				src/show_alloc.c src/tools.c

OBJ =			$(SRC:.c=.o)

FLAGS =			-Wall -Wextra -Werror

all:			$(LIB) $(NAME)

$(LIB):
				@echo "\033[32m[Make]\033[0m   " | tr -d '\n'
				@echo "\033[36m[libft]\033[0m Building libft... " | tr -d '\n'
				Make -C libft

$(NAME):		$(OBJ)
				@echo "\033[32m[Make]\033[0m   " | tr -d '\n'
				@echo "\033[36m[$(NAME)]\033[0m " | tr -d '\n'
				@echo "Building $(NAME)... " | tr -d '\n'
				$(CC) -shared -o $(NAME) $(OBJ) $(LIBFT)
				@echo "\033[32m   -> \033[0m" | tr -d '\n'
				@echo "\033[36m$(NAME) \033[0m\033[32mcreated\033[0m"
				@ln -s $(NAME) $(LINK)

clean:
				Make -C libft clean
				@echo "\033[31m[clean] " | tr -d '\n'
				@echo "\033[36m[$(NAME)]\033[0m Remove ofiles"
				rm -f $(OBJ)

fclean:
				Make -C libft fclean
				rm -f $(OBJ)
				rm -f $(NAME)
				rm -f $(LINK)
				@echo "\033[31m[fclean] \033[36m[$(NAME)]\033[0m" | tr -d '\n'
				@echo " Remove ofiles & $(NAME)"

run_fclean:
				rm -f $(OBJ)
				rm -f $(NAME)
				@echo "\033[31m[fclean] \033[36m[$(NAME)]\033[0m" | tr -d '\n'
				@echo " Remove ofiles & $(NAME)"

re:				fclean all

run:			run_fclean $(NAME)
				./$(NAME)


.PHONY:			all clean re fclean
.SILENT:

%.o:			%.c
				$(CC) -c $< -o $@
