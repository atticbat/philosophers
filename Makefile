# -*- MakeFile -*-

VPATH	=	init src utilities

SRC		=	main.c error.c init.c time.c string.c thread_start.c
OBJ		=	$(addprefix _obj/,$(notdir $(SRC:.c=.o)))
NAME	=	philo
CFLAGS	=	-Wall -Werror -Wextra
IFLAGS	=	-I ./includes/

all:		$(NAME)

_obj:
	mkdir _obj

_obj/%.o:	%.c | _obj
	cc $(CFLAGS) -c -MMD -MP $(IFLAGS) $< -o $@

$(NAME):	$(OBJ)
	cc $(CFLAGS) $^ -o $@

fclean:		clean
	rm philo

clean:
	rm -rf _obj

re:			fclean all

.PHONY: all clean fclean re
-include $(OBJ:.o=.d)