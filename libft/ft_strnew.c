/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:22:27 by jblazy            #+#    #+#             */
/*   Updated: 2017/11/13 12:26:43 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *str;

	if ((str = (char *)malloc(sizeof(char) * size + 1)) == NULL)
		return (NULL);
	ft_bzero(str, size + 1);
	return (str);
}
