/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 11:26:50 by mtiesha           #+#    #+#             */
/*   Updated: 2022/04/25 18:34:53 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	free_philo(t_src *s)
{
	int	i;

	i = 0;
	while (i <= s->count_ph)
		pthread_mutex_destroy(&s->phils[i++].monitor);
	i = 0;
	while (i <= s->count_ph)
		pthread_mutex_destroy(&s->forks[i++]);
	if (s->phils != NULL)
		free(s->phils);
	if (s->forks != NULL)
		free(s->forks);
	pthread_mutex_destroy(&s->print);
}

int	main(int argc, char **argv)
{
	t_src	s;

	if (argc < 5 || argc > 6 || !ft_valid(argc, argv))
	{
		printf(ERR_MESS_N);
		return (1);
	}
	if (!ft_init_ph(&s, argc, argv))
	{
		free_philo(&s);
		printf(ERR_MESS_S);
		return (1);
	}
	if (!ft_create_pth(&s))
		printf(ERR_MESS_S);
	free_philo(&s);
	return (0);
}
