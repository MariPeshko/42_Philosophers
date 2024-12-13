/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:24:36 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/13 18:30:27 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	phil_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->state_lock);
	if (philo->status != EATING)
	{
		pthread_mutex_unlock(&philo->state_lock);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&philo->state_lock);
		return (1);
	}
}

// printf("Monitor: all full\n");
void	*monitor(void *arg)
{
	t_table	*table;
	int		*result;
	int		x;

	table = (t_table *)arg;
	x = 1001;
	result = &x;
	while (1)
	{
		usleep(100);
		if (!monitor_in_loop(table))
			return ((void *)result);
	}
}

int	monitor_in_loop(t_table *tbl)
{
	int		i;
	t_philo	**philosophers;

	i = 0;
	philosophers = tbl->philos;
	if (!all_full(tbl))
		return (0);
	pthread_mutex_lock(&tbl->mtx_dead);
	while (i < tbl->total_nmb)
	{
		if (!phil_eat(philosophers[i]))
		{
			if (is_dead_monitor(philosophers[i]) == 1)
			{
				pthread_mutex_unlock(&tbl->mtx_dead);
				return (0);
			}
		}
		i++;
	}
	pthread_mutex_unlock(&tbl->mtx_dead);
	return (1);
}
