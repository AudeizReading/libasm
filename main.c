#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FPRINTF(args...) fprintf(stdout, args);
#define PRINT_INT(x) FPRINTF("\033[31;1m%s:%d\033[0m\t%-60s =\t%d\n", __FILE__, __LINE__, #x, x)
#define PRINT_STR(x) FPRINTF("\033[33;1m%s:%d\033[0m\t%-60s =\t%s\n", __FILE__, __LINE__, #x, x)

extern size_t ft_strlen(const char *s);
extern char *ft_strcpy(char *dst, const char *src);
extern int	ft_strcmp(const char *s1, const char *s2);
extern char *ft_strdup(const char *s);

int main(int argc, char **argv) {

	if (argc == 2 ) {
		/* ft_strlen - strlen comparison */
		int len_ft_strlen = ft_strlen(argv[1]);

		PRINT_INT((int)strlen(argv[1]));
		PRINT_INT((int)ft_strlen(argv[1]));

		/* ft_strcpy - strcpy comparison */
		char *dst = calloc(sizeof(char *), len_ft_strlen + 1);

		PRINT_STR(strcpy(dst, argv[1]));
		PRINT_STR(dst);
		PRINT_STR(ft_strcpy(dst, argv[1]));
		PRINT_STR(dst);

		/* ft_strcmp - strcmp comparison */
		PRINT_INT(strcmp(argv[1], dst));
		PRINT_INT(ft_strcmp(argv[1], dst));
		PRINT_INT(strcmp(dst, &argv[1][2]));
		PRINT_INT(ft_strcmp(dst, &argv[1][2]));
		PRINT_INT(strcmp(&argv[1][1], dst));
		PRINT_INT(ft_strcmp(&argv[1][1], dst));

		/* ft_strdup - strdup comparison */
		char *dup_base = strdup(argv[1]);
		char *dup_ft = ft_strdup(argv[1]);

		PRINT_STR(dup_base);
		PRINT_STR(dup_ft);

		free(dup_base);
		free(dup_ft);
		free(dst);
		return 0;
	}
	return 1;
}
