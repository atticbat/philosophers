# -*- MakeFile -*-

VPATH	=	init src utilities

SRC		=	main.c error.c init.c time.c string.c thread_start.c nu_itoa.c
OBJ		=	$(addprefix _obj/,$(notdir $(SRC:.c=.o)))
NAME	=	philo
CFLAGS	=	-Wall -Werror -Wextra #-fsanitize=thread
IFLAGS	=	-I ./includes/

all:		$(NAME)

_obj:
	mkdir _obj

_obj/%.o:	%.c | _obj
	cc $(CFLAGS) -c -MMD -MP $(IFLAGS) $< -o $@ -pthread

$(NAME):	$(OBJ)
	cc $(CFLAGS) -pthread $^ -o $@

fclean:		clean
	rm -rf philo

clean:
	rm -rf _obj

re:			fclean all

.PHONY: all clean fclean re
-include $(OBJ:.o=.d)