/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suppr_elem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 13:59:00 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/18 18:29:59 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int			decrease_nb(t_line *buf)
{
	while (buf)
	{
		buf->nb -= 1;
		buf = buf->next;
	}
	return (0);
}

int					suppr_char_list(t_line **chaine)
{
	t_line		*buf;

	buf = *chaine;
	if (buf->select == 1 && buf->prev == NULL)
		return (0);
	while (buf && buf->next && buf->next->select == 0)
		buf = buf->next;
	decrease_nb(buf->next);
	if (buf->prev == NULL)
	{
		*chaine = buf->next;
		(*chaine)->prev = NULL;
	}
	else
	{
		buf->prev->next = buf->next;
		buf->next->prev = buf->prev;
	}
	free(buf);
	return (0);
}
