/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 13:59:46 by jblazy            #+#    #+#             */
/*   Updated: 2017/12/02 18:19:16 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	ft_display(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_putendl(tab[i]);
		i++;
	}
}

void	ft_fillit(short fd)
{
	short		buf_size;
	char		buf[BUFF_MAX];
	char		**tab;
	t_tetri		**all_tetri;

	ft_bzero(buf, BUFF_MAX);
	buf_size = read(fd, buf, BUFF_MAX);
	buf[BUFF_MAX - 1] = '\0';
	if (ft_parsing(buf, buf_size) == -1)
	{
		ft_putendl("error");
		return ;
	}
	all_tetri = ft_create_data(buf, buf_size);
	tab = ft_create_tab(all_tetri);
	ft_display(tab);
	ft_freetab(&tab);
	ft_freetetri(all_tetri);
}

int		main(int argc, char **argv)
{
	short		fd;

	if (argc != 2)
	{
		ft_putendl("usage: ./fillit [valid fillit_file to resolve]");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	ft_fillit(fd);
	close(fd);
	return (0);
}
