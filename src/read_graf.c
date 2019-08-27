/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_graf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yserhii <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 19:24:38 by yserhii           #+#    #+#             */
/*   Updated: 2019/04/22 19:24:40 by yserhii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lem_in.h"

static void		node(char *line, t_lem *lem, int n)
{
	int			i;
	char		**str;
	t_room		*room;

	i = -1;
	str = ft_strsplit(line, ' ');
	if (!str[0] || !str[1] || !str[2] || str[0][0] == '#' || str[0][0] == 'L'
		|| ft_allnum(str[1]) == 1 || ft_allnum(str[2]) == 1)
	{
		ft_arreydel(str);
		exit(ft_printf("{red}Bad name of coordinates{eoc}\n"));
	}
	room = ft_memalloc(sizeof(t_room));
	room->name = ft_strdup(str[0]);
	room->x = ft_atoi(str[1]);
	room->y = ft_atoi(str[2]);
	ft_check_copy(lem->head, room, line, str);
	if (n == 1)
		lem->start = room;
	else if (n == 2)
		lem->end = room;
	if (!lem->head)
		lem->head = ft_lstlinks(room, sizeof(t_room));
	else
		ft_lstadd_end(&lem->head, ft_lstlinks(room, sizeof(t_room)));
}

static void		node_edges_add(t_room **room1,
								t_room **room2, t_lem *lem, char **str)
{
	t_list	*point;
	t_room	*room;

	point = lem->head;
	while (point)
	{
		room = point->content;
		if (ft_strcmp(str[0], room->name) == 0)
			*room1 = room;
		if (ft_strcmp(str[1], room->name) == 0)
			*room2 = room;
		point = point->next;
	}
	if (lem->end && lem->start &&
		((lem->start == *room1 && lem->end == *room2) ||
							(lem->start == *room2 && lem->end == *room1)))
		lem->start_end = 1;
}

static void		node_edges(char *line, t_lem *lem)
{
	char	**str;
	t_room	*room1;
	t_room	*room2;

	room1 = NULL;
	room2 = NULL;
	str = ft_strsplit(line, '-');
	node_edges_add(&room1, &room2, lem, str);
	ft_arreydel(str);
	if (!room1 || !room2)
		exit(ft_printf("{red}Bad coordinates{eoc}\n"));
	ft_check_copy_link(lem->head, room1, room2, line);
	if (!room1->head)
		room1->head = ft_lstlinks(room2, sizeof(t_room));
	else
		ft_lstadd_end(&room1->head, ft_lstlinks(room2, sizeof(t_room)));
	if (!room2->head)
		room2->head = ft_lstlinks(room1, sizeof(t_room));
	else
		ft_lstadd_end(&room2->head, ft_lstlinks(room1, sizeof(t_room)));
}

static char		*read_graf_s_e(int fd, char **line1, t_lem *lem)
{
	char	*line;

	line = *line1;
	if (ft_strcmp(line, "##start") == 0)
	{
		ft_strdel(&line);
		if (lem->start)
			exit(ft_printf("{red}Map have two or moor start{eoc}\n"));
		get_next_line(fd, &line);
		lem->allmapread = ft_strjoin(lem->allmapread, line);
		lem->allmapread = ft_strjoin(lem->allmapread, "\n");
		node(line, lem, 1);
	}
	else if (ft_strcmp(line, "##end") == 0)
	{
		ft_strdel(&line);
		if (lem->end)
			exit(ft_printf("{red}Map have two or moor end{eoc}\n"));
		get_next_line(fd, &line);
		lem->allmapread = ft_strjoin(lem->allmapread, line);
		lem->allmapread = ft_strjoin(lem->allmapread, "\n");
		node(line, lem, 2);
	}
	return (line);
}

void			read_graf(int fd, char *line, t_lem *lem)
{
	while (get_next_line(fd, &line) > 0)
	{
		lem->allmapread = ft_strjoin(lem->allmapread, line);
		lem->allmapread = ft_strjoin(lem->allmapread, "\n");
		if (lem->ants == 0 && line[0] != '#')
			ft_ants(line, lem);
		else if (ft_countword(line, ' ') == 3)
			node(line, lem, 0);
		else if (ft_countword(line, '-') == 2)
			node_edges(line, lem);
		else if (!ft_strcmp(line, "##start") ||
									!ft_strcmp(line, "##end"))
			line = read_graf_s_e(fd, &line, lem);
		else if (line[0] == '#')
		{
			ft_strdel(&line);
			continue ;
		}
		else
			break ;
		ft_strdel(&line);
	}
	ft_strdel(&line);
}
