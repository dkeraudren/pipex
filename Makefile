# Variables

NAME		=pipex

NAME_BONUS	=pipex_bonus

LIBFT_DIR	=libft/

LIBFT_FILE	=libft.a

LIBFT		=$(LIBFT_DIR)$(LIBFT_FILE)

SRC_DIR		=srcs/

OBJ_DIR		=objs/

INC_DIR		=includes/

INCS 		= $(LIBFT) includes/

CC = cc
CFLAGS = -Wall -Wextra -Werror
# CFLAGS = -Wall
RM = rm -rf

SRC_FILES = main\
			inits\
			parse\
			free\
			ft_execvp\
			pipex\


SRC_FILES_BONUS = main_bonus\
			inits\
			parse\
			free\
			ft_execvp\
			pipex_bonus\
			utils_bonus\

SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

SRCS_BONUS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES_BONUS)))
OBJS_BONUS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES_BONUS)))

all: $(NAME)

bonus: $(NAME_BONUS)

$(LIBFT):
	@make all -C $(LIBFT_DIR)

$(NAME):	$(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

$(NAME_BONUS):	$(OBJS_BONUS) $(LIBFT)
			$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJS_BONUS) $(LIBFT)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c $(INC_DIR)*.h | $(OBJ_DIR)
				$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@ -g3

$(OBJ_DIR):
			-mkdir -p $(OBJ_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re bonus