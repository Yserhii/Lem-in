/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lem_in.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yserhii <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 16:21:35 by yserhii           #+#    #+#             */
/*   Updated: 2019/04/22 16:21:38 by yserhii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LEM_IN_H
# define FT_LEM_IN_H

# include <libft.h>
# include <errno.h>

typedef struct		s_room
{
	int				x;
	int				y;
	int				lvl;
	int				road;
	int				ant;
	int				count_ant;
	char			*name;
	t_list			*head;
	struct s_room	*parent;
	struct s_room	*back;
}					t_room;

typedef struct		s_lem
{
	int				road;
	int				ants;
	int				count;
	int				bonus;
	int				numroad;
	int				flag_end;
	int				start_end;
	char			*allmapread;
	t_list			*head;
	t_room			*end;
	t_room			*start;
	t_room			**mass;
}					t_lem;

void				read_graf(int fd, char *line, t_lem *lem);
void				search_ways(t_lem *lem);
void				sorting_way_for_up(t_lem *lem);
void				steps_ants(t_lem *lem);
void				clear_node(t_list *list, t_lem *lem);
void				save_way(t_list *head, t_lem *lem, int c);
void				ft_ants(char *line, t_lem *lem);
void				make_add_end(t_lem *lem);
void				ft_check_copy(t_list *head, t_room *room,
										char *line, char **str);
char				*co(int i, t_lem *lem);
void				bonus(t_lem *lem);
void				ft_check_copy_link(t_list *head,
						t_room *room1, t_room *room2, char *line);

#endif
