NAME	=	cub3d
BNAME	=	so_long_bonus

CC		=	gcc
CFLAGS	=	-fsanitize=address
FRMS	=	-framework OpenGL -framework AppKit

SRCS =	main.c raycastTxt.c

OBJS =	main.o raycastTxt.o

BSRCS = bonus/check_utils.c bonus/check_utils2.c \
		bonus/check.c bonus/draw_map.c \
		bonus/enemy.c bonus/enemy2.c \
		bonus/free_exit.c bonus/hook.c \
		bonus/hook2.c bonus/init.c \
		bonus/init2.c bonus/libftutils.c \
		bonus/main.c \

BOBJS	=	bonus/check_utils.o bonus/check_utils2.o \
			bonus/check.o bonus/draw_map.o \
			bonus/enemy.o bonus/enemy2.o \
			bonus/free_exit.o bonus/hook.o \
			bonus/hook2.o bonus/init.o \
			bonus/init2.o bonus/libftutils.o \
			bonus/main.o \

ARCS = gnl/get_next_line.a mlx/libmlx.a

all: $(NAME)

bonus: $(BNAME) 

$(BNAME): $(BOBJS)
	@cd ./gnl && $(MAKE)
	@echo "Gnl is compiled."
	@cd ./mlx && $(MAKE)
	@$(CC) $(CFLAGS) $(BOBJS) $(ARCS) $(FRMS) -o $(BNAME)
	@echo "So_long bonus is compiled."

$(NAME): $(OBJS)
	@cd ./gnl && $(MAKE)
	@echo "Gnl is compiled."
	@cd ./mlx && $(MAKE)
	@$(CC) $(CFLAGS) $(OBJS) $(ARCS) $(FRMS) -o $(NAME)
	@echo "cub3d is compiled."

clean:
	rm -f $(OBJS)
	rm -f $(BOBJS)
	@cd ./gnl && $(MAKE) clean
	@cd ./mlx && $(MAKE) clean
	@echo "Cleaned"

fclean: clean
	rm -f $(NAME)
	rm -f $(BNAME)
	@cd ./gnl && $(MAKE) fclean
	@cd ./mlx && $(MAKE) clean
	@echo "Fully cleaned"

re: fclean all

.PHONY: all clean fclean re bonus