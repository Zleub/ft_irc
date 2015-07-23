# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adebray <adebray@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/10/02 03:26:29 by adebray           #+#    #+#              #
#    Updated: 2015/07/23 02:32:00 by adebray          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	ft_irc
SERV			=	serveur
CLI				=	client
HEADDIR			=	inc
HEADFLAG		=	-I ./$(HEADDIR)

SRCDIR			=	src
SERV_SRC		=	$(addprefix src/server/, $(shell ls src/server | grep ".c"))
CLI_SRC			=	$(addprefix src/client/, $(shell ls src/client | grep ".c"))

SERV_OBJ		=	$(subst .c,.o,$(SERV_SRC))
CLI_OBJ			=	$(subst .c,.o,$(CLI_SRC))

CC				=	clang
export CCFLAGS	=	-Werror -Wall -Wextra -Wuninitialized -Wpedantic -g

LIBLIBFT		=	-L$(SRCDIR)/libft -lft
LIBESSENTIAL	=	$(LIBLIBFT)

.PHONY: all clean fclean re $(NAME) asm

all: _depend $(SERV) $(CLI)

$(SERV): $(SERV_OBJ)
	@$(CC) $(CCFLAGS) $(HEADFLAG) $(LIBESSENTIAL) -o $(SERV) $(SERV_OBJ)
	@echo '!'
	@echo "\033[32m•\033[0m $(SERV) compil: \033[32m$(SERV)\033[0m"

$(CLI): $(CLI_OBJ)
	@$(CC) $(CCFLAGS) $(HEADFLAG) $(LIBESSENTIAL) -o $(CLI) $(CLI_OBJ)
	@echo '!'
	@echo "\033[32m•\033[0m $(CLI) compil: \033[32m$(CLI)\033[0m"

_depend: _libft

_libft: $(HEADDIR)/libft.h
	@make -C $(SRCDIR)/libft

%.o: %.c
	@echo '.''\c'
	@$(CC) $(CCFLAGS) $(HEADFLAG) -o $@ -c $<

clean:
	@make -C $(SRCDIR)/libft clean
	@rm -f $(SERV_OBJ)
	@rm -f $(CLI_OBJ)
	@echo "\033[31m•\033[0m clean: \033[31m$(SERV_OBJ) $(CLI_OBJ)\033[0m"

fclean:
	@make -C $(SRCDIR)/libft fclean
	@rm -f $(SERV_OBJ)
	@rm -f $(CLI_OBJ)
	@echo "\033[31m•\033[0m clean: \033[31m$(SERV_OBJ) $(CLI_OBJ)\033[0m"
	@rm -f $(SERV) $(CLI)
	@echo "\033[31m•\033[0m $(SERV) $(CLI) fclean: \033[31m$(SERV) $(CLI)\033[0m"

re: fclean all
