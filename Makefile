SOURCES_DIR = source/
SOURCES = $(SOURCES_DIR)main.c \
			$(SOURCES_DIR)input.c \
			$(SOURCES_DIR)ft_ping.c \
			$(SOURCES_DIR)signal.c \
			$(SOURCES_DIR)send.c \
			$(SOURCES_DIR)receive.c \
			$(SOURCES_DIR)utils.c \

BONUS_FILE = \

HEADER			=	includes/ft_ping.h
HEADER_BONUS	=	includes/ft_ping_bonus.h

BUILD_DIR		=	build/

OBJECTS			= 	$(patsubst $(SOURCES_DIR)%.c,$(BUILD_DIR)%.o,$(SOURCES))

OBJECTS_BONUS  	= 	$(patsubst $(SOURCES_DIR_BONUS)%.c,$(BUILD_DIR)%.o,$(SOURCES))


DEP				=	$(OBJECTS:%.o=%.d)

NAME			=	ft_ping

CC				=	gcc
RM				=	rm -rf

CFLAGS			=	-Wall -Wextra -Werror -g

LIBFT_PATH		=	./libft
LIBFT			=	$(LIBFT_PATH)/libft.a


_GREY	=	$'\e[30m
_RED	=	$'\e[31m
_GREEN	=	$'\e[32m
_YELLOW	=	$'\e[33m
_BLUE	=	$'\e[34m
_PURPLE	=	$'\e[35m
_CYAN	=	$'\e[36m
_WHITE	=	$'\e[37m


$(BUILD_DIR)%.o : $(SOURCES_DIR)%.c
					@echo "[$(NAME)] : Compiling Binary Files ...\t\t\t\c"
					@mkdir -p $(BUILD_DIR)
					@$(CC) $(CFLAGS) -MMD -c $< -o $@
					@echo "DONE"

all:				$(NAME)
-include $(DEP)

$(NAME):			$(LIBFT) $(OBJECTS) $(HEADER)
					@echo "[$(NAME)] : Creating $(NAME) ...\t\t\t\c"
					@$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(NAME)
					@echo "DONE"


bonus:				$(LIBFT) $(OBJECTS) $(OBJECTS_BONUS) $(HEADER_BONUS)
					@$(CC) $(CFLAGS) $(OBJECTS) $(OBJECTS_BONUS) $(LIBFT) -o $(NAME)

$(LIBFT):
					$(MAKE) -C $(LIBFT_PATH)


clean:
					@echo "[$(NAME)] : Deleting Objects Directory $(OBJECTS_DIR) ... \c"
					@$(MAKE) -C $(LIBFT_PATH) clean
					@$(RM) $(BUILD_DIR)/*.o
					@$(RM) $(BUILD_DIR)/*.d
					@echo "DONE\n-----"

fclean:				clean
					@echo "[$(NAME)] : Deleting Binary File ... \c"
					@$(MAKE) -C $(LIBFT_PATH) fclean
					@$(RM) $(NAME)
					@echo "DONE\n-----"

re:					fclean all


.PHONY:				all clean fclean re libft bonus