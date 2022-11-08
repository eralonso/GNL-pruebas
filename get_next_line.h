/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 19:49:22 by eralonso          #+#    #+#             */
/*   Updated: 2022/11/08 01:36:38 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include	<unistd.h>
# include	<stdlib.h>
# include	<limits.h>

typedef struct s_data {
	char	*buffer;
	char	*line;
	int		fd;
	int		err;
}			t_data;

void	ft_read_file(t_data *data);
void	ft_get_line(t_data *data);
void	ft_clean_buffer(t_data *data);
char	*get_next_line(int fd);
void	*ft_free(char **str);
int		ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *str);
char	*ft_strchr(char *str, char c);
char	*ft_substr(char *s, int start, int len);

#endif
