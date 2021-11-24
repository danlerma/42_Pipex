# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/07 13:40:36 by dlerma-c          #+#    #+#              #
#    Updated: 2021/11/24 15:59:54 by dlerma-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c\
		ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c\
		ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c\
		ft_memset.c ft_strchr.c ft_strdup.c ft_strjoin.c\
		ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c\
		ft_strnstr.c ft_strrchr.c ft_substr.c ft_tolower.c\
		ft_toupper.c ft_strtrim.c ft_split.c ft_itoa.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_strmapi.c \
		ft_striteri.c ft_putendl_fd.c ft_putnbr_fd.c\
		ft_free_malloc.c ft_print_errors.c

OBJS = $(SRC:.c=.o)

SRCBONUS= ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstlast_bonus.c \
		ft_lstsize_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c

OBJSBONUS= $(SRCBONUS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -pedantic 

all: $(NAME)

$(NAME): $(OBJS) $(OBJSBONUS)
	@ar rcs $(NAME) $(OBJS) $(OBJSBONUS)
	@echo "\033[1;105mLibft done\033[0m"


%.o : %.c libft.h
	@gcc $(CFLAGS) -c $< -o $@

bonus: $(OBJSBONUS) libft.h
	@ar rcs $(NAME) $(OBJSBONUS)
	
run: all
	@tput setaf 199; echo "MAKEFILE OF LIBFT"
	@gcc $(CFLAGS) libft.a -g3 -o a.out  
	./a.out

run_bonus: bonus
	@tput setaf 191; echo "MAKEFILE OF LIBFT BONUS"
	@gcc $(CFLAGS) libft.a -g3 -o a.out  
	./a.out
	
normi:
	@norminette $(SRC) $(SRCBONUS) ./libft.h
	@tput setaf 208; echo "Norminette"

clean:
	@rm -f $(OBJS) $(OBJSBONUS)

fclean: clean
	@rm -f $(NAME)
	
re:	fclean all

PHONY.: clean all fclean re bonus
