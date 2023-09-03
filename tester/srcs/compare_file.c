#include "libasm_tester.h"

int		compare_files(char *filename1, char *filename2) {
	if (!filename1 || !filename2)
		exit(1);

	char	*content_file1 = read_file(filename1);
	char	*content_file2 = read_file(filename2);
	char	**lines_file1 = ft_split(content_file1, '\n');
	char	**lines_file2 = ft_split(content_file2, '\n');

	PRINT_TEST(1, "REG:[%s%s%s]\nFT[%s%s%s]\n", BLUE, content_file1, RESET, BLUE_ALT, content_file2, RESET);
	free(content_file1);
	free(content_file2);
	for (int i = 0; lines_file1[i]; i++, free(lines_file1[i]));
	free(lines_file1);
	for (int i = 0; lines_file2[i]; i++, free(lines_file2[i]));
	free(lines_file2);
	return 0;
}
