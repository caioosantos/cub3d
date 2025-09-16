NAME = cub3D
NAME_BONUS = cub3D_bonus

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
INC_DIR_BONUS = -I include/ -I $(LIB_DIR) -D BONUS
OBJ_DIR = objs/
SRC_DIR = src/
COR_DIR = src/core/
INP_DIR = src/input/
MAT_DIR = src/math/
PAR_DIR = src/parse/
REN_DIR = src/render/
ULT_DIR = src/utils/

OBJ_DIR_BONUS = objs/bonus/
SRC_DIR_BONUS = src/bonus/
COR_DIR_BONUS = src/bonus/core_bonus/
DOO_DIR_BONUS = src/bonus/door_bonus/
INP_DIR_BONUS = src/bonus/input_bonus/
MAT_DIR_BONUS = src/bonus/math_bonus/
PAR_DIR_BONUS = src/bonus/parse_bonus/
REN_DIR_BONUS = src/bonus/render_bonus/
ULT_DIR_BONUS = src/bonus/utils_bonus/

SRC =	$(addprefix $(SRC_DIR), main.c) \
		$(addprefix $(COR_DIR), init.c) \
		$(addprefix $(INP_DIR), handler.c handler_utils.c) \
		$(addprefix $(MAT_DIR), vectors.c) \
		$(addprefix $(PAR_DIR), parse.c parse_colors.c parse_texture.c parse_map.c parse_player.c parse_utils.c set_start_position.c) \
		$(addprefix $(REN_DIR), render.c dda.c render_utils.c texture.c) \
		$(addprefix $(ULT_DIR), clean.c) \

OBJS = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# BONUS
SRC_BONUS = $(addprefix $(SRC_DIR_BONUS), main_bonus.c) \
			$(addprefix $(COR_DIR_BONUS), init_bonus.c) \
			$(addprefix $(DOO_DIR_BONUS), door_bonus.c) \
			$(addprefix $(INP_DIR_BONUS), handler_bonus.c handler_utils_bonus.c) \
			$(addprefix $(MAT_DIR_BONUS), vectors_bonus.c) \
			$(addprefix $(PAR_DIR_BONUS), parse_bonus.c parse_colors_bonus.c parse_texture_bonus.c parse_map_bonus.c parse_player_bonus.c parse_utils_bonus.c set_start_position_bonus.c) \
			$(addprefix $(REN_DIR_BONUS), render_bonus.c dda_bonus.c render_utils_bonus.c texture_bonus.c) \
			$(addprefix $(ULT_DIR_BONUS), clean_bonus.c)

OBJS_BONUS = $(SRC_BONUS:$(SRC_DIR_BONUS)%.c=$(OBJ_DIR_BONUS)%.o)

MLX = $(MLX_DIR)build/libmlx42.a

all: $(MLX) libft $(NAME)
	@printf "$(GREEN)Build completed successfully!$(END)\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

$(OBJ_DIR_BONUS)%.o: $(SRC_DIR_BONUS)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC_DIR_BONUS) -c $< -o $@

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

$(NAME_BONUS): $(OBJS_BONUS) $(MLX)
	@$(CC) $(CFLAGS) -no-pie $(OBJS_BONUS) -L$(LIB_DIR) -lft $(MLX) -o $(NAME_BONUS) $(MLX_FLAGS)
	@printf "$(GREEN)$(NAME_BONUS) compiled successfully!$(END)\n"

debug: $(NAME)
	valgrind ./$(NAME) maps/valide_maps/subject.cub

libft:
	@printf "$(YELLOW)Compiling libft...$(END)\n"
	@if $(MAKE) -q -C $(LIB_DIR); then \
		printf "$(GREEN)Libft is up to date!$(END)\n"; \
	else \
		make -C $(LIB_DIR) $(PRINT_DIR) && printf "$(GREEN)Libft compiled successfully!$(END)\n"; \
	fi

bonus: libft $(NAME_BONUS)
	@printf "$(GREEN)Build bonus completed successfully!$(END)\n"

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DIR_BONUS)
	@make -C $(LIB_DIR) fclean $(PRINT_DIR)

fclean: clean
	@printf "$(RED)Full cleaning...$(END)\n"
	@make -C $(LIB_DIR) fclean $(PRINT_DIR)
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@rm -rf $(MLX_DIR)build
	@printf "$(GREEN)Full clean completed!$(END)\n"

re: fclean all

valg:
	@valgrind --leak-check=full \
			--show-leak-kinds=all \
			--suppressions=suppress_mlx_error.supp \
			./$(NAME) maps/valid_maps/mandatory.cub

.PHONY: all clean fclean valg re bonus
