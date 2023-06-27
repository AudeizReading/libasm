#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FPRINTF(args...) fprintf(stdout, args);
#define PRINT_INT(x) FPRINTF("\033[31;1m%s:%d\033[0m\t%s = %d\n", __FILE__, __LINE__, #x, x)
#define PRINT_STR(x) FPRINTF("\033[33;1m%s:%d\033[0m\t%s = %s\n", __FILE__, __LINE__, #x, x)

extern int ft_strlen(const char *s);
extern char * ft_strcpy(char *dst, const char *src);

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

		free(dst);
		return 0;
	}
	return 1;
}
