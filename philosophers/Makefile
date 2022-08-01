#TARGET
NAME = philo

#DIRECTORIES
SRC_DIR = ./src/
OBJ_DIR = ./obj/
INC_DIR = ./include/

#FILES
SRC	=	philo.c \
		init_data.c \
		init_utils.c \
		utils.c \

OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)
HEADER = $(INC_DIR)philo.h

#FLAGS
#CFLAGS = -Wall -Wextra -Werror

#COMMANDS
CC = gcc
RM = rm -rf

.PHONY	: all clean fclean re

$(NAME)	:	$(OBJ)
		$(CC) -lpthread $(OBJ) -o $(NAME)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c $(HEADER)
		mkdir -p $(OBJ_DIR)
		$(CC) $(CFLAGS) -c $< -o $@

clean	:
		$(RM) $(OBJ_DIR)

fclean	:	clean
		$(RM) $(NAME)

re		:	fclean all