#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define FPRINTF(args...) fprintf(stdout, args);
#define PRINT_INT(x) FPRINTF("\033[31;1m%s:%d\033[0m\t%-45s =\t%d\n", __FILE__, __LINE__, #x, x)
#define BONUS_INT(x) FPRINTF("\033[32;1m%s:%d\033[0m\t%-75s =\t%d\n", __FILE__, __LINE__, #x, x)
#define PRINT_STR(x) FPRINTF("\033[33;1m%s:%d\033[0m\t%-45s =\t%s\n", __FILE__, __LINE__, #x, x)
#define BONUS_STR(x) FPRINTF("\033[34;1m%s:%d\033[0m\t%-45s =\t%s\n", __FILE__, __LINE__, #x, x)

extern	size_t	ft_strlen(const char *s);
extern	char	*ft_strcpy(char *dst, const char *src);
extern	int		ft_strcmp(const char *s1, const char *s2);
extern	char	*ft_strdup(const char *s);
extern	ssize_t	ft_write(int fildes, const void *buffer, int iovcnt);
extern	ssize_t	ft_read(int fildes, const void *buffer, size_t iovcnt);

#ifdef BONUS
typedef struct s_list {
	void			*data;
	struct s_list	*next;
}				t_list;

t_list	*ft_create_elem(void *data) {
	t_list	*elem = malloc(sizeof(t_list));
	if (!elem)
		return NULL;

	elem->data = data;
	elem->next = NULL;
	return elem;
}

extern	void	ft_list_push_front(t_list **begin_list, void *data);
extern	int		ft_list_size(t_list *begin_list);
extern	void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fn)(void *));
extern	void	ft_list_sort(t_list **begin_list, int (*cmp)());
extern	int		ft_atoi_base(char *str, char *base);
#endif

int main(int argc, char **argv) {

	if (argc == 2 ) {
#ifndef BONUS
		/* ft_strlen - strlen comparison */
		int len_ft_strlen = ft_strlen(argv[1]);

		PRINT_STR("----------------------------------------");
		PRINT_INT((int)strlen(argv[1]));
		PRINT_INT((int)ft_strlen(argv[1]));

		/* ft_strcpy - strcpy comparison */
		char *dst = calloc(sizeof(char *), len_ft_strlen + 1);

		PRINT_STR("----------------------------------------");
		PRINT_STR(strcpy(dst, argv[1]));
		PRINT_STR(dst);
		PRINT_STR("----------------------------------------");
		PRINT_STR(ft_strcpy(dst, argv[1]));
		PRINT_STR(dst);
		PRINT_STR("----------------------------------------");

		/* ft_strcmp - strcmp comparison */
		PRINT_INT(strcmp(argv[1], dst));
		PRINT_INT(ft_strcmp(argv[1], dst));
		PRINT_STR("----------------------------------------");
		PRINT_INT(strcmp(dst, &argv[1][2]));
		PRINT_INT(ft_strcmp(dst, &argv[1][2]));
		PRINT_STR("----------------------------------------");
		PRINT_INT(strcmp(&argv[1][1], dst));
		PRINT_INT(ft_strcmp(&argv[1][1], dst));
		PRINT_STR("----------------------------------------");

		/* ft_strdup - strdup comparison */
		char *dup_base = strdup(argv[1]);
		char *dup_ft = ft_strdup(argv[1]);

		PRINT_STR(dup_base);
		PRINT_STR(dup_ft);
		PRINT_STR("----------------------------------------");

		free(dup_base);
		free(dup_ft);

		/* ft_write - write comparison */
		errno = 0;
		PRINT_INT((int)write(1, dst, len_ft_strlen));
		PRINT_INT(errno);
		PRINT_STR(strerror(errno));
		PRINT_STR("----------------------------------------");
		errno = 0;
		PRINT_INT((int)ft_write(1, dst, len_ft_strlen));
		PRINT_INT(errno);
		PRINT_STR(strerror(errno));
		PRINT_STR("----------------------------------------");

		errno = 0;
		PRINT_INT((int)write(1, dst, -10));
		PRINT_INT(errno);
		PRINT_STR(strerror(errno));
		PRINT_STR("----------------------------------------");
		errno = 0;
		PRINT_INT((int)ft_write(1, dst, -10));
		PRINT_INT(errno);
		PRINT_STR(strerror(errno));
		PRINT_STR("----------------------------------------");

		errno = 0;
		PRINT_INT((int)write(-1, dst, len_ft_strlen));
		PRINT_INT(errno);
		PRINT_STR(strerror(errno));
		PRINT_STR("----------------------------------------");
		errno = 0;
		PRINT_INT((int)ft_write(-1, dst, len_ft_strlen));
		PRINT_INT(errno);
		PRINT_STR(strerror(errno));
		PRINT_STR("----------------------------------------");

		errno = 0;
		PRINT_INT((int)write(1, NULL, len_ft_strlen));
		PRINT_INT(errno);
		PRINT_STR(strerror(errno));
		PRINT_STR("----------------------------------------");
		errno = 0;
		PRINT_INT((int)ft_write(1, NULL, len_ft_strlen));
		PRINT_INT(errno);
		PRINT_STR(strerror(errno));
		PRINT_STR("----------------------------------------");


		size_t	len = 50;
		char	test_read[50] = {0};
		char	test_ft_read[50] = {0};

		errno = 0;
		PRINT_INT((int)read(0, test_read, len));
		PRINT_INT(errno);
		PRINT_STR(strerror(errno));
		PRINT_STR(test_read);
		PRINT_STR("----------------------------------------");
		errno = 0;
		PRINT_INT((int)ft_read(0, test_ft_read, len));
		PRINT_INT(errno);
		PRINT_STR(strerror(errno));
		PRINT_STR(test_ft_read);
		PRINT_STR("----------------------------------------");

		errno = 0;
		PRINT_INT((int)read(-1, test_read, len));
		PRINT_INT(errno);
		PRINT_STR(strerror(errno));
		PRINT_STR(test_read);
		PRINT_STR("----------------------------------------");
		errno = 0;
		PRINT_INT((int)ft_read(-1, test_ft_read, len));
		PRINT_INT(errno);
		PRINT_STR(strerror(errno));
		PRINT_STR(test_ft_read);
		PRINT_STR("----------------------------------------");

		errno = 0;
		PRINT_INT((int)read(0, test_read, -10));
		PRINT_INT(errno);
		PRINT_STR(strerror(errno));
		PRINT_STR(test_read);
		PRINT_STR("----------------------------------------");
		errno = 0;
		PRINT_INT((int)ft_read(0, test_ft_read, -10));
		PRINT_INT(errno);
		PRINT_STR(strerror(errno));
		PRINT_STR(test_ft_read);
		PRINT_STR("----------------------------------------");

		errno = 0;
		PRINT_INT((int)read(0, NULL, len));
		PRINT_INT(errno);
		PRINT_STR(strerror(errno));
		PRINT_STR(test_read);
		PRINT_STR("----------------------------------------");
		errno = 0;
		PRINT_INT((int)ft_read(0, NULL, len));
		PRINT_INT(errno);
		PRINT_STR(strerror(errno));
		PRINT_STR(test_ft_read);
		PRINT_STR("----------------------------------------");
		free(dst);
#endif

#ifdef BONUS
		BONUS_STR(BONUS);
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

		BONUS_STR("----------------------------------------");

		t_list	*begin = NULL;
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
