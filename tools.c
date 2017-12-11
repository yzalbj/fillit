/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 13:34:03 by jblazy            #+#    #+#             */
/*   Updated: 2017/12/02 19:20:15 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	REGARDE SI IL Y A UN DIESE SUR LA LIGNE DU TETRIMINOS
*/

int		ft_ishashtag(char *buf)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		if (buf[i] == '#')
			return (1);
		i++;
	}
	return (0);
}

/*
**	FREE LE TABLEAU DE CHAINES DE CARACTERES
*/

void	*ft_freetab(char ***tab)
{
	int		i;

	i = 0;
	while ((*tab)[i])
	{
		free((*tab)[i]);
		(*tab)[i] = NULL;
		i++;
	}
	free(*tab);
	*tab = NULL;
	return (NULL);
}

/*
**	FREE TOUS LES TETRIS
*/

void	*ft_freetetri(t_tetri **tetri)
{
	int		i;
	int		size;

	i = 0;
	size = (*tetri)->total;
	while (i < size)
	{
		if ((tetri[i])->buf)
			ft_freetab(&((tetri[i])->buf));
		free(tetri[i]);
		tetri[i] = NULL;
		i++;
	}
	free(tetri);
	tetri = NULL;
	return (NULL);
}

/*
** CRER LE TABLEAU A LA TAILLE DU PREMIER TETRI PUIS APPEL LE BACKTRACKING
*/

char	**ft_create_tab(t_tetri **tetri)
{
	char	**tab;
	int		size;
	int		i;

	i = 0;
	size = ((*tetri)->x > (*tetri)->y - 1) ? (*tetri)->x : (*tetri)->y - 1;
	if (!(tab = (char **)malloc(sizeof(char *) * (size + 1))))
		return ((char **)ft_freetab(&tab));
	tab[size] = NULL;
	while (i < size)
	{
		if (!(tab[i] = (char *)malloc(sizeof(char) * size + 1)))
			return ((char **)ft_freetab(&tab));
		ft_memset((char *)tab[i], '.', size);
		tab[i][size] = '\0';
		i++;
	}
	ft_resolve(&tab, tetri, 0, 0);
	return (tab);
}
