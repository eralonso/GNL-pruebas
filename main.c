/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 23:21:41 by eralonso          #+#    #+#             */
/*   Updated: 2022/11/10 12:47:22 by eralonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"get_next_line_bonus.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<fcntl.h>
#include	<unistd.h>
#include	<limits.h>

void	ft_memset(void *s, int c, int len)
{
	int	*arr;
	int	i;

	arr = (int *)s;
	i = 0;
	while (len-- > 0)
	{
		arr[i] = c;
		i++;
	}
}

int	ft_numdig(int *cls, int i)
{
	int	j;

	j = 0;
	while (j <= (i + 1))
	{
		if (cls[j] == i)
			return (1);
		j++;
	}
	return (0);
}

int	ft_strexist(char **str, int nfl)
{
	int	i;

	i = 0;
	while (nfl >= 0)
	{
		if (str[nfl])
			return (1);
		nfl--;
	}
	return (0);
}

int	ft_strncmp(char *s1, char *s2)
{
	if (!s1 && !s2)
		return (1);
	if (!s1 || !s2)
		return (0);
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 == *s2);
}

int	main(int ac, char **av)
{
	int		i;
	int		j;
	int		*cls;
	int		fd[OPEN_MAX];
	char	*str[OPEN_MAX];
	char	*files[OPEN_MAX];
	int		nfl;

	if (ac < 3)
	{
		printf("El número de parámetros és incorrecto\n");
		return (0);
	}
	if (ft_strncmp(av[1], "mandatory"))
	{
		i = -1;
		while (av[++i + 2])
			files[i] = av[i + 2];
		i = -1;
		while (files[++i])
		{
			j = 1;
			fd[0] = open(files[i], O_RDONLY);
			if (fd[0] == -1)
			{
				printf("\033[1;31mHa habido un problema a la hora de abrir el archivo.\nCompruebe que el archivo pasado está correcto.\n\033[0m");
				return (0);
			}
			printf("\033[1;32m\n%s\n\n\033[0m", files[i]);
			str[0] = get_next_line(fd[0]);
			while (str[0] && *(str[0]))
			{
				printf("\tline %i: %s", j, str[0]);
				if (!ft_strchr(str[0], '\n'))
					printf("\n");
				str[0] = get_next_line(fd[0]);
				j++;
			}
			printf("\tline %i: %s\n", j, str[0]);
			close(fd[0]);
		}
	}
	else if (ft_strncmp(av[1], "bonus"))
	{
		cls = (int *)malloc(sizeof(int) * (OPEN_MAX + 1));
		if (!cls)
			return (-1);
		ft_memset(cls, -1, OPEN_MAX);
		nfl = 0;
		i = 1;
		while (av[++i])
		{
			files[nfl] = av[i];
			fd[nfl] = open(files[nfl], O_RDONLY);
			str[nfl] = get_next_line(fd[nfl]);
			nfl++;
		}
		nfl--;
		j = 0;
		while (ft_strexist(str, nfl))
		{
			i = 0;
			while (i <= nfl)
			{
				if (!str[i] && !ft_numdig(cls, i))
				{
					printf("\033[1;32m\n%s: \033[0m", files[i]);
					printf("%s\n", str[i]);
					cls[j++] = i;
				}
				if (!ft_numdig(cls, i))
				{
					printf("\033[1;32m\n%s: \033[0m%s", files[i], str[i]);
					if (!ft_strchr(str[i], '\n'))
						printf("\n");
					str[i] = get_next_line(fd[i]);
					if (!ft_strexist(str, nfl))
						printf("\033[1;32m\n%s: \033[0m%s", files[i], str[i]);
				}
				i++;
			}
		}
		i = 0;
		while (i <= nfl)
		{
			close(fd[i]);
			i++;
		}
	}
	else
		printf("\033[1;31m\nEl formato especificado no es correcto. Pruebe con uno de los formatos siguientes:\033[0m\n\t\033[1;33m1.mandatory\n\t2.bonus\n\033[0m");
	return (0);
}
