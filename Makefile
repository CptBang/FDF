# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mschroed <mschroed@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/21 15:47:13 by mschroed          #+#    #+#              #
#    Updated: 2019/10/29 16:46:25 by mschroed         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CCFLAGS = -Wall -Wextra -Werror -fsanitize=address
INCLUDES = -Iminilibx_macos -Ilibft/includes -I.
LIBS = -lmlx -lft
FRAMEWORKS = -framework OpenGl -framework AppKit
LIBFLAGS = -Lminilibx_macos -Llibft
LDFLAGS = $(LIBFLAGS) $(LIBS) $(FRAMEWORKS)  -fsanitize=address
SRCDIR = src
SRC = controller1.c draw.c fc3vector.c loop.c main.c vector.c
SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS = $(SRCS:.c=.o)
CFLAGS = $(CCFLAGS) $(INCLUDES) $(LDFLAGS)

all: $(NAME)

libft/libft.a:
	$(MAKE) -C libft all

minilibx_macos/libmlx.a:
	$(MAKE) -C minilibx_macos all

$(NAME): $(OBJS) libft/libft.a minilibx_macos/libmlx.a
	$(CC) $(CFLAGS) -o $@ $^

$(OBJS): CFLAGS = $(CCFLAGS) $(INCLUDES)

.PHONY: clean
clean:
	$(MAKE) -C libft clean
	$(MAKE) -C minilibx_macos clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C libft fclean
	$(MAKE) -C minilibx_macos fclean
	$(RM) $(NAME)

re: fclean all

# CFLAGS := -std=c11 -Wall -Wextra -Wshadow -pedantic -g -I minilibx_macos -I libft/includes -I. -fsanitize=address
# LDFLAGS := -framework OpenGl -framework AppKit -L minilibx_macos -l mlx -L libft -l ft -fsanitize=address
# name := fdf
# src := $(wildcard src/*.c)
# obj := $(src:.c=.o)

# $(name): $(obj)
# 	make -C libft
# 	$(CC) $(LDFLAGS) -o $@ $^

# .PHONY: all clean fclean re

# all: $(name)

# clean:
# 	$(RM) -f $(obj)

# fclean: clean
# 	$(RM) -f $(name)

# re: fclean all
