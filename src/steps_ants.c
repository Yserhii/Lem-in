/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   steps_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yserhii <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 17:54:13 by yserhii           #+#    #+#             */
/*   Updated: 2019/05/03 17:54:15 by yserhii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

void	make_mass(t_lem *lem)
{
	int		i;
	int		count;
	t_list	*list;
	t_room	*room;

	i = -1;
	list = lem->start->head;
	room = list->content;
	while (list && room->road == 0)
	{
		list = list->next;
		if (list)
			room = list->content;
	}
	lem->road = ft_lstcount(list);
	count = lem->road;
	lem->mass = ft_memalloc(sizeof(t_room) * count + 1);
	while (++i < count)
	{
		lem->mass[i] = room;
		list = list->next;
		if (list)
			room = list->content;
	}
	lem->mass[count] = NULL;
}

int		true_false(t_lem *lem, t_room *room, int i)
{
	int		lvl;

	lvl = 0;
	while (--i >= 0)
		lvl += room->lvl - lem->mass[i]->lvl;
	return (lem->ants > lvl ? 1 : 0);
}

void	step_by_step_add(t_room **mass, int i, t_lem *lem, t_room *room)
{
	char	*s;

	while (room->ant)
	{
		if (!ft_strcmp(room->name, lem->end->name))
		{
			ft_printf("%sL%d-%s{eoc}", s = co(i, lem), room->ant, room->name);
			mass[i]->count_ant--;
		}
		else
		{
			if (room != lem->start)
				room->parent->ant = room->ant;
			if (room != lem->start)
				ft_printf("%sL%d-%s{eoc}", s = co(i, lem),
										room->ant, room->name);
			else
				return ;
		}
		room->ant = 0;
		if (room->back->ant || (mass[i + 1] && mass[i + 1]->count_ant))
			ft_printf(" ");
		room = room->back;
		ft_strdel(&s);
	}
}

void	step_by_step(t_room **mass, int i, t_lem *lem)
{
	t_room *room;

	while (mass[++i])
	{
		room = mass[i];
		while (room && !room->ant)
			room = room->parent;
		while (room && room->parent && room->parent->ant)
			room = room->parent;
		if (mass[i]->count_ant > 0)
			step_by_step_add(mass, i, lem, room);
	}
	lem->count += ft_printf("\n");
}

void	steps_ants(t_lem *lem)
{
	int		ant;
	int		i;

	lem->start->head ? make_mass(lem) : 0;
	!lem->road ? exit(ft_printf("{red}Not roads{eoc}\n")) : 0;
	ft_printf("%s\n", lem->allmapread);
	make_add_end(lem);
	ant = 0;
	while (1)
	{
		i = -1;
		while (lem->mass[++i] && lem->ants)
		{
			if (true_false(lem, lem->mass[i], i))
			{
				lem->mass[i]->count_ant++;
				lem->mass[i]->ant = ++ant;
				lem->ants--;
			}
		}
		step_by_step(lem->mass, -1, lem);
		if (!lem->mass[0]->count_ant)
			break ;
	}
}
