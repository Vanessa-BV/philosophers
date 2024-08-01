# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: vbusekru <vbusekru@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2024/05/17 14:50:07 by vbusekru      #+#    #+#                  #
#    Updated: 2024/08/01 10:18:42 by vbusekru      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=thread #-TSAN_OPTIONS=second_deadlock_stack=1

RM = rm -f

SOURCE =	1_main.c \
			2_input_check.c \
			3_init_data.c \
			4_mutexes_threads.c \
			5_actions.c \
			6_monitor.c \
			7_utils.c \
			8_print_messages.c \

OBJECTS = $(SOURCE:%.c=$(OBJS_DIR)/%.o)

OBJS_DIR = objects

all: $(NAME)
	
$(NAME): $(OBJS_DIR) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o:%.c 
	$(CC) $(CFLAGS) -c -o $@ $^

clean: 
	$(RM) -rf $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re