/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yserhii <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 13:39:50 by yserhii           #+#    #+#             */
/*   Updated: 2019/05/10 13:39:51 by yserhii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

void		ft_check_copy_link_add(t_list *list, t_room *room2, char *line)
{
	t_room	*tmp;

	while (list)
	{
		tmp = list->content;
		if (!ft_strcmp(tmp->name, room2->name))
		{
			ft_strdel(&line);
			exit(ft_printf("{red}Bad links{eoc}\n"));
		}
		list = list->next;
	}
}

void		ft_check_copy_link(t_list *head, t_room *room1,
												t_room *room2, char *line)
{
	t_room		*tmp;
	t_list		*list;
	int			i;

	i = 0;
	while (head)
	{
		tmp = head->content;
		if (room1 == tmp || room2 == tmp)
			i++;
		if (room1 == room2)
		{
			ft_strdel(&line);
			exit(ft_printf("{red}Bad links{eoc}\n"));
		}
		if (room1 == tmp)
		{
			list = tmp->head;
			ft_check_copy_link_add(list, room2, line);
		}
		head = head->next;
	}
}

static void	bonus_add(t_lem *lem)
{
	int		i;
	char	*s;
	t_room	*room;

	i = 0;
	while (lem->mass[i])
	{
		room = lem->mass[i];
		ft_printf("%sRoad[%d]:  ", s = co(i, lem), i + 1);
		while (room && room->parent && room->parent != lem->end)
		{
			ft_printf("[%s]->", room->name);
			room = room->parent;
		}
		ft_printf("[%s]{eoc}\n", lem->end->name);
		ft_strdel(&s);
		i++;
	}
	ft_printf("\n{green}My steps = [%d]{eoc}\n", lem->count);
}

void		bonus(t_lem *lem)
{
	if (lem->bonus)
	{
		ft_printf("\n");
		if (!lem->start_end)
			bonus_add(lem);
		else
		{
			ft_printf("{yellow}Road[1]:  ");
			ft_printf("[%s]->[%s]{eoc}\n", lem->start->name, lem->end->name);
			ft_printf("\n{green}My steps = [1]{eoc}\n");
		}
	}
}
