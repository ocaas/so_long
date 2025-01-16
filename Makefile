CC = cc

NAME = so_long.a

SRC = 

MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	
%.o: %.c
	@echo "Compiling..." $<
	@$(CC) $(MLX_FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "OBJ CLEANED!"
fclean:
	@rm -f $(OBJ) $(NAME)
	@echo "ALL CLEANED!"

re: fclean all

.PHONY: all clean fclean re