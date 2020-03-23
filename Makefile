#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/20 21:31:38 by archid-           #+#    #+#              #
#    Updated: 2020/03/23 09:04:05 by archid-          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		= foo.out
CC			= g++
CPPFLAGS	= -Wall -Wextra -g -Iinclude

OBJDIR		= .obj
SRCDIR		= src

SRCS		= $(shell find $(SRCDIR) -name '*.cpp' -type f)
OBJS		= $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CPPFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJDIR) $(NAME)

re: clean all

check:
	@make clean
	@ls -lR
	@echo
	@make re
	@echo
	@cat tinyG.txt
	@echo
	@./$(NAME) tinyG.txt

.PHONY: all re clean $(NAME)
