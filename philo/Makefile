# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/12 22:36:36 by mbachar           #+#    #+#              #
#    Updated: 2023/06/23 01:52:21 by mbachar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PHILO 		= 	philo

CFLAGS		=	-Wall -Wextra -Werror

INC 		= 	philo.h

CC			=	cc

MAN_SRC 	= 	main.c \
				philo.c \
				parsing.c \
				tools.c \
				tools2.c \
				tools3.c

MAN_OBJ		=	$(MAN_SRC:.c=.o)

all: $(PHILO)

%.o : %.c $(INC)
	@ $(CC) $(CFLAGS) -c $< -o $@

$(PHILO): $(MAN_OBJ)
	@ $(CC) $(CFLAGS) $(MAN_OBJ) -o $(PHILO)
	@ printf "===============================================\n"
	@ printf "All mandatory source files have been compiled.\n"
	@ printf "Executable file philo has been generated.\n"
	@ printf "===============================================\n"

clean:
	@ rm -fr $(MAN_OBJ)
	@ printf "===============================================\n"
	@ printf "All object files have been destroyed.\n"
	@ printf "===============================================\n"

fclean:
	@ rm -fr $(PHILO) $(MAN_OBJ)
	@ printf "=========================================================\n"
	@ printf "All object files and executable file have been destroyed.\n"
	@ printf "==========================================================\n"

re: fclean all

.PHONY: fclean clean re bonus