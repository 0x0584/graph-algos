#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/20 21:31:38 by archid-           #+#    #+#              #
#    Updated: 2020/03/27 14:19:14 by archid-          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		= foo.out
ARGS		= tinyG.txt

RUN			= ./$(NAME) $(ARGS)

CC			= g++
CPPFLAGS	= -Wall -Wextra -g -Iinclude

OBJDIR		= .obj
SRCDIR		= src
DEPSDIR		= include

SRCS		= $(shell find $(SRCDIR) -name '*.cpp' -type f)
DEPS		= $(shell find $(DEPSDIR) -name '*.hpp' -type f)
OBJS		= $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS) $(DEPS)
	$(CC) $(CPPFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJDIR) $(NAME)

re: clean all

distcheck:
	@uname -a
	@echo
	@$(CC) --version
	@git --version

check: all
	@echo
	@ls -lR
	@echo
	@cat tinyG.txt
	@echo
	@$(RUN)

valg: all
	@echo
	@cppcheck -v --std=c++11 .
	@echo
	@valgrind --leak-check=full --show-leak-kinds=all --show-reachable=yes $(RUN)

.PHONY: all check re clean $(NAME)
