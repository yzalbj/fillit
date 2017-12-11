/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 12:31:07 by jblazy            #+#    #+#             */
/*   Updated: 2017/12/04 11:15:50 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# define BUFF_MAX 545

# include "./libft/libft.h"
# include <fcntl.h>

typedef	struct	s_tetri
{
	char	**buf;
	char	position;
	char	x;
	short	x_tmp;
	char	first_x;
	char	y;
	char	total;
}				t_tetri;

/*
**	PARSING.C
*/

int				ft_parsing(char *buf, short buf_size);

/*
**	RESOLVE.C
*/

int				ft_resolve(char ***tab, t_tetri **tetri, int x, int y);

/*
**	TOOLS.C
*/

int				ft_ishashtag(char *buf);
void			*ft_freetab(char ***tab);
void			*ft_freetetri(t_tetri **tetri);
char			**ft_create_tab(t_tetri **tetri);

/*
**	DATA.C
*/

t_tetri			**ft_create_data(char *buf, short buf_size);
#endif
