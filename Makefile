# Variables

NAME	= philo
HEADERS	= src/philo.h
SRC_DIR	= src/
OBJ_DIR	= obj/
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
RM		= rm -f

# Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

#Sources

SRC_FILES	= main init error_handling utils routine debugging

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

###

OBJF		= .cache_exists

all:		$(NAME)

$(NAME):	$(OBJ)
			@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
			@echo "$(GREEN)$(NAME) compiled!$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
			@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
			@$(CC) $(CFLAGS) -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)

clean:
			@$(RM) -rf $(OBJ_DIR)
			@echo "$(BLUE)$(NAME) object files succesfully cleaned!$(DEF_COLOR)"

fclean:		clean
			@$(RM) -f $(NAME)
			@echo "$(CYAN)$(NAME) executable files succesfully cleaned!$(DEF_COLOR)"

re:			fclean all
			@echo "$(GREEN)Everything was cleaned and the rebuilt for pipex!$(DEF_COLOR)"

norm:
			@norminette $(SRC) $(INCLUDE) $(LIBFT) $(FT_PRINTF) | grep -v Norme -B1 || true

.PHONY:		all clean fclean re norm
