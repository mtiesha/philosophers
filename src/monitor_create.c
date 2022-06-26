/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 11:27:09 by mtiesha           #+#    #+#             */
/*   Updated: 2022/04/25 18:35:18 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	ft_food_limit(t_src *s, int id)
{
	pthread_mutex_lock(&s->phils[id].monitor);
	if (s->phils[id].count_eat >= s->max_eat)
	{
		printf("%lu %d is eating\n", ft_get_actual_tm() \
			- s->tm_start, s->phils[id].id + 1);
		pthread_mutex_unlock(&s->phils[id].monitor);
		return (1);
	}
	pthread_mutex_unlock(&s->phils[id].monitor);
	return (0);
}

static int	ft_isdie(t_phil *p)
{
	pthread_mutex_lock(&p->monitor);
	if (ft_get_actual_tm() - p->last_eat > p->s->tm_die + 5)
		return (1);
	pthread_mutex_unlock(&p->monitor);
	return (0);
}

static void	ft_monitor(t_src *s)
{
	int	i;

	i = 0;
	while (1)
	{
		if (i == s->count_ph)
			i = 0;
		if (ft_isdie(&s->phils[i]))
		{
			pthread_mutex_lock(&s->print);
			pthread_mutex_unlock(&s->phils[i].monitor);
			printf("%lu %d is died\n", ft_get_actual_tm() \
				- s->tm_start, s->phils[i].id + 1);
			break ;
		}
		else if (-2 != s->max_eat)
		{
			if (ft_food_limit(s, i))
				break ;
		}
		i++;
	}
}

int	ft_create_pth(t_src *s)
{
	int	i;

	i = 0;
	while (i < s->count_ph)
	{
		if (pthread_create(&s->phils[i].tid, NULL, &ft_gate_actions,
				(void *)&s->phils[i]))
			return (0);
		pthread_detach(s->phils[i].tid);
		i++;
		if (i % 2)
			usleep(42);
	}
	ft_monitor(s);
	return (1);
}
