/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_and_eff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yserhii <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 14:31:16 by yserhii           #+#    #+#             */
/*   Updated: 2019/04/26 14:31:18 by yserhii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

void		sorting_way_for_up(t_lem *lem)
{
	t_list	*tmp;
	t_list	*list;
	t_room	*room;
	t_room	*room_next;

	list = lem->start->head;
	tmp = ft_memalloc(sizeof(t_list));
	while (list && list->next)
	{
		room = list->content;
		room_next = list->next->content;
		if (room->road > room_next->road)
		{
			tmp->content = list->content;
			list->content = list->next->content;
			list->next->content = tmp->content;
			list = lem->start->head;
		}
		else
			list = list->next;
	}
	free(tmp);
	tmp = NULL;
}

void		clear_node(t_list *list, t_lem *lem)
{
	t_room	*room;

	lem->flag_end = 0;
	while (list)
	{
		room = list->content;
		if (room->road == 0)
		{
			room->lvl = 0;
			room->parent = NULL;
			room->back = NULL;
		}
		list = list->next;
	}
}

void		save_way(t_list *head, t_lem *lem, int c)
{
	t_room	*room;

	while (head)
	{
		room = head->content;
		if (room->parent && room->road == 0)
		{
			room->back = lem->start;
			while (room != lem->end)
			{
				if (room->parent != lem->end)
					room->parent->back = room;
				room->road = c;
				room = room->parent;
			}
			return ;
		}
		head = head->next;
	}
}

void		ft_ants(char *line, t_lem *lem)
{
	if (line)
	{
		if (ft_allnum(line) == 0)
			lem->ants = ft_atoi(line);
		else
		{
			ft_strdel(&line);
			exit(ft_printf("{red}No ants{eoc}\n"));
		}
		if (lem->ants == 0)
		{
			ft_strdel(&line);
			exit(ft_printf("{red}No ants{eoc}\n"));
		}
	}
	else
	{
		ft_strdel(&line);
		exit(ft_printf("{red}No ants{eoc}\n"));
	}
}

void		make_add_end(t_lem *lem)
{
	int		i;
	t_room	*room;

	i = 0;
	while (lem->mass[i])
	{
		room = lem->mass[i];
		while (room->parent != lem->end)
			room = room->parent;
		room->parent = ft_memalloc(sizeof(t_room));
		room->parent->ant = lem->end->ant;
		room->parent->back = room;
		room->parent->count_ant = lem->end->count_ant;
		room->parent->head = lem->end->head;
		room->parent->lvl = lem->end->lvl;
		room->parent->name = lem->end->name;
		room->parent->parent = NULL;
		room->parent->road = lem->end->road;
		room->parent->x = lem->end->x;
		room->parent->y = lem->end->y;
		i++;
	}
}
