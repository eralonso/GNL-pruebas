/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eralonso <eralonso@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 23:21:41 by eralonso          #+#    #+#             */
/*   Updated: 2022/11/08 19:34:47 by eralonso         ###   ########.fr       */
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

int	ft_intdig(int *cls, int i)
{
	int	j;

	j = 0;
	while (cls[j])
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
			printf("\033[1;32m\n%s\n\n\033[0m", files[i]);
			fd[0] = open(files[i], O_RDONLY);
			str[0] = get_next_line(fd[0]);
			while (str[0] && *(str[0]))
			{
				printf("\tget_next_line == %s", str[0]);
				str[0] = get_next_line(fd[0]);
			}
			printf("\tget_next_line == %s\n", str[0]);
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
			printf("fd[%i] == %i\n", nfl, fd[nfl]);
			str[nfl] = get_next_line(fd[nfl]);
			nfl++;
		}
		nfl--;
		j = 0;
		printf("str[%i] == %s\n", 0, str[0]);
		printf("str[%i] == %s\n", 1, str[1]);
		while (ft_strexist(str, nfl))
		{
			i = 0;
			while (i <= nfl)
			{
				if (ft_intdig(cls, i) && str[i])
				{
					printf("\033[1;32m\n\n%s:\033[0m", files[i]);
					printf("%s", str[i]);
					str[i] = get_next_line(fd[i]);
				}
				if (!str[i])
				{
					printf("\n2\n");
					cls[j++] = i;
					close(fd[i]);
				}
				i++;
			}
		}
	}
	else
		printf("\033[1;31m\nEl formato especificado no es correcto. Pruebe con uno de los formatos siguientes:\n\t1.mandatory\n\t2.bonus\n");
	return (0);
}
