# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdiaz <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/15 19:22:08 by jdiaz             #+#    #+#              #
#    Updated: 2019/05/19 16:59:36 by jdiaz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

### PATH ###
SRCS_PATH = srcs/
OBJ_PATH  = obj/
LIBFT_PATH = libft/

FLAGS	= -Wall -Werror -Wextra
INC		= -I ./includes/ -I ./$(LIBFT_PATH)includes/

SRC		= srcs/main.c \
		  srcs/executer.c \
		  srcs/parser.c \
		  srcs/func_dispatcher.c \
		  srcs/built_in_commands.c \
		  srcs/env.c \
		  srcs/echo_built_in.c \
		  srcs/signals.c

OBJ 	= main.o \
		  executer.o \
		  parser.o \
		  func_dispatcher.o \
		  built_in_commands.o \
		  env.o \
		  echo_built_in.o \
		  signals.o

all: $(NAME)

$(NAME):
	@make -C $(LIBFT_PATH)
	@gcc $(FLAGS) $(INC) -c $(SRC)
	@gcc -o $(NAME) $(OBJ) -L $(LIBFT_PATH) -lft
	@echo "Compiled $(NAME)"

clean:
	@make -C $(LIBFT_PATH)/ clean
	@/bin/rm -rf $(OBJ)
	@echo "Cleaned $(OBJS_LIST)"

fclean: clean
	@make -C $(LIBFT_PATH)/ fclean
	@/bin/rm -rf $(NAME)
	@echo "Cleaned $(NAME)"

re: fclean all

.PHONY: all, clean, fclean, re
