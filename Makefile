arch = $(shell uname)
as = nasm
cc = gcc
rm = rm -rf
ar = ar
echo = printf

# a voir ce qu'il y a besoin pour le link des sources et le test
warning_options = -Wall -Werror
debug_options = -g
compil_options = -Wall -Werror -Wextra
archive_options = crs

NAME = libasm
#SRCS = $(addprefix ft_, $(addsuffix .s, \
#			strlen\
#			strcpy\
#			strcmp\
#			write\
#			read\
#			strdup\
#	   ))
SRCS = $(addprefix ft_, $(addsuffix .s, \
			strlen\
			strcpy\
	   ))
OBJS = $(SRCS:.s=.o)

BONUS_SRCS = $(addprefix ft_, $(addsuffix _bonus.s, \
			atoi_base\
			list_push_front\
			list_size\
			list_sort\
			list_remove_if\
	   ))
BONUS_OBJS = $(BONUS_SRCS:.s=.o)

TEST_SRCS = main.c
TEST_OBJS = $(TEST_SRCS:.c=.o)

ifeq (${arch},Darwin)
	format := -f macho64
else
	format := -f elf64
endif

options = $(warning_options) $(format)

ifdef DEBUG
	options += $(debug_options)
endif

EXP_SRCS = $(addprefix ft_, $(addsuffix .c, \
			strlen\
			strcpy\
			strcmp\
			strdup\
			memcpy\
	   ))
EXP_OBJS = $(EXP_SRCS:.c=.o)
EXP_ASM = $(EXP_SRCS:.c=.s)

BONUS_EXP_SRCS = $(addprefix ft_, $(addsuffix _bonus.c, \
			atoi_base\
			list_push_front\
			list_size\
			list_sort\
			list_remove_if\
	   ))
BONUS_EXP_OBJS = $(BONUS_EXP_SRCS:.c=.o)
EXP_PATH = ./minilibft/
EXP_HEADER = minilibft.h

VPATH += $(EXP_PATH)
.PHONY: clean fclean re all bonus test experience1

all: $(NAME)
	@$(echo) "arch: %-10.10s, opt: %-50.50s\r" $(arch) ${options}

$(NAME): $(OBJS)
#	$(as) $(format) $(warning_options) $^
	$(ar) $(archive_options) $@.a $^

clean:
	$(rm) $(OBJS)

clean_bonus: clean
	$(rm) $(BONUS_OBJS)

fclean: clean
	$(rm) $(NAME)

fclean_bonus: clean_bonus
	$(rm) $(NAME)

re: clean all

bonus: $(OBJS) $(BONUS_OBJS)
	$(as) $(format) $(warning_options) $^
	$(ar) $(archive_options) $@.a $^

test: $(TEST_SRCS) $(NAME)
ifdef BONUS
	make bonus
	$(cc) $(compil_options) -L . -lasm $< -o $@
else
	make $(NAME)
	$(cc) $(compil_options) -L . -lasm $< -o $@
endif
	./$@ Hello

%.o: %.s 
	$(as) $(format) $(warning_options) $< -o $(<:.s=.o)
#	$(cc) $(warning_options) -I $(EXP_HEADER) -S $< -o $(<:.c=.s)
%.s: %.c 
	$(cc) $(warning_options) -I $(EXP_HEADER) -S $< -o $(<:.c=.s)

# $< 1ere dependance
experience1: $(EXP_ASM)
#	$(cc) $(warning_options) -I $(EXP_HEADER) -S $^ -o $(^:.c=.s)
