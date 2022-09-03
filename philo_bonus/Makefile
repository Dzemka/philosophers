#TARGET
NAME = philo_bonus

#DIRECTORIES
SRC_DIR = ./src/
OBJ_DIR = ./obj/
INC_DIR = ./include/

#FILES
SRC	=	philo_bonus.c \
		init_data_bonus.c \
		init_utils_bonus.c \
		utils_bonus.c \

OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)
HEADER = $(INC_DIR)philo_bonus.h

#FLAGS
CFLAGS = -Wall -Wextra -Werror

#COMMANDS
CC = gcc
RM = rm -rf

.PHONY	:	all clean fclean re

all	:	$(NAME)

$(NAME)	:	$(OBJ)
		$(CC) -lpthread $(OBJ) -o $(NAME)

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c $(HEADER)
		mkdir -p $(OBJ_DIR)
		$(CC) $(CFLAGS) -c $< -o $@

clean	:
		$(RM) $(OBJ_DIR)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all