/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yserhii <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 16:21:51 by yserhii           #+#    #+#             */
/*   Updated: 2019/04/22 16:21:53 by yserhii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

char	*co(int i, t_lem *lem)
{
	if (lem->bonus)
	{
		if (i == 1)
			return (ft_strdup("\e[31m"));
		if (i == 2)
			return (ft_strdup("\e[32m"));
		if (i == 3)
			return (ft_strdup("\e[33m"));
		if (i == 4)
			return (ft_strdup("\e[34m"));
		if (i == 5)
			return (ft_strdup("\e[35m"));
		if (i == 6)
			return (ft_strdup("\e[36m"));
		if (i == 7)
			return (ft_strdup("\e[37m"));
		if (i == 8)
			return (ft_strdup("\e[91m"));
		if (i == 9)
			return (ft_strdup("\e[92m"));
		if (i == 0)
			return (ft_strdup("\e[94m"));
	}
	return (ft_strdup("\e[37m"));
}

void	ft_check_copy(t_list *head, t_room *room, char *line, char **str)
{
	t_room		*tmp;

	ft_arreydel(str);
	while (head)
	{
		tmp = head->content;
		if (!ft_strcmp(tmp->name, room->name) ||
									(room->y == tmp->y && room->x == tmp->x))
		{
			ft_strdel(&line);
			if (room->y == tmp->y && room->x == tmp->x)
				exit(ft_printf("{red}Coordinates repeated{eoc}\n"));
			else
				exit(ft_printf("{red}Name repeated{eoc}\n"));
		}
		head = head->next;
	}
}

void	move_ants_strar_end(t_lem *lem)
{
	char *s;

	while (lem->ants > lem->end->ant)
	{
		lem->end->ant++;
		ft_printf("%sL%d-%s ", s = co(9, lem), lem->end->ant, lem->end->name);
		ft_strdel(&s);
	}
	ft_printf("\n");
}

void	ft_usage(t_lem *lem, char **av, int ac)
{
	if (ac == 2)
	{
		if (!ft_strcmp(av[1], "--help"))
		{
			ft_printf("{yellow}You must send a valid card.\n");
			ft_printf("It should look like: ./lem_in < map\n");
			ft_printf("And you can use flag: [--bonus]{eoc}\n");
			exit(1);
		}
		else if (!ft_strcmp(av[1], "--bonus"))
			lem->bonus = 1;
		else
			exit(ft_printf("{yellow}usage: git [--help] [--bonus]{eoc}\n"));
	}
	else if (ac > 2)
		exit(ft_printf("{yellow}usage: git [--help] [--bonus]{eoc}\n"));
}

int		main(int ac, char **av)
{
	int		fd;
	t_lem	*lem;
	char	*line;

	line = NULL;
	fd = 0;
	lem = ft_memalloc(sizeof(t_lem));
	if (ac >= 1)
		ft_usage(lem, av, ac);
	read_graf(fd, line, lem);
	if (!lem->start || !lem->end)
		exit(ft_printf("{red}Not start or end{eoc}\n"));
	if (lem->start_end)
	{
		ft_printf("%s\n", lem->allmapread);
		move_ants_strar_end(lem);
		bonus(lem);
		return (0);
	}
	search_ways(lem);
	steps_ants(lem);
	bonus(lem);
	return (0);
}
