/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_hist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 14:51:22 by dbaldy            #+#    #+#             */
/*   Updated: 2016/03/19 15:40:16 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int		init_debut(t_line **debut)
{
	if ((*debut = (t_line*)malloc(sizeof(t_line))) == NULL)
		return (-1);
	(*debut)->prev = NULL;
	(*debut)->next = NULL;
	(*debut)->c = ' ';
	(*debut)->select = 1;
	(*debut)->nb = 0;
	return (0);
}

static int		new_char_chaine(char n_c, t_line **chaine)
{
	t_line		*new;
	t_line		*buf;

	buf = *chaine;
	if ((new = (t_line*)malloc(sizeof(t_line))) == NULL)
		return (-1);
	while (buf->next && buf->select == 0)
		buf = buf->next;
	new->c = n_c;
	new->select = 0;
	new->next = buf;
	new->prev = buf->prev;
	buf->prev = new;
	new->nb = buf->nb;
	increase_nb(buf);
	if (new->prev != NULL)
		new->prev->next = new;
	*chaine = ((*chaine)->select == 1) ? new : *chaine;
	return (0);
}

static int		move_cursor_chaine(char direction, t_line **chaine)
{
	t_line		*buf;

	buf = *chaine;
	while (buf && buf->select == 0)
		buf = buf->next;
	buf->select -= 1;
	if (direction == 67 && buf->next != NULL)
		buf->next->select += 1;
	else if (direction == 68 && buf->prev != NULL)
		buf->prev->select += 1;
	else
		buf->select += 1;
	return (0);
}

static int		reprint_line(t_line *line, t_param *debut, int nb_row)
{
	ft_tputs("do", nb_row);
	ft_tputs("cd", 1);
	ft_putstr_fd("search file: ", get_fd(0));
	print_line(line);
	change_select(debut, line);
	ft_tputs("up", nb_row);
	ft_tputs("cr", 1);
	return (0);
}

int				manage_hist(char *buf, t_param *debut, int nb_row, int check)
{
	static t_line		*line;

	if (line == NULL)
		init_debut(&line);
	if (check == 2)
	{
		reset_select(debut);
		clear_tline(&line);
		return (0);
	}
	if (ft_strcmp(buf, "\x1a\x5b\x43") == 0 ||
			ft_strcmp(buf, "\x1a\x5b\x44") == 0)
		move_cursor_chaine(buf[2], &line);
	if (buf[0] > 32 && buf[0] <= 127 && buf[1] == 0)
	{
		if (buf[0] == 127)
			suppr_char_list(&line);
		else
			new_char_chaine(buf[0], &line);
	}
	reprint_line(line, debut, nb_row);
	if (buf[0] == 32 && buf[1] == 0)
		multi_select(debut, line);
	return (0);
}
