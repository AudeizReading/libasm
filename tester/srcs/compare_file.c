#include "libasm_tester.h"

#ifdef	PHASE_TWO
static void		check_version(int idx_test, char* test_name, char *ft_line, char *reg_line) {
	char **first_line_ft = ft_split(ft_line, ':');
	char **first_line_reg = ft_split(reg_line, ':');

	assert(strcmp(first_line_reg[2], first_line_ft[2]) != 0);
	PRINT_RES(idx_test, test_name, OK, "\t%s%s.\n", first_line_ft[2], RESET);

	ft_free_char_array(first_line_ft);
	ft_free_char_array(first_line_reg);
}

int		compare_files(enum e_functions type_test, ...) {
	va_list		args;

	va_start(args, type_test);

	char	*reg_file = va_arg(args, char *);
	char	*ft_file = va_arg(args, char *);
	int		*idx_test = va_arg(args, int *);
	
	if (!reg_file || !ft_file)
		exit(1);

	char	*reg_content = read_file(reg_file);
	char	*ft_content = read_file(ft_file);
	char	**reg_lines = ft_split(reg_content, '\n');
	char	**ft_lines = ft_split(ft_content, '\n');

	switch (type_test) {
		case TEST_LEAKS: {
				if (strstr(ft_content, "All heap blocks were freed -- no leaks are possible") != NULL) {
					PRINT_RES(*idx_test, "FT - check LEAKS", OK, "\t%s\n", "No Leaks.");
				} else {
					PRINT_RES(*idx_test, "FT - check LEAKS", KO, "\n%s\n", strstr(ft_content, "LEAK SUMMARY") ? strstr(ft_content, "LEAK SUMMARY") : "It should find leaks...");
				}
			}
			break;
		case TEST_STRLEN: {
				check_version(*idx_test, "FT - check version STRLEN", ft_lines[0], reg_lines[0]);

				// __FILE__:__LINE__:idx_test:taille_chaine:valeur_chaine:
				for (int i = 1; ft_lines[i] && reg_lines[i]; i++) {
					char **line_ft = ft_split(ft_lines[i], ':');
					char **line_reg = ft_split(reg_lines[i], ':');
					
					(*idx_test)++;
					assert(strcmp(line_reg[2], line_ft[2]) == 0 && strcmp(line_reg[3], line_ft[3]) == 0 && strcmp(line_reg[3], line_ft[3]) == 0);
					PRINT_RES(*idx_test, "FT - check size STRLEN", OK, "\tFT: %-5s - REG: %-5s%s\n", line_ft[3], line_reg[3], RESET);

					ft_free_char_array(line_ft);
					ft_free_char_array(line_reg);
					if (!ft_lines[i + 1])
						printf("\n");
				}
			}
			break;
		case TEST_STRCPY: {
				check_version(*idx_test, "FT - check version STRCPY", ft_lines[0], reg_lines[0]);
				// __FILE__:__LINE__:idx_test:retour_strcpy:chaine_destination:chaine_source:
				for (int i = 1; ft_lines[i] && reg_lines[i]; i++) {
					char **line_ft = ft_split(ft_lines[i], ':');
					char **line_reg = ft_split(reg_lines[i], ':');
					
					int fields = 0;
					for (int i = 0; line_ft[i]; i++, fields++);
					(*idx_test)++;
					assert(strcmp(line_reg[2], line_ft[2]) == 0 
							&& (line_reg[3] && line_ft[3]) ? strcmp(line_reg[3], line_ft[3]) == 0 : line_reg[3] == NULL && line_ft[3] == NULL
							&& (line_reg[4] && line_ft[4]) ? strcmp(line_reg[4], line_ft[4]) == 0 : line_reg[4] == NULL && line_ft[4] == NULL
							&& (fields == 6 && line_reg[3] && line_ft[3]) ? strcmp(line_reg[5], line_ft[5]) == 0 : line_reg[3] == NULL && line_ft[3] == NULL
					);
					
					PRINT_RES(*idx_test, "FT - check value STRCPY", OK, "\tFT: [%-15.15s]\v- REG: [%-15.15s]%s\n", line_ft[3] ?  line_ft[3] : "NULL", line_reg[3] ?  line_reg[3] : "NULL", RESET);

					ft_free_char_array(line_ft);
					ft_free_char_array(line_reg);
					if (!ft_lines[i + 1])
						printf("\tContent may have been truncated for clarity. But the test is succeed if you can read this\n\n");
				}
			}
			break;
		case TEST_STRCMP: {
				check_version(*idx_test, "FT - check version STRCMP", ft_lines[0], reg_lines[0]);
			}
			break;
		case TEST_STRDUP: {
				check_version(*idx_test, "FT - check version STRDUP", ft_lines[0], reg_lines[0]);
			}
			break;
		case TEST_READ:
		case TEST_WRITE: {
				check_version(*idx_test, "FT - check version READ & WRITE", ft_lines[0], reg_lines[0]);
			}
			break;
#ifdef BONUS
		case TEST_ATOI_BASE: {
				check_version(*idx_test, "FT - check version ATOI BASE", ft_lines[0], reg_lines[0]);
			}
			break;
		case TEST_FT_LIST_PUSH_FRONT: {
				check_version(*idx_test, "FT - check version LIST PUSH FRONT", ft_lines[0], reg_lines[0]);
			}
			break;
		case TEST_FT_LIST_SIZE: {
				check_version(*idx_test, "FT - check version LIST SIZE", ft_lines[0], reg_lines[0]);
			}
			break;
		case TEST_FT_LIST_SORT: {
				check_version(*idx_test, "FT - check version LIST SORT", ft_lines[0], reg_lines[0]);
			}
			break;
		case TEST_FT_LIST_REMOVE_IF: {
				check_version(*idx_test, "FT - check version LIST REMOVE IF", ft_lines[0], reg_lines[0]);
			}
			break;
#endif
		default:
			break;
	}
	va_end(args);

	(*idx_test)++;
	free(reg_content);
	free(ft_content);
	ft_free_char_array(reg_lines);
	ft_free_char_array(ft_lines);
	return 0;
}
# endif //PHASE_TWO
