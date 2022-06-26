/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 11:27:21 by mtiesha           #+#    #+#             */
/*   Updated: 2022/04/23 16:07:33 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

unsigned long	ft_get_actual_tm(void)
{
	struct timeval	tm;

	gettimeofday(&tm, NULL);
	return ((tm.tv_sec * 1000 + tm.tv_usec / 1000));
}

void	ft_print_mess(t_phil *p, char *str)
{
	unsigned long	tm;

	pthread_mutex_lock(&p->s->print);
	if (p->s->max_eat != -2 && p->count_eat == p->s->max_eat)
		usleep(4221);
	tm = ft_get_actual_tm() - p->s->tm_start;
	printf("%ld %d %s\n", tm, p->id + 1, str);
	pthread_mutex_unlock(&p->s->print);
}
