/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 15:40:53 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/19 15:40:30 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int			reset_select(t_param *debut)
{
	t_param *buf;

	buf = debut->next;
	debut->select = (debut->select % 2 == 1) ? debut->select :
		debut->select + 1;
	while (buf->nb != 0)
	{
		buf->select = ((buf->select % 2) == 1) ? buf->select - 1 :
			buf->select;
		buf = buf->next;
	}
	return (0);
}

int			clear_tline(t_line **elem)
{
	t_line	*buf;
	t_line	*a;

	buf = *elem;
	if (buf->prev != NULL)
		buf->prev->next = NULL;
	while (buf)
	{
		a = buf->next;
		buf->next = NULL;
		buf->prev = NULL;
		free(buf);
		buf = a;
	}
	*elem = NULL;
	return (0);
}

int			increase_nb(t_line *buf)
{
	while (buf)
	{
		buf->nb += 1;
		buf = buf->next;
	}
	return (0);
}
