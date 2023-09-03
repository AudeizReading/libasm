#include "libasm_tester.h"

static char	*ft_substr(char const *s, unsigned int start, size_t len) {
	char	*dst = NULL;
	size_t	len_s = 0;

	if (!s)
		return NULL;

	while (s[len_s++]) ;
	if (len > len_s || (len + start > len_s && start < len_s))
		len = len_s - start;
	if (start >= len_s)
		len = 0;
	dst = (char *)calloc((len + 1), sizeof(*dst));
	if (!dst)
		return NULL;
	memcpy(dst, s + start, len);
	return dst;
}

static char	*ft_slice(char const *s, char c, int *j) {
	int		i = 0;
	char	*dst = NULL;;

	while (s[i] && s[i] != c)
		i++;
	dst = ft_substr(s, 0, i);
	if (!dst)
		return NULL;
	while (s[i] && s[i] == c)
		i++;
	*j += i;
	return dst;
}

static int	ft_is_in_charset(int c, char const *charset) {
	while (*charset) {
		if (c == *charset++)
			return 1;
	}
	return 0;
}

static int	get_nb_token(char const *str, int sep) {
	int		nb = 0;
	enum	e_state {
		OUTSIDE_TOKEN,
		INSIDE_TOKEN
	};
	int		state = OUTSIDE_TOKEN;

	while (*str) {
		if (ft_is_in_charset(*str, (char const *)&sep))
			state = OUTSIDE_TOKEN;
		else if (state == OUTSIDE_TOKEN) {
			state = INSIDE_TOKEN;
			nb++;
		}
		str++;
	}
	return nb;
}

char		**ft_split(char const *s, char c) {
	if (!s)
		return 0;

	int		nb_token = get_nb_token(s, (int)c);
	int		i = -1;
	int		j = 0;
	char	**dst = (char **)calloc(nb_token + 1, sizeof(*dst));
	if (!dst)
		return NULL;
	while (s[j] && s[j] == c)
		j++;
	while (++i < nb_token) {
		dst[i] = ft_slice((s + j), c, &j);
		if (!dst[i]) {
			while (--i >= 0)
				free(dst[i]);
			free(dst);
			return NULL;
		}
	}
	return dst;
}
/*char							**split(char *src, char c) {

	//(void)c;
	char	**vals = NULL;
	int		*pos = NULL;
	char	*to_split = STRDUP(src);
	unsigned int		nb_token = 0;
	//int
	for (unsigned int i = 0; i < STRLEN(to_split); ++i) {
		while (to_split[i] && to_split[i] != c) {
			i++;
		}
		nb_token++;
		if (i > STRLEN(to_split) - 1)
			break;
		while (to_split[i] && to_split[i] == c) {
			i++;
			nb_token++;
		}
		if (i > STRLEN(to_split) - 1)
			break;
		if (i == STRLEN(to_split) - 1 && to_split[i] != c)
			nb_token++;
		//BONUS_INT(nb_token);
		//BONUS_INT(i);
		//PRINT_STR("=====");
	}
	BONUS_INT(nb_token);
	PRINT_STR("*****");
	//BONUS_STR(src);
	vals = malloc(sizeof(char *) * (nb_token + 1));
	vals[nb_token] = 0;
	pos = malloc(sizeof(int) * nb_token);

	unsigned int j = 0;
	for (unsigned int i = 0; i < STRLEN(to_split); ++i) {
		if ((to_split[i] == c || i == 0) && j < nb_token) {
			if (i == 0) {
				pos[j++] = i;
			} else if (to_split[i + 1] && j < nb_token){
				pos[j++] = i + 1;
			}
		}
	}

	unsigned int	size_token = 0;
	for (unsigned int i = 0; i < nb_token; ++i) {
		if (&pos[i] && pos[i + 1] && i < nb_token - 1) {
		//				BONUS_INT(pos[i]);
		//				BONUS_STR(&to_split[pos[i]]);
		//				BONUS_INT(pos[i + 1]);
			size_token = pos[i + 1] - pos[i] - 1;
		//				BONUS_INT(size_token);
		}
		else if (&pos[i] != NULL) {
			size_token = STRLEN(to_split) - pos[i];
		}
		else if (pos[i] == c) {
			size_token = 1;
		}
		else {
			size_token = 0;
		}
		vals[i] = malloc(sizeof(char) * size_token + 1);
		vals[i][size_token] = 0;
		for (unsigned int k = 0; k < size_token ; k++) {
			vals[i][k] = to_split[(int)(pos[i] + k)];
		}
		BONUS_INT(i);
		BONUS_STR("[");
		BONUS_STR(vals[i]);
		BONUS_STR("]");
	}

	free(pos);
	free(to_split);
	return vals;
}*/
