/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtiesha < mtiesha@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:52:43 by mtiesha           #+#    #+#             */
/*   Updated: 2022/04/23 16:11:50 by mtiesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define ERR_MESS_N "Error: Not valid args\n"
# define ERR_MESS_S "Error (-___-)\n"

typedef struct s_phil
{
	pthread_t		tid;
	int				id;
	int				count_eat;
	unsigned long	last_eat;
	int				l_fork;
	int				r_fork;
	pthread_mutex_t	monitor;
	struct s_src	*s;
}	t_phil;

typedef struct s_src
{
	int				count_ph;
	unsigned long	tm_die;
	unsigned long	tm_eat;
	unsigned long	tm_sleep;
	unsigned long	tm_start;
	int				max_eat;
	t_phil			*phils;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}	t_src;

/* validation */
int				ft_isdigit(int c);
int				ft_atoi(const char *str);
int				ft_valid(int ac, char **av);

/* init */
int				ft_init_ph(t_src *s, int argc, char **argv);

/* print mess */
unsigned long	ft_get_actual_tm(void);
void			ft_print_mess(t_phil *p, char *str);

/* utils */
int				ft_get_min_max(int a, int b, char *min_or_max);

/* monitor and create threads */
int				ft_create_pth(t_src *s);
int				ft_detach_all(t_src *s);

/* actions */
void			*ft_gate_actions(void *p_v);

#endif
