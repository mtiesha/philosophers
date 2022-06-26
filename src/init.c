/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 11:27:34 by mtiesha           #+#    #+#             */
/*   Updated: 2022/04/20 14:47:59 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	ft_init_argv(t_src *s, int argc, char **argv)
{
	s->phils = NULL;
	s->forks = NULL;
	s->count_ph = ft_atoi(argv[1]);
	s->tm_die = ft_atoi(argv[2]);
	s->tm_eat = ft_atoi(argv[3]);
	s->tm_sleep = ft_atoi(argv[4]);
	s->max_eat = -2;
	if (argc == 6)
		s->max_eat = ft_atoi(argv[5]);
	s->tm_start = ft_get_actual_tm();
	s->phils = (t_phil *)malloc(sizeof(t_phil) * s->count_ph);
	s->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * s->count_ph);
	if (!s->phils || !s->forks || s->count_ph < 1 || s->tm_die < 1 \
		|| s->tm_eat < 1 || s->tm_sleep < 1)
		return (0);
	if (-2 != s->max_eat && s->max_eat < 1)
		return (0);
	s->tm_eat *= 1000;
	s->tm_sleep *= 1000;
	return (1);
}

int	ft_init_ph(t_src *s, int argc, char **argv)
{
	int	i;

	i = 0;
	if (!ft_init_argv(s, argc, argv))
		return (0);
	if (pthread_mutex_init(&s->print, NULL) != 0)
		return (0);
	while (i < s->count_ph)
	{
		s->phils[i].id = i;
		s->phils[i].count_eat = 0;
		s->phils[i].last_eat = s->tm_start;
		s->phils[i].s = s;
		s->phils[i].l_fork = i;
		s->phils[i].r_fork = (i + 1) % s->count_ph;
		if (pthread_mutex_init(&s->phils[i].monitor, NULL) != 0)
			return (0);
		if (pthread_mutex_init(&s->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}
