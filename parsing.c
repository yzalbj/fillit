/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 12:29:52 by jblazy            #+#    #+#             */
/*   Updated: 2017/12/02 19:08:21 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
**	CHECK UNE PIECE, LES CHARS, LA LONGUEUR DE LA LIGNE
*/

static int		ft_checkpiece(char *buf, short index)
{
	short	tmp;
	char	check_line;

	check_line = 0;
	tmp = index + 19;
	while (index < tmp)
	{
		if (buf[index] != '.' && buf[index] != '#')
		{
			return (-1);
		}
		if (buf[index + 1] == '\n' && check_line == 3)
		{
			index++;
			check_line = 0;
		}
		else
			check_line++;
		if (check_line > 3)
		{
			return (-1);
		}
		index++;
	}
	return (1);
}

static int		ft_checkconnec(char *buf, short index, short tmp)
{
	char	connection_nbr;

	connection_nbr = 0;
	if (index < tmp + 19 && buf[index + 1] == '#')
		connection_nbr++;
	if (index > tmp + 0 && buf[index - 1] == '#')
		connection_nbr++;
	if (index < tmp + 15 && buf[index + 5] == '#')
		connection_nbr++;
	if (index > tmp + 4 && buf[index - 5] == '#')
		connection_nbr++;
	return (connection_nbr);
}

/*
**	CHECK LES TETRIMINOS DANS UNE PIECE
*/

static int		ft_checktetri(char *buf, short index)
{
	short	tmp;
	char	count_hashtag;
	char	connection_nbr;

	tmp = index;
	count_hashtag = 0;
	connection_nbr = 0;
	while (index < tmp + 19)
	{
		if (buf[index] == '#')
			count_hashtag++;
		if (count_hashtag <= 4 && buf[index] == '#')
			connection_nbr = connection_nbr + ft_checkconnec(buf, index, tmp);
		if (count_hashtag > 4)
			return (-1);
		index++;
	}
	if (count_hashtag != 4 || connection_nbr < 6)
		return (-1);
	return (1);
}

/*
**	LANCE LE PARSING, CHECK LE NOMBRE DE PIECES, SI YA UN \n en fin de fichier
*/

int				ft_parsing(char *buf, short buf_size)
{
	short	index;

	index = 0;
	if (buf_size > BUFF_MAX || buf_size < 20)
		return (-1);
	while (buf[index])
	{
		if ((ft_checkpiece(buf, index) == -1))
			return (-1);
		if ((ft_checktetri(buf, index) == -1))
			return (-1);
		index = index + 20;
		if (buf[index] == '\n' && index == buf_size - 1)
			return (-1);
		index++;
	}
	return (1);
}
