# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eralonso <eralonso@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/05 15:44:36 by eralonso          #+#    #+#              #
#    Updated: 2022/11/05 16:02:36 by eralonso         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	gnl.a

ODIR	=	obj/

HEADER	=	./

INCLUDE	=	-I${HEADER}

MK		=	Makefile

FILES	=	get_next_line get_next_line_utils

SRC		=	$(addsuffix .c, ${FILES})
OBJ		=	$(addprefix ${ODIR}, $(addsuffix .o, ${FILES}))
DEP		=	$(addsuffix .d, $(basename ${OBJ}))

CFLAGS	=	-Wall -Wextra -Werror -D BUFFER_SIZE=10
AR		=	ar -src
RM		=	rm -rf
MKD		=	mkdir -p

${ODIR}%.o	:	%.c ${MK}
	@${MKD} $(dir $@)
	@${CC} -MT $@ ${CFLAGS} -MMD -MP ${INCLUDE} -c $< -o $@
	@echo "\033[1;33mCompiling $< ...\033[0m"

all			:
	@$(MAKE) ${NAME}

${NAME}		:: ${OBJ}
	@${AR} ${NAME} ${OBJ}

${NAME}		::
	@echo "\033[1;33mNothing to be done for 'gnl'\033[0m"

-include	${DEP}

clean		:
	@${RM} ${ODIR} ./a.out
	@echo	"\033[1;31mObjects and dependences have been removed\033[0m"

fclean		:
	@$(MAKE) clean
	@${RM} ${NAME}
	@echo "\033[1;31mLibrary 'gnl' have been removed\033[0m"

re			:
	@$(MAKE) fclean
	@$(MAKE) all
	@echo "\033[1;35mLibrary have been restored\033[0m"

.PHONY: all clean fclean re
