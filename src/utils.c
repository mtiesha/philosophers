/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 11:27:44 by mtiesha           #+#    #+#             */
/*   Updated: 2022/04/25 18:35:08 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_get_min_max(int a, int b, char *min_or_max)
{
	if ('i' == min_or_max[1])
	{
		if (a > b)
			return (b);
		return (a);
	}
	if (a < b)
		return (b);
	else if (a > b)
		return (a);
	if (a == b)
		return (0);
	return (-1);
}

int	ft_detach_all(t_src *s)
{
	int	i;

	i = 0;
	while (i < s->count_ph)
	{
		if (pthread_detach(s->phils[i].tid) != 0)
			return (0);
		i++;
	}
	return (1);
}
