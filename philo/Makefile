NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

INCLUDES = -I./includes

SRC_DIR = srcs
SRCS = $(SRC_DIR)/main.c \
	   $(SRC_DIR)/init.c \
	   $(SRC_DIR)/threads.c \
	   $(SRC_DIR)/utils.c \
	   $(SRC_DIR)/actions.c \
	   $(SRC_DIR)/monitor.c

OBJ_DIR = objs
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re