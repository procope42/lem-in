/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <abarriel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 02:15:55 by abarriel          #+#    #+#             */
/*   Updated: 2017/03/20 06:49:50 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		verif_no_path(t_tube *t)
{
	t_tube *tmp;

	tmp = t;
	while (t)
	{
		if (t->room->poids == 0 || t->room->poids == 1)
			break ;
		t = t->next;
	}
	if (!t)
		return (1);
	t = tmp;
	return (0);
}

void	save_path_(t_room **r, t_path **p, int size)
{
	add_back_path(p, (*r), size);
	while ((*r) && (*r)->end != 1)
	{
		while ((*r)->tube && ((*r)->tube->room->by == 4 ||
					(*r)->tube->room->poids != 1))
			(*r)->tube = (*r)->tube->next;
		if ((*r)->by != 4 && (*r)->tube->room->poids == 1 && (*r)->start != 1)
		{
			add_back_path(p, (*r), size);
			(*r)->by = 4;
			(*r)->poids = 2;
			(*r) = (*r)->tube->room;
			size++;
		}
		else
			(*r) = (*r)->tube->room;
	}
	add_back_path(p, (*r), size);
}

t_path	*save_path(t_room *r, int *i)
{
	t_path	*path;
	int		p;

	p = 1;
	path = NULL;
	while (r && r->start != 1)
		r = r->next;
	if (!r->tube || verif_no_path(r->tube))
	{
		(*i)++;
		return (path);
	}
	save_path_(&r, &path, p);
	return (path);
}

t_path	*init_path(t_room *r, int p)
{
	t_path	*u;

	if (!(u = (t_path*)malloc(sizeof(t_path))))
		ft_exit("Failed to Malloc");
	u->r = r;
	u->name = r->name;
	u->size = p;
	u->next = NULL;
	return (u);
}

void	add_back_path(t_path **t, t_room *r, int p)
{
	t_path	*tmp;

	tmp = *t;
	if (!tmp)
	{
		*t = init_path(r, p);
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = init_path(r, p);
	tmp = tmp->next;
}
