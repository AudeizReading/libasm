################################################################################
#                                                                              #
#                                COMMANDES                                     #
#                                                                              #
################################################################################

arch = $(shell uname)
as = nasm
cc = gcc
rm = rm -rf
ar = ar
echo = printf
make = make -s --no-print-directory -i

warning_options = -Wall -Werror
debug_options = -g
compil_options = -Wall -Werror -Wextra
archive_options = crs

ifeq (${arch},Darwin)
	format := -f macho64
endif

################################################################################
#                                                                              #
#                                  FILES                                       #
#                                                                              #
################################################################################

NAME = libasm.a
SRCS = $(addprefix ft_, $(addsuffix .s, \
			strlen\
			strcpy\
			strcmp\
			strdup\
			write\
			read\
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

################################################################################
#                                                                              #
#                                  RULES                                       #
#                                                                              #
################################################################################

.PHONY: clean fclean re all bonus test 

all: $(NAME)

ifdef BONUS
$(NAME): $(OBJS) $(BONUS_OBJS)
	$(ar) $(archive_options) $@ $^
else
$(NAME): $(OBJS)
	$(ar) $(archive_options) $@ $^
endif

clean:
	$(rm) $(OBJS)

clean_bonus: clean
	$(rm) $(BONUS_OBJS)

fclean: clean
	$(rm) $(NAME)

fclean_bonus: clean_bonus
	$(rm) $(NAME)

re: fclean all

bonus: 
	make $(NAME) BONUS=1

test: $(TEST_SRCS) 
	$(make) fclean_test
ifdef BONUS
	$(make) bonus
	$(cc) $(compil_options) -Wno-deprecated-non-prototype -DBONUS="\"C\'est la bonus party\"" -L . -lasm $^ -o $@
else
	$(make) 
	$(cc) $(compil_options) -L . -lasm $^ -o $@
endif
	./$@ "Hello 42's M8 That Will Correct Me"

test_bonus:
	$(make) test BONUS=1

fclean_test: fclean_bonus
	${rm} test $(TEST_OBJS)

%.o: %.s 
	$(as) $(format) $(warning_options) $< -o $(<:.s=.o)
