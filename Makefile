# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alvelazq <alvelazq@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/22 15:06:36 by alvelazq          #+#    #+#              #
#    Updated: 2024/06/18 14:00:56 by alvelazq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#GENERAL
NAME		=	pipex
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror
RM			=	rm -rf # 'r' -> para que sea recursivo 'f' -> para no preguntar al usuario e ignorar archivos inexistentes

#SUBCARPETAS
HEADER		=	pipex.h

SRC_SOURCES	=	pipex.c tube.c free.c
SRC_DIR	=	src/
SRC		=	$(addprefix $(SRC_DIR), $(SRC_SOURCES))
SRC_OBJ		=	$(SRC:.c=.o)

FUNCTIONS_SOURCES	=	ft_strncmp.c ft_split.c ft_strjoin.c ft_strlen.c ft_strlcpy.c
FUNCTIONS_DIR	=	functions/
FUNCTIONS		=	$(addprefix $(FUNCTIONS_DIR), $(FUNCTIONS_SOURCES))
FUNCTIONS_OBJ		=	$(FUNCTIONS:.c=.o)

#COMANDOS
%.o: %.c $(HEADER) Makefile
				@${CC} ${FLAGS} -c $< -o $@

$(NAME):		$(FUNCTIONS_OBJ) $(SRC_OBJ)
				@$(CC) $(FUNCTIONS_OBJ) $(SRC_OBJ) -o $(NAME)
				@echo "$(GREEN)$(NAME) creado!"

all:			$(NAME)

clean:
				@$(RM) $(SRC_OBJ)
				@$(RM) $(FUNCTIONS_OBJ)
				@echo "$(YELLOW)archivos *.o borrados"

fclean:			clean
				@$(RM) $(NAME)
				@echo "$(RED)todo borrado!"

re:				fclean all

.PHONY:		all clean fclean re

#COLORES
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m





