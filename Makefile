##
## Makefile for Makefile in /home/Epitech
##
## Made by moriss_h
## Login   <moriss_h@epitech.net>
##
## Started on  Sun Jun  9 03:35:24 2013 Hugues
## Last update Thu Jul  3 15:33:38 2014 Hugues
##

SRC		=	main.c \
			elf.c \
			endianess.c \
			file.c \
			liste.c \
			liste_find.c \
			node.c \
			ftrace.c \
			path.c \
			call.c \
			ff_call.c \
			mrrbyte.c \
			ptr_tab.c \
			peektext.c \
			section32.c \
			section64.c \
			section_search.c \
			section_spec32.c \
			section_spec64.c \
			strace.c \
			get_next_line.c \
			symbol32.c \
			symbol64.c \
			symbol_type32.c \
			symbol_type64.c \
			symbols_search.c \
			func_name.c \
			find_func.c \
			symbol_resolver.c \
			relocation.c \
			elf_dynamic_symbols.c \
			elf_dependancies.c \
			dotty.c

CC		=	gcc
FILETYPE	=	.c

RM		=	rm -f

NAME		=	trace

OBJDIR		=	obj/
SRCDIR		=	src/
INCDIR		=	inc/

CFLAGS		+=	-I$(INCDIR)
CFLAGS		+=	-Wall -Wextra -Winit-self
CFLAGS		+=	-Wunused-function -pipe -g

LDFLAGS		+=	-Wl,-O1

OBJ		=	$(patsubst %${FILETYPE},${OBJDIR}%.o, $(SRC))
DEPS		=	$(patsubst %${FILETYPE}, ${OBJDIR}%.d, $(SRC))

PRINTFLAGS	=	0

dummy		:=	$(shell test -d $(OBJDIR) || mkdir -p $(OBJDIR))
dummy		:=	$(shell test -d $(SRCDIR) || mkdir -p $(SRCDIR))
dummy		:=	$(shell test -d $(INCDIR) || mkdir -p $(INCDIR))

$(OBJDIR)%.o:		$(patsubst %${FILETYPE}, ${SRCDIR}%${FILETYPE}, %${FILETYPE})
			@if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
ifneq ("$(shell tty)", "not a tty")
			@if [ $(PRINTFLAGS) = "0" ]; then \
			echo -e "Compile flags { $(CFLAGS) }" | sed 's/^-e //' \
			| sed 's/[-a-zA-Z]\+/\x1B[31m&\x1B[0m/g' \
			| sed 's/[A-Z]\+/\x1B[32m&\x1B[0m/g' \
			| sed 's/[{}]/\x1B[34m&\x1B[0m/g'; fi
			$(eval PRINTFLAGS = 1)
			@echo -e "Compiling $< $(patsubst %.o, %.d, $@)" | sed 's/^-e //' \
			| sed 's/[-a-zA-Z]\+/\x1B[31m&\x1B[0m/g' \
			| sed 's/[A-Z]\+/\x1B[32m&\x1B[0m/g' | sed 's/d/\x1B[35m&\x1B[0m/'
			@$(CC) $(CFLAGS) -c $< -o $@
			@$(CC) $(CFLAGS) -MM -MF $(patsubst %.o, %.d, $@) -MT $@ -MT $(patsubst %.o, %.d, $@) -c $<
else
			$(CC) $(CFLAGS) -c $< -o $@
			$(CC) $(CFLAGS) -MM -MF $(patsubst %.o, %.d, $@) -MT $@ -MT $(patsubst %.o, %.d, $@) -c $<
endif

$(NAME):	$(OBJ)
ifneq ("$(shell tty)", "not a tty")
		@echo -e "Linking $@ { $(LDFLAGS) }" | sed 's/^-e //' \
		| sed 's/[-a-zA-Z]\+/\x1B[34m&\x1B[0m/g'
		@$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)
else
		$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)
endif

-include $(DEPS)

all:	$(NAME)

clean:
ifneq ("$(shell tty)", "not a tty")
	@echo -e "Removing object !" | sed 's/^-e //' \
	| sed 's/[-a-zA-Z]\+/\x1B[35m&\x1B[0m/g'
	@$(RM) $(OBJ) $(DEPS)
else
	$(RM) $(OBJ) $(DEPS)
endif

fclean:	clean
ifneq ("$(shell tty)", "not a tty")
	@echo -e "Removing ${NAME} !" | sed 's/^-e //' \
	| sed 's/[-a-zA-Z]\+/\x1B[36m&\x1B[0m/g'
	@$(RM) $(NAME)
else
	$(RM) $(NAME)
endif

re:	fclean all

help:
	@echo -e "\033[37mTarget available: all, ${NAME}, clean, fclean\033[00m" | sed 's/^-e //'

.PHONY:	all clean fclean re help

