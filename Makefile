#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/20 21:31:38 by archid-           #+#    #+#              #
#    Updated: 2020/03/29 22:36:36 by archid-          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

DEBUG		?= 1

NAME		= foo.out
ARGS		= tinyG.txt

RUN			= ./$(NAME) $(ARGS)

CC			= g++
CPPFLAGS	= -Wall -Wextra -Iinclude -std=c++14

ifeq ($(DEBUG),1)
	CPPFLAGS += -g
else
	CPPFLAGS += -O2
endif

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
	@cat $(ARGS)
	@echo
	@$(RUN)

valg: all
	@echo
	@cppcheck -v --std=c++11 .
	@echo
	@valgrind --leak-check=full --show-leak-kinds=all --show-reachable=yes $(RUN)

.PHONY: all check re clean $(NAME)
