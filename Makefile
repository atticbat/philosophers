# -*- MakeFile -*-

VPATH	=	error init src time utilities

SRC		=	main.c error.c init.c time.c string.c
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

-include $(OBJL.o=.d)