/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:29:28 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/01/05 13:25:08 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_var
{
	char	*temp_read;
	char	*temp_save;
	char	*new_to_save;
	int		newline_index;
	int		bytes_read;
	char	*line;
	char	*start;
}			t_variable;

char		*get_next_line(int fd);
char		*ft_separator(t_variable *v, char **to_save);
void		free_all(char **s, char **s1);
char		*ft_strjoin(char *s1, char *s2);
size_t		ft_strlen(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strdup(const char *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);

#endif