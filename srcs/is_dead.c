/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dead.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:48:56 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/14 01:20:46 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	dead_or_full(t_table *tbl)
{
	pthread_mutex_lock(&tbl->mtx_dead);
	if (tbl->dead == true || tbl->all_full == true)
	{
		pthread_mutex_unlock(&tbl->mtx_dead);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&tbl->mtx_dead);
		return (1);
	}
}

int	is_dead_monitor(t_philo *philo)
{
	unsigned long	diff;
	unsigned long	timestamp;

	diff = 0;
	timestamp = 2000;
	if (philo->tbl->dead == true)
		return (0);
	pthread_mutex_lock(&philo->state_lock);
	diff = (curr_time()) - philo->time_last_meal;
	pthread_mutex_unlock(&philo->state_lock);
	if (diff >= philo->tbl->time_die || philo->tbl->time_die == 0)
	{
		philo->tbl->dead = true;
		timestamp = curr_time() - philo->tbl->start_time;
		ft_msg(philo, timestamp, DEAD);
		return (1);
	}
	else
		return (0);
}
