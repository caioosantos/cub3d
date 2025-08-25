NAME = cub3D

RED =		\033[1;31m
YELLOW =	\033[1;33m
GREEN =		\033[1;32m
END =		\033[0m
PRINT_DIR =	--no-print-directory

# FLAGS
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3
MLX_FLAGS = -ldl -lglfw -pthread -lm

#DIR
LIB_DIR = lib/libft/
MLX_DIR = lib/mlx_42/
INC_DIR = -I include/ -I $(LIB_DIR)
OBJ_DIR = objs/
SRC_DIR = src/
COR_DIR = src/core/
INP_DIR = src/input/
MAT_DIR = src/math/
PAR_DIR = src/parse/
REN_DIR = src/render/
ULT_DIR = src/utils/

SRC =	$(addprefix $(SRC_DIR), main.c) \
		$(addprefix $(COR_DIR), ) \
		$(addprefix $(INP_DIR), ) \
		$(addprefix $(MAT_DIR), ) \
		$(addprefix $(PAR_DIR), ) \
		$(addprefix $(REN_DIR), ) \
		$(addprefix $(ULT_DIR), ) \

OBJS = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

MLX = $(MLX_DIR)build/libmlx42.a

all: $(MLX) libft $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

$(MLX):
	@if cmake $(MLX_DIR) -B $(MLX_DIR)/build > /dev/null 2>&1 && make -C $(MLX_DIR)/build -j4 $(PRINT_DIR) > /dev/null 2>&1; then \
		printf "$(YELLOW)MLX compiled success!$(END)\n" "$(notdir $(<))"; \
	else \
		cmake $(MLX_DIR) -B $(MLX_DIR)/build > /dev/null 2>&1 && make -C $(MLX_DIR)/build -j4 --no-print-directory > /dev/null 2>&1; \
	fi

$(NAME): $(OBJS) $(MLX)
	@printf "$(GREEN)All compiled!!!$(END)\n" "$(notdir $(<))"
	@$(CC) $(CFLAGS) -no-pie $(OBJS) -L$(LIB_DIR) $(MLX) -o $(NAME) $(MLX_FLAGS)

libft:
	@printf "$(GREEN)Libft compiled success!$(END)\n" "$(notdir $(<))"
	@make -C $(LIB_DIR) $(PRINT_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIB_DIR) fclean $(PRINT_DIR)

fclean: clean
	@printf "$(RED)Cleaning...$(END)\n" "$(notdir $(<))"
	@make -C $(LIB_DIR) fclean $(PRINT_DIR)
	@rm -f $(NAME)
	@rm -rf $(MLX_DIR)build
	@printf "$(GREEN)Finish!$(END)\n" "$(notdir $(<))"

re: fclean all

valg:
	@valgrind --leak-check=full \
			--show-leak-kinds=all \
			--suppressions=suppress_mlx_error.supp \
			./$(NAME)

.PHONY: all clean fclean valg re
