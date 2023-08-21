################################################################################
#                                                                              #
#                                COMMANDES                                     #
#                                                                              #
################################################################################

red = \033[1;31m
gre = \033[1;32m
yel = \033[1;33m
blu = \033[1;34m
mag = \033[1;35m
cya = \033[1;36m
raz = \033[0m

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
	format := -f macho64 -D MACOSX
else
	format := -f elf64 -D LINUX 
	 
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

bonus_rule = all
regular_size=70
ifdef BONUS
	OBJS += $(BONUS_OBJS)
	compil_options += -Wno-deprecated-non-prototype -DBONUS="\"C\'est la bonus party\""
	bonus_rule = bonus
	regular_size=120
	_bonus = _bonus
endif
################################################################################
#                                                                              #
#                                  RULES                                       #
#                                                                              #
################################################################################

.PHONY: all clean clean_bonus fclean fclean_bonus re bonus test test_bonus fclean_test

all: $(NAME)

# $?: the name of all the prerequisites that are newer than the target with
# spaces between them, for archive members, only the named member is used (the
# part retrieved with $% or %)
$(NAME): $(OBJS)
	@$(echo) " *** Creating archive: \t\t$(gre)%30.30s$(raz)\n\t$(gre)%-$(regular_size).$(regular_size)s$(raz)\n\r" "$@ $(_bonus)" "$?"
	@$(ar) $(archive_options) $@ $?

clean:
	@$(echo) " *** Deleting object files:\n\t$(mag)%-70.70s$(raz)\n\r" "$(OBJS)"
	@$(rm) $(OBJS)

clean_bonus: clean
	@$(echo) " *** Deleting bonus object files:\n\t$(mag)%-120.120s$(raz)\n\r" "$(BONUS_OBJS)"
	@$(rm) $(BONUS_OBJS)

fclean: clean
	@$(echo) " *** Deleting archive\t$(red)%30.30s$(raz)\n\r" "$(NAME) $(_bonus)"
	@$(rm) $(NAME)

fclean_bonus: clean_bonus
	@$(echo) " *** Deleting bonus archive\t$(red)%30.30s$(raz)\n\r" "$(NAME) bonus"
	@$(rm) $(NAME)

re: fclean all

bonus: 
	@make $(NAME) BONUS=1

################################################################################
#                                                                              #
#                                  TESTS                                       #
#                                                                              #
################################################################################

test: fclean_test $(bonus_rule) $(TEST_SRCS) 
	@$(echo) " *** Starting testing: \t\t$(blu)%30.30s$(raz)\n\r" "$(NAME) $(_bonus)"
	@$(cc) $(compil_options) $(TEST_SRCS) -L . -lasm -o $@
	@./$@ "Hello WORLD"

test_bonus:
	@$(make) test BONUS=1

fclean_test: fclean_bonus
	@${rm} test $(TEST_OBJS)

# $(as): 					commande assembleur, ici nasm
# $(format): 				si Linux => elf64, si MACOSX => macho64
# $(warning_options):		-Wall -Werror (-Wextra does not work with nasm)
# $<						name of the first prerequisite
%.o: %.s 
	@$(echo) " *** Creating object files:\t$(cya)%30.30s$(raz)\n\r" "$(<:.s=.o)"
	@$(as) $(format) $(warning_options) $< -o $(<:.s=.o)
