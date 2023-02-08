# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eralonso <eralonso@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/05 15:44:36 by eralonso          #+#    #+#              #
#    Updated: 2023/02/08 09:25:46 by eralonso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	gnl.a

PROGRAM		=	gnl

SDIR		=	./src/
ODIR		=	./obj/

HEADER		=	./inc

INCLUDE		=	-I${HEADER}

MK			=	Makefile

MAIN		=	main

SRCM		=	$(addprefix ${SDIR}, $(addsuffix .c, ${MAIN}))
OBJM		=	$(addprefix ${ODIR}, $(addsuffix .o, ${MAIN}))
DEPM		=	$(addsuffix .d, $(basename ${OBJM}))

FILES		=	get_next_line get_next_line_utils

SRC			=	$(addprefix ${SDIR}, $(addsuffix .c, ${FILES}))
OBJ			=	$(addprefix ${ODIR}, $(addsuffix .o, ${FILES}))
DEP			=	$(addsuffix .d, $(basename ${OBJ}))

BFILES		=	$(addsuffix _bonus, ${FILES})

SRCB		=	$(addprefix ${SDIR}, $(addsuffix .c, ${BFILES}))
OBJB		=	$(addprefix ${ODIR}, $(addsuffix .o, ${BFILES}))
DEPB		=	$(addsuffix .d, $(basename ${OBJB}))

CFLAGS		=	-Wall -Wextra -Werror -D BUFFER_SIZE=1000
AR			=	ar -src
RM			=	rm -rf
MKD			=	mkdir -p

${ODIR}%.o	:	${SDIR}%.c ${MK}
	@${MKD} $(dir $@)
	@${CC} -MT $@ ${CFLAGS} -MMD -MP ${INCLUDE} -c $< -o $@
	@printf "\033[1;33m          \rCompiling \033[1;35m$(notdir $<)...                              \r\033[0m"

all			:
	@$(MAKE) ${NAME}

bonus		:
	@$(MAKE) BONUS=1 all

ifndef BONUS

${NAME}		:: ${OBJ}
	@${AR} ${NAME} ${OBJ}

else

${NAME}		:: ${OBJB}
	@${AR} ${NAME} ${OBJB}

endif

${NAME}		::
	@echo ""
	@echo "\033[1;33mNothing to be done for 'gnl'\033[0m"

${PROGRAM}	:: ${OBJB} ${OBJM}
	@${CC} ${CFLAGS} ${OBJM} gnl.a -o $@
	@echo ""
	@echo "\033[1;33mProgram: \033[1;31m$@ \033[1;32mhas been compiled\033[0m"

clean		:
	@${RM} ${ODIR}
	@echo	"\033[1;31mObjects and dependencies have been removed\033[0m"

fclean		:
	@$(MAKE) clean
	@${RM} ${NAME} ${PROGRAM}
	@echo "\033[1;31mLibrary 'gnl' have been removed\033[0m"

re			:
	@$(MAKE) fclean
	@$(MAKE) all
	@echo "\033[1;96mLibrary have been restored\033[0m"

.PHONY: all clean fclean re

-include	${DEP}
-include	${DEPB}
