/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 17:06:36 by jblazy            #+#    #+#             */
/*   Updated: 2017/12/02 19:17:28 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	REALLOC LE TAB DE +1 A CHAQUE FOIS QUE LE PREMIER TETRI SE RETROUVE A LA FIN
**	DU TAB
*/

static char	**ft_realloc_tab(char **tab)
{
	char	**new_tab;
	int		i;
	int		size;

	size = ft_strlen(tab[0]);
	i = 0;
	if (!(new_tab = (char **)malloc(sizeof(char *) * (size + 2))))
		return ((char **)ft_freetab(&tab));
	new_tab[size + 1] = NULL;
	while (i < size + 1)
	{
		if (!(new_tab[i] = (char *)malloc(sizeof(char) * (size + 2))))
			return ((char **)ft_freetab(&tab));
		if (i < size)
		{
			ft_strcpy(new_tab[i], tab[i]);
			new_tab[i][size] = '.';
		}
		else
			ft_memset((char *)new_tab[i], '.', size + 1);
		new_tab[i++][size + 1] = '\0';
	}
	ft_freetab(&tab);
	return (new_tab);
}

/*
**	CHECK SI SUR UNE CASE DU TABLEAU LA PIECE DE TETRI PEUT S'Y METTRE
*/

static int	ft_isplacefree(char **tab, t_tetri *tetri, int x_tab, int y_tab)
{
	int		i;
	int		x;
	int		x_tab_tmp;
	char	**buf;

	i = 0;
	buf = tetri->buf;
	while (i < tetri->y - 1)
	{
		x = 0;
		x_tab_tmp = x_tab;
		while (x < tetri->x)
		{
			if (!tab[y_tab] || !tab[y_tab][x_tab_tmp] ||
					(tab[y_tab][x_tab_tmp] != '.' && (*buf)[x] == '#'))
				return (0);
			x_tab_tmp++;
			x++;
		}
		buf++;
		i++;
		y_tab++;
	}
	return (1);
}

/*
**	PLACE LA PIECE DE TETRI SUR LA CASE DU TABLEAU INDIQUEE
*/

static void	ft_place_piece(char **tab, t_tetri *tetri, int x_tab, int y_tab)
{
	int		x;
	int		x_tab_tmp;
	int		i;
	char	**buf;

	x = 0;
	i = 0;
	buf = tetri->buf;
	while (i < tetri->y - 1)
	{
		x = 0;
		x_tab_tmp = x_tab;
		while (x < tetri->x)
		{
			if ((*buf)[x] == '#')
				tab[y_tab][x_tab_tmp] = tetri->position + 65;
			x++;
			x_tab_tmp++;
		}
		buf++;
		y_tab++;
		i++;
	}
}

/*
**	REMPLACE LA PIECE INDIQUEE PAR DES POINTS
*/

static void	ft_delete_piece(char **tab, t_tetri *tetri)
{
	int		x;
	int		y;

	y = 0;
	while (tab[y])
	{
		x = 0;
		while (tab[y][x])
		{
			if (tab[y][x] == tetri->position + 65)
				tab[y][x] = '.';
			x++;
		}
		y++;
	}
}

/*
**	LA FONCTION REGARDE POUR CHAQUE CASE DU TABLEAU SI LE TETRI PEUT S'Y METTRE,
**	SI C'EST LE CAS ON LA PLACE ET ON PASSE AU SUIVANT, SINON ON REVIENT AU
**	PRECEDENT POUR LE DEPLACER DE 1, SI LE PREMIER TETRI EST A LA FIN DU TABLEAU
**	ON REALLOC LE TAB DE 1, SI TOUS LES TETRIS ONT ETE PLACES, L'ALGO EST FINI
*/

int			ft_resolve(char ***tab, t_tetri **tetri, int x, int y)
{
	if (!(*tetri))
		return (1);
	while ((*tab)[y])
	{
		if (ft_isplacefree(*tab, *tetri, x, y))
		{
			ft_place_piece(*tab, *tetri, x, y);
			if (ft_resolve(tab, tetri + 1, 0, 0) == 1)
				return (1);
			ft_delete_piece(*tab, *tetri);
		}
		if (!(*tab)[y][x])
		{
			y++;
			x = 0;
			if (!(*tab)[y] && (*tetri)->position == 0)
			{
				*tab = ft_realloc_tab(*tab);
				y = 0;
			}
		}
		else
			x++;
	}
	return (0);
}
