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

SRC =	$(addprefix $(SRC_DIR), main.c init.c) \
		$(addprefix $(COR_DIR), ) \
		$(addprefix $(INP_DIR), ) \
		$(addprefix $(MAT_DIR), vectors.c) \
		$(addprefix $(PAR_DIR), parse.c) \
		$(addprefix $(REN_DIR), render.c) \
		$(addprefix $(ULT_DIR), clean.c) \

OBJS = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

MLX = $(MLX_DIR)build/libmlx42.a

all: $(MLX) libft $(NAME)
	@printf "$(GREEN)Build completed successfully!$(END)\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

$(MLX):
	@printf "$(YELLOW)Compiling MLX42...$(END)\n"
	@if cmake $(MLX_DIR) -B $(MLX_DIR)/build > /dev/null 2>&1 && make -C $(MLX_DIR)/build -j4 $(PRINT_DIR) > /dev/null 2>&1; then \
		printf "$(GREEN)MLX42 compiled successfully!$(END)\n"; \
	else \
		printf "$(RED)Failed to compile MLX42$(END)\n"; \
		cmake $(MLX_DIR) -B $(MLX_DIR)/build > /dev/null 2>&1 && make -C $(MLX_DIR)/build -j4 --no-print-directory > /dev/null 2>&1; \
	fi

$(NAME): $(OBJS) $(MLX)
	@$(CC) $(CFLAGS) -no-pie $(OBJS) -L$(LIB_DIR) -lft $(MLX) -o $(NAME) $(MLX_FLAGS)
	@printf "$(GREEN)$(NAME) compiled successfully!$(END)\n"

libft:
	@printf "$(YELLOW)Compiling libft...$(END)\n"
	@if $(MAKE) -q -C $(LIB_DIR); then \
		printf "$(GREEN)Libft is up to date!$(END)\n"; \
	else \
		make -C $(LIB_DIR) $(PRINT_DIR) && printf "$(GREEN)Libft compiled successfully!$(END)\n"; \
	fi

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIB_DIR) fclean $(PRINT_DIR)

fclean: clean
	@printf "$(RED)Full cleaning...$(END)\n"
	@make -C $(LIB_DIR) fclean $(PRINT_DIR)
	@rm -f $(NAME)
	@rm -rf $(MLX_DIR)build
	@printf "$(GREEN)Full clean completed!$(END)\n"

re: fclean all

valg:
	@valgrind --leak-check=full \
			--show-leak-kinds=all \
			--suppressions=suppress_mlx_error.supp \
			./$(NAME)

.PHONY: all clean fclean valg re
