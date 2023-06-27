#include <stdio.h>
#include <string.h>

#define FPRINTF(args...) fprintf(stdout, args);
#define PRINT_INT(x) FPRINTF("\033[31;1m%s:%d\033[0m\t%s = %d\n", __FILE__, __LINE__, #x, x)

extern int ft_strlen(const char *s);

int main(int argc, char **argv) {

	if (argc == 2 ) {
		int len_strlen = strlen(argv[1]);
		int len_ft_strlen = ft_strlen(argv[1]);

		PRINT_INT(len_strlen);
		PRINT_INT(len_ft_strlen);
		return 0;
	}
	return 1;
}
