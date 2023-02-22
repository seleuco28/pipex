# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alvelazq <alvelazq@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/22 15:06:36 by alvelazq          #+#    #+#              #
#    Updated: 2023/02/22 12:36:08 by alvelazq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#GENERAL
NAME		=	pipex
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror
RM			=	rm -rf # 'r' -> para que sea recursivo 'f' -> para no preguntar al usuario e ignorar archivos inexistentes

#SUBCARPETAS
HEADER		=	pipex.h

PROGRAMA_SOURCES	=	pipex.c tube.c free.c
PROGRAMA_DIR	=	programa/
PROGRAMA		=	$(addprefix $(PROGRAMA_DIR), $(PROGRAMA_SOURCES))
PROGRAMA_OBJ		=	$(PROGRAMA:.c=.o)

FUNCIONES_SOURCES	=	ft_strncmp.c ft_split.c ft_strjoin.c ft_strlen.c ft_strlcpy.c
FUNCIONES_DIR	=	funciones/
FUNCIONES 		=	$(addprefix $(FUNCIONES_DIR), $(FUNCIONES_SOURCES))
FUNCIONES_OBJ		=	$(FUNCIONES:.c=.o)

#COMANDOS
%.o: %.c $(HEADER) Makefile
				@${CC} ${FLAGS} -c $< -o $@

$(NAME):		$(FUNCIONES_OBJ) $(PROGRAMA_OBJ)
				@$(CC) $(FUNCIONES_OBJ) $(PROGRAMA_OBJ) -o $(NAME)
				@echo "$(GREEN)$(NAME) creado!"

all:			$(NAME)

clean:
				@$(RM) $(PROGRAMA_OBJ)
				@$(RM) $(FUNCIONES_OBJ)
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





