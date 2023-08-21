#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>

#define FPRINTF(args...)		fprintf(stdout, args);
#define PRINT_INT(x)			FPRINTF("\033[31;1m%s:%d\033[0m\t%-45s =\t%d\n", __FILE__, __LINE__, #x, x)
#define BONUS_INT(x)			FPRINTF("\033[32;1m%s:%d\033[0m\t%-75s =\t%d\n", __FILE__, __LINE__, #x, x)
#define PRINT_STR(x)			FPRINTF("\033[33;1m%s:%d\033[0m\t%-45s =\t%s\n", __FILE__, __LINE__, #x, x)
#define BONUS_STR(x)			FPRINTF("\033[34;1m%s:%d\033[0m\t%-45s =\t%s\n", __FILE__, __LINE__, #x, x)
#define BUFFER_SIZE				4096

extern	size_t					ft_strlen(const char *s);
extern	char					*ft_strcpy(char *dst, const char *src);
extern	int						ft_strcmp(const char *s1, const char *s2);
extern	char					*ft_strdup(const char *s);
extern	ssize_t					ft_write(int fildes, const void *buffer, size_t iovcnt);
extern	ssize_t					ft_read(int fildes, const void *buffer, size_t iovcnt);

#ifdef BONUS
typedef struct					s_list {
	void			*data;
	struct s_list	*next;
}								t_list;

t_list							*ft_create_elem(void *data) {
	t_list			*elem = malloc(sizeof(t_list));
	if (!elem)
		return NULL;

	elem->data = data;
	elem->next = NULL;
	return elem;
}

extern	void					ft_list_push_front(t_list **begin_list, void *data);
extern	int						ft_list_size(t_list *begin_list);
extern	void					ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fn)(void *));
extern	void					ft_list_sort(t_list **begin_list, int (*cmp)());
extern	int						ft_atoi_base(char *str, char *base);
#endif

#ifdef LIBASM
# define STRLEN(s)				ft_strlen(s)
# define STRCPY(dst, src)		ft_strcpy(dst, src)
# define STRCMP(s1, s2)			ft_strcmp(s1, s2)
# define STRDUP(s)				ft_strdup(s)
# define READ(x, y, z)			ft_read(x, y, z)
# define WRITE(x, y, z)			ft_write(x, y, z)
# define VERSION				"ft version"
# define VERSION_STRLEN			"----- FT_STRLEN ------------------------"
# define VERSION_STRCPY			"----- FT_STRCPY ------------------------"
# define VERSION_STRCMP			"----- FT_STRCMP ------------------------"
# define VERSION_STRDUP			"----- FT_STRDUP ------------------------"
# define VERSION_REAWRI			"----- FT_READ / FT_WRITE ---------------"
# define VERSION_READ  			"----- FT_READ --------------------------"
# define VERSION_WRITE  		"----- FT_WRITE -------------------------"
# define VERSION_ATOI_B  		"----- FT_ATOI_BASE ---------------------"
#else
# define STRLEN(s)				strlen(s)
# define STRCPY(dst, src)		strcpy(dst, src)
# define STRCMP(s1, s2)			strcmp(s1, s2)
# define STRDUP(s)				strdup(s)
# define READ(x, y, z)			read(x, y, z)
# define WRITE(x, y, z)			write(x, y, z)
# define VERSION				"regular version"
# define VERSION_STRLEN			"-------- STRLEN ------------------------"
# define VERSION_STRCPY			"-------- STRCPY ------------------------"
# define VERSION_STRCMP			"-------- STRCMP ------------------------"
# define VERSION_STRDUP			"-------- STRDUP ------------------------"
# define VERSION_REAWRI			"-----    READ /    WRITE ---------------"
# define VERSION_READ  			"-----    READ --------------------------"
# define VERSION_WRITE  		"-----    WRITE -------------------------"
#endif

enum e_functions {
	TEST_STRLEN,
	TEST_STRCPY,
	TEST_STRCMP,
	TEST_STRDUP,
	TEST_READ,
	TEST_WRITE,
	TEST_ATOI_BASE,
	TEST_FT_LIST_PUSH_FRONT,
	TEST_FT_LIST_SIZE,
	TEST_FT_LIST_REMOVE_IF,
	TEST_FT_LIST_SORT
};

int	read_file(int fd_in, int fd_out) {
	int		res_read_size = 0;
	int		read_size = 0;
	int		res_write_size = 0;
	int		write_size = 0;
	char	buffer[BUFFER_SIZE] = {0};

	while ((res_read_size = READ(fd_in, buffer, BUFFER_SIZE)) > 0) {
		read_size += res_read_size;
		if ((res_write_size = WRITE(fd_out, buffer, BUFFER_SIZE)) < 0) {
			PRINT_STR(VERSION_WRITE);
			return errno;
		}
		write_size += res_write_size;
		buffer[0] = 0;
	}
	if (res_read_size == -1) {
		PRINT_STR(VERSION_READ);
		return errno;
	}
	PRINT_STR(VERSION_REAWRI);
	return read_size;
}

void tests_read_and_write(char *filename) {
	int		fd = open(filename, O_RDONLY);
	int		fds_in[] = {fd, 177, fd};
	int		fds_out[] = {1, 1, 177};
	
	for (int i = 0; i < 3; i++) {
		errno = 0;
		PRINT_STR(VERSION);
		PRINT_INT(read_file(fds_in[i], fds_out[i]));
		PRINT_INT(errno);
		PRINT_STR(strerror(errno));
		PRINT_STR("----------------------------------------");
	}
	close(fd);
	PRINT_STR(VERSION_REAWRI);
}

void tests_strlen(char **strs) {
	for (int i = 0; strs[i] != NULL; i++) {
		PRINT_STR(VERSION);
		PRINT_STR(strs[i]);
		PRINT_INT((int)STRLEN(strs[i]));
		PRINT_STR("----------------------------------------");
	}
	PRINT_STR(VERSION_STRLEN);
}

void	tests_strcpy(char **strs) {
	for (int i = 0; strs[i] != NULL; i++) {
		char *dst = calloc(sizeof(char *), STRLEN(strs[i]) + 1);
		PRINT_STR(VERSION);
		PRINT_STR(strs[i]);
		PRINT_STR(STRCPY(dst, strs[i]));
		PRINT_STR(dst);
		PRINT_STR("----------------------------------------");
		free(dst);
	}
	PRINT_STR(VERSION_STRCPY);
}

void	tests_strcmp(char **strs1, char **strs2) {
	for (int i = 0; strs1[i] != NULL; i++) {
		PRINT_INT(STRCMP(strs1[i], strs2[i]));
		PRINT_STR("----------------------------------------");
		PRINT_INT(STRCMP(strs2[i], strs1[i]));
		PRINT_STR("----------------------------------------");
		PRINT_INT(STRCMP(&strs1[i][1], &strs2[i][1]));
		PRINT_STR("----------------------------------------");
		PRINT_INT(STRCMP(&strs1[i][1], &strs2[i][2]));
		PRINT_STR("----------------------------------------");
	}
	PRINT_STR(VERSION_STRCMP);
}

void	tests_strdup(char **strs) {
	for (int i = 0; strs[i] != NULL; i++) {
		char *str_dup = STRDUP(strs[i]);
		PRINT_STR(VERSION);
		PRINT_STR(strs[i]);
		PRINT_STR(str_dup);
		PRINT_STR("----------------------------------------");
		free(str_dup);
	}
	PRINT_STR(VERSION_STRDUP);
}

void print_result(enum e_functions type_test, ...) {
	va_list		args;

	va_start(args, type_test);

	switch (type_test) {
		case TEST_STRLEN:
			{
				char **test_strs = va_arg(args, char**);
				tests_strlen(test_strs);
			}
			break;
		case TEST_STRCPY:
			{
				char **test_strs = va_arg(args, char**);
				tests_strcpy(test_strs);
			}
			break;
		case TEST_STRCMP:
			{
				char **test_strs1 = va_arg(args, char**);
				char **test_strs2 = va_arg(args, char**);
				tests_strcmp(test_strs1, test_strs2);
			}
			break;
		case TEST_STRDUP:
			{
				char **test_strs = va_arg(args, char**);
				tests_strdup(test_strs);
			}
			break;
		case TEST_READ:
		case TEST_WRITE: 
			{
				char *filename = va_arg(args, char*);
				tests_read_and_write(filename);
			}
			break;
		case TEST_ATOI_BASE:
			break;
		case TEST_FT_LIST_PUSH_FRONT:
			break;
		case TEST_FT_LIST_SIZE:
			break;
		case TEST_FT_LIST_REMOVE_IF:
			break;
		case TEST_FT_LIST_SORT:
			break;
		default:
			break;
	}
	va_end(args);

#ifndef BONUS
	printf("\033[35m========================================================================================================================\n\033[0m");
#else
	printf("\033[36m========================================================================================================================\n\033[0m");
#endif
}

int main(int argc, char **argv) {

	if (argc == 2 ) {
#ifndef BONUS
		char *strings_to_test[42] = {
			&argv[1][STRLEN(argv[1]) / 2],
			argv[1],
			"Hello 42 World",
			"Lorem Ipsum                         ......",
			"",
			"1234567890",
			"123",
			NULL
	};
		char *strings_to_cmp[42] = {
			"Hello 42 World",
			argv[1],
			"Lorem Ipsum                         ......",
			&argv[1][STRLEN(argv[1]) / 2],
			"1234567890",
			"",
			"123",
			NULL
	};
		
		print_result(TEST_STRLEN, strings_to_test);

		print_result(TEST_STRCPY, strings_to_test);
		
		print_result(TEST_STRCMP, strings_to_test, strings_to_cmp);

		print_result(TEST_STRDUP, strings_to_cmp);

		print_result(TEST_WRITE, "./Makefile");
#endif

#ifdef BONUS
		char *atoi_base_tests_datas[42][2] = {
			{"123", "0123456789"},// -> 123
			{"123", "0123456789ABCDEF"},// -> 291
			{"7B", "0123456789ABCDEF"},// -> 123
			{"123", "01"},// -> 0, 2 et 3 ne font pas partie de la base
			{"1111011", "01"},// -> 123
			{"                     123", "0123456789ABCDEF"},// -> 291
			{"                     ---+--+123", "0123456789ABCDEF"},// -> -291
			{"123", "0123456A89ABCDEF"},// -> 0, 2 fois le m char
			{"123", "1"},// -> 0, base < 2
			{"--******** ++-----   123", "0123456789ABCDEF"},// 0, car * non autorié
			{"123", "0123456a89ABCDEF"},// 291
			{"3aa", "0123456a89ABCDEF"},// 887
			{"887", "0123456a89ABCDEF"},// -> 0, normal 7 n'est pas dans la base, et
										// je considere a et A differents sans precision
										// info sup dans le sujet
			{"2147483647", "0123456789"},// INT_MAX
			{"7FFFFFFF", "0123456789ABCDEF"},
			{"01111111111111111111111111111111", "01"},
			{"2147483648", "0123456789"},// overflow INT_MAX
			{"80000000", "0123456789ABCDEF"},
			{"10000000000000000000000000000000", "01"},
			{"-2147483647", "0123456789"},// INT_MIN
			{"-7FFFFFFF", "0123456789ABCDEF"},
			{"01111111111111111111111111111111", "01"},
			{"-2147483648", "0123456789"},// -INT_MAX
			{"-80000000", "0123456789ABCDEF"},
			{"-10000000000000000000000000000000", "01"},
			{"-1111111111111111", "1"},// -> 0, car base < 2
			{NULL, NULL}
		};

		for (int i = 0; atoi_base_tests_datas[i] != NULL; i++) {
			BONUS_INT((int)ft_atoi_base(atoi_base_tests_datas[i][0], atoi_base_tests_datas[i][1]));
			BONUS_STR(VERSION_ATOI_B);
		}


	/*	BONUS_STR(BONUS);
		BONUS_STR("----------------------------------------");
		BONUS_INT((int)ft_atoi_base("123", "0123456789"));	// -> 123
		BONUS_INT((int)ft_atoi_base("123", "0123456789ABCDEF")); // -> 291
		BONUS_INT((int)ft_atoi_base("7B", "0123456789ABCDEF"));	// -> 123
		BONUS_INT((int)ft_atoi_base("123", "01"));	// -> 0, 2 et 3 ne font pas partie de la base
		BONUS_INT((int)ft_atoi_base("1111011", "01"));	// -> 123
		BONUS_INT((int)ft_atoi_base("                     123", "0123456789ABCDEF")); // -> 291
		BONUS_INT((int)ft_atoi_base("                     ---+--+123", "0123456789ABCDEF")); // -> -291
		BONUS_INT((int)ft_atoi_base("123", "0123456A89ABCDEF")); // -> 0, 2 fois le m char
		BONUS_INT((int)ft_atoi_base("123", "1"));	// -> 0, base < 2
		BONUS_INT((int)ft_atoi_base("--******** ++-----   123", "0123456789ABCDEF")); // 0, car * non autorié
		BONUS_INT((int)ft_atoi_base("123", "0123456a89ABCDEF"));	// 291
		BONUS_INT((int)ft_atoi_base("3aa", "0123456a89ABCDEF"));	// 887
		BONUS_INT((int)ft_atoi_base("887", "0123456a89ABCDEF")); // -> 0, normal 7 n'est pas dans la base, et
																 // je considere a et A differents sans precision
																// info sup dans le sujet
		BONUS_STR("----------------------------------------");
		BONUS_INT((int)ft_atoi_base("2147483647", "0123456789")); // INT_MAX
		BONUS_INT((int)ft_atoi_base("7FFFFFFF", "0123456789ABCDEF"));
		BONUS_INT((int)ft_atoi_base("01111111111111111111111111111111", "01"));
		BONUS_STR("----------------------------------------");
		BONUS_INT((int)ft_atoi_base("2147483648", "0123456789")); // overflow INT_MAX
		BONUS_INT((int)ft_atoi_base("80000000", "0123456789ABCDEF"));
		BONUS_INT((int)ft_atoi_base("10000000000000000000000000000000", "01"));
		BONUS_STR("----------------------------------------");
		BONUS_INT((int)ft_atoi_base("-2147483647", "0123456789")); // INT_MIN
		BONUS_INT((int)ft_atoi_base("-7FFFFFFF", "0123456789ABCDEF"));
		BONUS_INT((int)ft_atoi_base("-01111111111111111111111111111111", "01"));
		BONUS_STR("----------------------------------------");
		BONUS_INT((int)ft_atoi_base("-2147483648", "0123456789")); // -INT_MAX
		BONUS_INT((int)ft_atoi_base("-80000000", "0123456789ABCDEF"));
		BONUS_INT((int)ft_atoi_base("-10000000000000000000000000000000", "01"));
		BONUS_STR("----------------------------------------");
		BONUS_INT((int)ft_atoi_base("-1111111111111111", "1")); // -> 0, car base < 2

		BONUS_STR("----------------------------------------");*/

		//t_list	*begin = NULL;
		t_list	*begin;
		for (int i = ft_strlen(argv[1]); i > 0; --i) {
			char *val = ft_strdup(argv[1]);;
			if (i % 2)
				*(val) -= 12;
			*(val) += 7;
			ft_list_push_front(&begin, val);
		}
		t_list	*p_begin = begin;
		while (p_begin) {
			BONUS_STR((char *)p_begin->data);
			p_begin = p_begin->next;
		}
		BONUS_STR("----------------------------------------");
		BONUS_INT(ft_list_size(begin));
		BONUS_STR("-ft_list_sort---------------------------");
		ft_list_sort(&begin, ft_strcmp);
		p_begin = begin;
		while (p_begin) {
			BONUS_STR((char *)p_begin->data);
			p_begin = p_begin->next;
		}
		BONUS_STR("----------------------------------------");
		BONUS_INT(ft_list_size(begin));
		while (begin) {
			ft_list_remove_if(&begin, begin->data, ft_strcmp, free);
		}
		BONUS_STR("-After releasing t_list linked list-----");
		BONUS_INT(ft_list_size(begin));
		BONUS_STR("----------------------------------------");
#endif

		return 0;
	}
	return 1;
}
