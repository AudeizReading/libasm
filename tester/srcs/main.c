#include "libasm_tester.h"

int main(int argc, char **argv) {

#ifdef	PHASE_ONE
	if (argc == 2 ) {

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
		
		select_test(TEST_STRLEN, strings_to_test);

		select_test(TEST_STRCPY, strings_to_test);
		
		select_test(TEST_STRCMP, strings_to_test, strings_to_cmp);

		select_test(TEST_STRDUP, strings_to_cmp);

		select_test(TEST_WRITE, FILE_TEST_WRITE);
# ifdef BONUS
		select_test(TEST_ATOI_BASE);

		t_list	*begin = NULL;

		select_test(TEST_FT_LIST_PUSH_FRONT, &begin, argv[1]);

		select_test(TEST_FT_LIST_SIZE, &begin);

		select_test(TEST_FT_LIST_SORT, &begin, argv[1]);

		select_test(TEST_FT_LIST_REMOVE_IF, &begin);

# endif
		return 0;
	}
#endif
#ifdef	PHASE_TWO
	if (argc == 1) {
		(void)argv;
		char *title = read_file(FILE_TITLE);
		PRINT_TEST(1, "%s\t%s\n", title, EXPAND_STRINGIFY(title));

		compare_files(REG_STRLEN, FT_STRLEN);
		free(title);
		return 0;
	}
#endif
	return 1;
}
