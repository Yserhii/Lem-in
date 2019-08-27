/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yserhii <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 10:39:21 by yserhii           #+#    #+#             */
/*   Updated: 2019/04/24 10:39:23 by yserhii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

int		check_start(t_list *list, t_lem *lem)
{
	t_room *room;

	while (list)
	{
		room = list->content;
		if (room == lem->start)
			return (1);
		list = list->next;
	}
	return (0);
}

int		bfs_next_add(int n, t_lem *lem, t_room *room, t_list *alllist)
{
	t_list	*list;

	lem->flag_end = 0;
	list = room->head;
	while (list)
	{
		room = list->content;
		if (list->content != lem->end &&
			list->content != lem->start &&
			room->lvl == 0 && room->road == 0)
		{
			room->lvl = n;
			room->parent = alllist->content;
			if (check_start(room->head, lem) == 1)
				return (1);
		}
		else
			list = list->next;
	}
	return (0);
}

void	bfs_next(t_list *alllist, t_lem *lem, int n)
{
	t_room	*room;

	if (lem->flag_end == 0)
	{
		lem->flag_end = 1;
		while (alllist)
		{
			room = alllist->content;
			if (room->lvl == n - 1 && room->road == 0)
				if (bfs_next_add(n, lem, room, alllist))
					return ;
			alllist = alllist->next;
		}
		bfs_next(lem->head, lem, ++n);
	}
}

void	bfs(t_list *list, t_lem *lem, int n)
{
	t_room	*room;

	while (list)
	{
		room = list->content;
		if (list->content != lem->start &&
			list->content != lem->end &&
			room->road == 0)
		{
			room->lvl = n;
			room->parent = lem->end;
		}
		list = list->next;
	}
	bfs_next(lem->head, lem, ++n);
}

void	search_ways(t_lem *lem)
{
	int		c;

	c = 1;
	lem->numroad = ft_lstcount(lem->start->head);
	while (c <= lem->numroad)
	{
		bfs(lem->end->head, lem, 1);
		save_way(lem->start->head, lem, c);
		clear_node(lem->head, lem);
		sorting_way_for_up(lem);
		c++;
	}
}
