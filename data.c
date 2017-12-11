/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 15:01:21 by jblazy            #+#    #+#             */
/*   Updated: 2017/12/02 19:11:05 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	CALCULE LE X GRACE X_TMP, X_TMP CONTIENT LES INDEX DE CHAQUE HASHTAG, LA
**	FONCTION INCREMENT X A CHAQUE INDEX DIFFERENT
*/

static int		ft_calc_x(int x_tmp)
{
	int		x;
	int		tmp;
	int		i;
	int		flag;

	x = 0;
	i = 10;
	while (x_tmp)
	{
		flag = 0;
		tmp = x_tmp / 10;
		while (tmp)
		{
			if (x_tmp % 10 == tmp % 10 && !flag)
				flag = 1;
			tmp = tmp / 10;
		}
		if (!flag)
			x++;
		x_tmp = x_tmp / 10;
	}
	return (x);
}

/*
**	CREE LE TABLEAU DE CHAINES DE CARACTERES ET COPIE LE BUF DANS CE TABLEAU
*/

static char		**ft_alloc_and_set_tetri(char *buf, t_tetri *tetri)
{
	char	**tab;
	short	i;

	i = 0;
	if (!(tab = (char **)malloc(sizeof(char *) * tetri->y)))
		return ((char **)ft_freetab(&tab));
	while (i < tetri->y - 1)
	{
		while (!(ft_ishashtag(buf)))
			buf = buf + 5;
		if (!(tab[i] = (char *)malloc(sizeof(char) * (tetri->x + 1))))
			return ((char **)ft_freetab(&tab));
		ft_strncpy(tab[i], &buf[(int)tetri->first_x], tetri->x);
		tab[i][(int)tetri->x] = '\0';
		buf = buf + 5;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

/*
**	CALCULE LA HAUTEUR, LA LARGEUR ET L'INDEX
**	A PARTIR DUQUEL COMMENCE LA LARGEUR
*/

static void		ft_create_buf(t_tetri *tetri, char *buf)
{
	char	i;
	char	*buf_tmp;
	char	line;

	i = 0;
	line = 0;
	buf_tmp = buf;
	while (line < 4)
	{
		if (*buf_tmp == '#' && tetri->first_x > i)
			tetri->first_x = i;
		if (*buf_tmp == '#')
			tetri->x_tmp = tetri->x_tmp * 10 + i + 1;
		i++;
		if (*(buf_tmp++) == '\n')
		{
			line++;
			if (ft_ishashtag(buf_tmp - 5))
				tetri->y++;
			i = 0;
		}
	}
	tetri->x = ft_calc_x(tetri->x_tmp);
	tetri->buf = ft_alloc_and_set_tetri(buf, tetri);
}

/*
**	CREE UNE STRUCTURE T_TETRI ET L'INITIALISE
*/

static t_tetri	*ft_create_tetri(char *buf, char position, char total)
{
	t_tetri	*tetri;

	if (!(tetri = (t_tetri *)malloc(sizeof(t_tetri))))
		return ((t_tetri *)ft_freetetri(&tetri));
	tetri->position = position;
	tetri->y = 1;
	tetri->x = 0;
	tetri->x_tmp = 0;
	tetri->first_x = 10;
	tetri->total = total;
	ft_create_buf(tetri, buf);
	return (tetri);
}

/*
**	CREE LE TABLEAU DE STRUCTURE T_TETRI
*/

t_tetri			**ft_create_data(char *buf, short buf_size)
{
	short	i;
	char	len;
	char	*buf_tmp;
	t_tetri	**all_tetri;

	buf_tmp = buf;
	i = 0;
	while (*buf_tmp)
	{
		if (*buf_tmp == '\n' && *(buf_tmp + 1) == '\n')
			i++;
		buf_tmp++;
	}
	len = (buf_size - i) / 20;
	if (!(all_tetri = (t_tetri **)malloc(sizeof(t_tetri *) * (len + 1))))
		return ((t_tetri **)ft_freetetri(all_tetri));
	all_tetri[(short)len] = NULL;
	i = 0;
	while (i < len)
	{
		all_tetri[i] = ft_create_tetri(buf, (char)i, len);
		buf = buf + 21;
		i++;
	}
	return (all_tetri);
}
