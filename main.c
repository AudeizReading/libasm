#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#define FPRINTF(args...) fprintf(stdout, args);
#define PRINT_INT(x) FPRINTF("\033[31;1m%s:%d\033[0m\t%-45s =\t%d\n", __FILE__, __LINE__, #x, x)
#define BONUS_INT(x) FPRINTF("\033[32;1m%s:%d\033[0m\t%-75s =\t%d\n", __FILE__, __LINE__, #x, x)
#define PRINT_STR(x) FPRINTF("\033[33;1m%s:%d\033[0m\t%-45s =\t%s\n", __FILE__, __LINE__, #x, x)
#define BONUS_STR(x) FPRINTF("\033[34;1m%s:%d\033[0m\t%-45s =\t%s\n", __FILE__, __LINE__, #x, x)
#define BUFFER_SIZE 4096

extern	size_t	ft_strlen(const char *s);
extern	char	*ft_strcpy(char *dst, const char *src);
extern	int		ft_strcmp(const char *s1, const char *s2);
extern	char	*ft_strdup(const char *s);
extern	ssize_t	ft_write(int fildes, const void *buffer, size_t iovcnt);
extern	ssize_t	ft_read(int fildes, const void *buffer, size_t iovcnt);
#ifdef LIBASM
# undef READ
# undef WRITE
# undef VERSION
# define READ(x, y, z) ft_read(x, y, z)
# define WRITE(x, y, z) ft_write(x, y, z)
# define VERSION "ft version"
#else
# undef READ
# undef WRITE
# undef VERSION
# define READ(x, y, z) read(x, y, z)
# define WRITE(x, y, z) write(x, y, z)
# define VERSION "regular version"
#endif
int	read_file(int fd_in, int fd_out) {
	int		res_size = 0;
	int		size = 0;
	char	buffer[BUFFER_SIZE] = {0};

	while ((res_size = READ(fd_in, buffer, BUFFER_SIZE)) > 0) {
		size += res_size;
		if (WRITE(fd_out, buffer, BUFFER_SIZE) < 0)
			return errno;
		buffer[0] = 0;
	}
	if (res_size == -1)
		return errno;
	return size;
}

//int mandatory_scenario(int fd_in, int fd_out) {}

int		ft_strchr(char *s, int c)
{
	if (!s)
		return 0;
	while (*s)
		if (*s++ == c)
			return 1;
	return 0;
}

char	*after_n(char *s)
{
	if (!s)
		return NULL;
	while (*s)
		if (*s++ == '\n')
			return s;
	return NULL;
}

char	*before_n(char *s)
{
	char	*dst;
	char	*aft_n;
	int		len_dst;

	if (!s)
		return NULL;
	aft_n = after_n(s);
	len_dst = (aft_n) ? aft_n - s : (int)ft_strlen(s);
	dst = malloc(len_dst + 1);
	if (!dst)
		return NULL;
	dst[len_dst] = 0;
	while (len_dst--)
		dst[len_dst] = s[len_dst];
	return dst;
}

char	*ft_concat(char *s1, char *s2)
{
	char	*dst;
	int		len_s1 = ft_strlen(s1);
	int		len_dst = len_s1 + ft_strlen(s2);

	dst = malloc(len_dst + 1);
	if (!dst)
		return NULL;
	dst[len_dst] = 0;
	while (len_dst--)
		dst[len_dst] = (len_dst >= len_s1) ? s2[len_dst - len_s1] : s1[len_dst];
	free((void *)s1);
	return dst;
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1] = {0};
	char		*next_line = NULL;
	char		*tmp = NULL;
	int			ret = ft_strlen(buf) + 1;
	int			i = 0;

	if (BUFFER_SIZE < 1 || fd < 0)
		return NULL;
	while (!(ft_strchr(buf, '\n')) && ret > 0)
	{
		next_line = ft_concat(next_line, buf);
		if (!next_line)
			return NULL;
		ret = ft_read(fd, buf, BUFFER_SIZE);
		if (ret < 0)
		{
			if (next_line)
				free(next_line);
			return NULL;
		}
		buf[ret] = 0;
	}
	if (!ret && ft_strlen(next_line))
	{
		tmp = before_n(next_line);
		free(next_line);
		return tmp;
	}
	if (ft_strchr(buf, '\n'))
	{
		tmp = before_n(buf);
		if (!tmp)
		{
			if (next_line)
				free(next_line);
			return NULL;
		}
		next_line = ft_concat(next_line, tmp);
		if (!next_line)
		{
			free(tmp);
			return NULL;
		}
		free(tmp);
		tmp = after_n(buf);
		if (!tmp)
		{
			if (next_line)
				free(next_line);
			return NULL;
		}
		while (tmp[i])
		{
			buf[i] = tmp[i];
			i++;
		}
		buf[i] = 0;
	}
	else
	{
		if (next_line)
			free(next_line);
		return NULL;
	}
	return next_line;
}

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
		(void)argv;
		/* ft_strlen - strlen comparison */
		/*int len_ft_strlen = ft_strlen(argv[1]);

		PRINT_STR("----------------------------------------");
		PRINT_INT((int)strlen(argv[1]));
		PRINT_INT((int)ft_strlen(argv[1]));*/

		/* ft_strcpy - strcpy comparison */
		/*char *dst = calloc(sizeof(char *), len_ft_strlen + 1);

		PRINT_STR("----------------------------------------");
		PRINT_STR(strcpy(dst, argv[1]));
		PRINT_STR(dst);
		PRINT_STR("----------------------------------------");
		PRINT_STR(ft_strcpy(dst, argv[1]));
		PRINT_STR(dst);
		PRINT_STR("----------------------------------------");*/

		/* ft_strcmp - strcmp comparison */
		/*PRINT_INT(strcmp(argv[1], dst));
		PRINT_INT(ft_strcmp(argv[1], dst));
		PRINT_STR("----------------------------------------");
		PRINT_INT(strcmp(dst, &argv[1][2]));
		PRINT_INT(ft_strcmp(dst, &argv[1][2]));
		PRINT_STR("----------------------------------------");
		PRINT_INT(strcmp(&argv[1][1], dst));
		PRINT_INT(ft_strcmp(&argv[1][1], dst));
		PRINT_STR("----------------------------------------");*/

		/* ft_strdup - strdup comparison */
		/*char *dup_base = strdup(argv[1]);
		char *dup_ft = ft_strdup(argv[1]);

		PRINT_STR(dup_base);
		PRINT_STR(dup_ft);
		PRINT_STR("----------------------------------------");

		free(dup_base);
		free(dup_ft);*/

		/* ft_write - write comparison */
		/*errno = 0;
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
		PRINT_STR("----------------------------------------");*/

		errno = 0;
		int		fd = open("./Makefile", O_RDONLY);
		PRINT_INT(read_file(fd, 1));
		PRINT_INT(errno);
		PRINT_STR(strerror(errno));
		PRINT_STR(VERSION);
		PRINT_STR("-------- READ --------------------------");
		close(fd);
		errno = 0;
		fd = open("./Makefile", O_RDONLY);
#define LIBASM
		PRINT_INT(read_file(fd, 1));
		PRINT_INT(errno);
		PRINT_STR(strerror(errno));
		PRINT_STR(VERSION);
		PRINT_STR("----- FT_READ --------------------------");
		close(fd);
		errno = 0;
#undef LIBASM
		PRINT_INT(read_file(177, 1));
		PRINT_INT(errno);
		PRINT_STR(strerror(errno));
		PRINT_STR(VERSION);
		PRINT_STR("-------- READ --------------------------");
		errno = 0;
#define LIBASM
		PRINT_INT(read_file(177, 1));
		PRINT_INT(errno);
		PRINT_STR(strerror(errno));
		PRINT_STR(VERSION);
		PRINT_STR("----- FT_READ --------------------------");
#undef LIBASM
		errno = 0;
		fd = open("./Makefile", O_RDONLY);
		PRINT_INT(read_file(fd, 177));
		PRINT_INT(errno);
		PRINT_STR(strerror(errno));
		PRINT_STR(VERSION);
		PRINT_STR("-------- READ --------------------------");
		close(fd);
#define LIBASM
		errno = 0;
		fd = open("./Makefile", O_RDONLY);
		PRINT_INT(read_file(fd, 177));
		PRINT_INT(errno);
		PRINT_STR(strerror(errno));
		PRINT_STR(VERSION);
		PRINT_STR("----- FT_READ --------------------------");
		close(fd);
#undef LIBASM
	/*	size_t	len = 5;
		char	test_read[5] = {0};
		char	test_ft_read[5] = {0};

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
		PRINT_STR("----------------------------------------");*/
	//	free(dst);
#endif

#ifdef BONUS
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
