/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 19:53:04 by jblazy            #+#    #+#             */
/*   Updated: 2017/11/15 14:43:09 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstadd(t_list **alst, t_list *new)
{
	if (!new || !alst)
		return (NULL);
	new->next = *alst;
	*alst = new;
	return (*alst);
}