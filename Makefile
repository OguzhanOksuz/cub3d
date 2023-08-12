# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/26 16:15:07 by mkaraden          #+#    #+#              #
#    Updated: 2023/08/12 22:10:54 by ooksuz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



AR	= ar rcs
RM	= rm -f

CC		= gcc
CFLAGSA	= -I ./include/ -fsanitize=address
CFLAGS	= -I ./include/
CDEBUG	= -g 
FRMS	=	-framework OpenGL -framework AppKit



SRC_DIR	= src
OBJ_DIR	= obj
BIN_DIR	= bin

SRC =	main/main.c		main/hook.c		main/data_error_handler.c	main/init.c	 \
		parser/parse.c 	parser/string_utils.c parser/get_elements.c\
		parser/lexer.c	parser/ft_split.c\
		parser/debug.c\
		raycast/raycast.c	\
		raycast/raycast_calculate.c		raycast/raycast_draw.c	raycast/raycast_utils.c	\
		minimap/minimap.c
		
		

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

ARC = ./src/gnl/get_next_line.a mlx/libmlx.a


BIN		= cub3d
NAME	= $(BIN_DIR)/$(BIN)


all: $(NAME)

data: $(OBJ) | $(BIN_DIR)
	@cd ./$(SRC_DIR)/gnl && $(MAKE)
	@echo "Gnl is compiled."
	@cd ./mlx && $(MAKE)
	@$(CC) $(CFLAGSA) $(OBJ) $(ARC) $(FRMS) -o $(NAME)
	@echo "cub3d data is compiled."

$(NAME): $(OBJ) | $(BIN_DIR)
	@cd ./$(SRC_DIR)/gnl && $(MAKE)
	@echo "Gnl is compiled."
	@cd ./mlx && $(MAKE)
	@$(CC) $(CFLAGS) $(OBJ) $(ARC) $(FRMS) -o $(NAME)
	@echo "cub3d is compiled."


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC)  $(CFLAGS) $(CDEBUG) -c $< -o $@

run: all
	./$(NAME)

clean:
	rm -f $(OBJ)
	rm -f $(BOBJS)
	@cd ./$(SRC_DIR)/gnl && $(MAKE) clean
	@cd ./mlx && $(MAKE) clean
	@echo "Cleaned"

fclean: clean
	rm -f $(NAME)
	rm -f $(BNAME)
	@cd ./$(SRC_DIR)/gnl && $(MAKE) fclean
	@cd ./mlx && $(MAKE) clean
	@echo "Fully cleaned"
	

re: fclean
	@make all

.PHONY: all clean fclean run re
