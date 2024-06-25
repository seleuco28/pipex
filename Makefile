#SETUP
NAME		=	pipex
NAME_BONUS	=	pipex_bonus
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror
RM			=	rm -rf

#FILES AND PATH
HEADER_SRCS	=	pipex.h pipex_bonus.h
HEADER_DIR	=	include/
HEADER		=	$(addprefix $(HEADER_DIR), $(HEADER_SRCS))

MPATH_SRCS	=	pipex.c utils.c tube.c
MPATH_DIR	=	src/
MPATH		=	$(addprefix $(MPATH_DIR), $(MPATH_SRCS))
OBJ_M		=	$(MPATH:.c=.o)

BPATH_SRCS	=	pipex_bonus.c utils_bonus.c tube_bonus.c
BPATH_DIR	=	bonus/
BPATH		=	$(addprefix $(BPATH_DIR), $(BPATH_SRCS))
OBJ_B		=	$(BPATH:.c=.o)

FUNC_SRCS	=	ft_split.c ft_strjoin.c ft_strlcpy.c ft_strlen.c ft_strncmp.c
FUNC_DIR	=	functions/
FUNC 		=	$(addprefix $(FUNC_DIR), $(FUNC_SRCS))
OBJ_F		=	$(FUNC:.c=.o)

#COMMANDS
%.o: %.c $(HEADER) Makefile
				@${CC} ${FLAGS} -c $< -o $@

$(NAME):		$(OBJ_F) $(OBJ_M)
				@$(CC) $(OBJ_F) $(OBJ_M) -o $(NAME)
				@echo "$(GREEN)$(NAME) created!$(DEFAULT)"

$(NAME_BONUS):	$(OBJ_F) $(OBJ_B)
				@$(CC) $(OBJ_F) $(OBJ_B) -o $(NAME_BONUS)
				@echo "$(GREEN)$(NAME_BONUS) created!$(DEFAULT)"

all:			$(NAME)

bonus:			$(NAME_BONUS)

clean:
				@$(RM) $(OBJ_M)
				@$(RM) $(OBJ_F)
				@$(RM) $(OBJ_B)
				@echo "$(YELLOW)object files deleted!$(DEFAULT)" ##cambiarle la frase a esto

fclean:			clean
				@$(RM) $(NAME) $(NAME_BONUS)
				@echo "$(RED)all deleted!$(DEFAULT)" ##cambiarle la frase a esto

re:				fclean all

.PHONY:		all clean fclean bonus re

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m





