/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 11:26:31 by mtiesha           #+#    #+#             */
/*   Updated: 2022/04/23 16:09:19 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	ft_take(t_phil *p, int min, int max)
{
	pthread_mutex_lock(&p->s->forks[min]);
	ft_print_mess(p, "has taken a fork");
	pthread_mutex_lock(&p->s->forks[max]);
	ft_print_mess(p, "has taken a fork");
}

static void	ft_eat(t_phil *p)
{
	int	min;
	int	max;

	min = ft_get_min_max(p->s->phils[p->id].l_fork, \
		p->s->phils[p->id].r_fork, "min");
	max = ft_get_min_max(p->s->phils[p->id].l_fork, \
		p->s->phils[p->id].r_fork, "max");
	ft_take(p, min, max);
	pthread_mutex_lock(&p->monitor);
	p->count_eat++;
	p->last_eat = ft_get_actual_tm();
	pthread_mutex_unlock(&p->monitor);
	ft_print_mess(p, "is eating");
	usleep(p->s->tm_eat);
	pthread_mutex_unlock(&p->s->forks[max]);
	pthread_mutex_unlock(&p->s->forks[min]);
}

void	*ft_gate_actions(void *p_v)
{
	t_phil	*p;

	p = (t_phil *)p_v;
	while (1)
	{
		if (-2 != p->s->max_eat && p->count_eat >= p->s->max_eat)
			break ;
		ft_eat(p);
		if (-2 != p->s->max_eat && p->count_eat >= p->s->max_eat)
			break ;
		ft_print_mess(p, "is sleeping");
		usleep(p->s->tm_sleep);
		if (-2 != p->s->max_eat && p->count_eat >= p->s->max_eat)
			break ;
		ft_print_mess(p, "is thinking");
		if (-2 != p->s->max_eat && p->count_eat >= p->s->max_eat)
			break ;
	}
	return (0);
}
