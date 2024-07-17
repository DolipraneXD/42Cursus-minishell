# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahsadik <ahsadik@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/04 13:15:07 by ahsadik           #+#    #+#              #
#    Updated: 2024/06/29 15:04:58 by ahsadik          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =  libft.a
MAND = 	ft_atoi.c\
		ft_bzero.c\
		ft_calloc.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_isprint.c\
		ft_itoa.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_memset.c\
		ft_putchar_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_putstr_fd.c\
		ft_strchr.c\
		ft_strdup.c\
		ft_striteri.c\
		ft_strjoin.c\
		ft_strlcat.c\
		ft_strlcpy.c\
		ft_strlen.c\
		ft_strmapi.c\
		ft_strncmp.c\
		ft_strnstr.c\
		ft_strrchr.c\
		ft_strtrim.c\
		ft_substr.c\
		ft_tolower.c\
		ft_toupper.c\
		ft_split.c\
		ft_lstnew_bonus.c\
		ft_lstadd_front_bonus.c\
		ft_lstsize_bonus.c\
		ft_lstlast_bonus.c\
		ft_lstadd_back_bonus.c\
		ft_lstdelone_bonus.c\
		ft_lstclear_bonus.c\
		ft_lstiter_bonus.c\
		ft_lstmap_bonus.c

CC = cc
FLAGS = -Wall -Wextra -Werror
OBJS = $(MAND:.c=.o)
BNS_OBJS = $(BONUS:bonus.c=bonus.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@ar rc $(NAME) $(OBJS)

%.o : %.c libft.h
	@$(CC) $(FLAGS) -c $< -o $@

bonus : $(BNS_OBJS)
	@ar rc $(NAME) $(BNS_OBJS)

clean:
	rm -rf $(OBJS) $(BNS_OBJS)

fclean:
	rm -rf $(OBJS) $(BNS_OBJS) $(NAME)

re: fclean all