/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dead.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 21:48:56 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/08 21:33:38 by mpeshko          ###   ########.fr       */
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

//  printf("%li %i %li ms without meal monitor\n", curr_time(), 
// 	philo->philo_id, diff);
int	is_dead_monitor(t_philo *philo)
{
	unsigned long	diff;
	unsigned long	timestamp;
	
	diff = 0;
	timestamp = 6666;
	if (philo->tbl->dead == true)
		return (0);
	diff = (curr_time()) - philo->time_last_meal;
	if (diff >= philo->tbl->time_die || philo->tbl->time_die == 0)
	{
		pthread_mutex_lock(&philo->tbl->mtx_dead);
		philo->tbl->dead = true;
		timestamp = curr_time() - philo->tbl->start_time;
		ft_msg(philo, timestamp, DEAD);
		pthread_mutex_unlock(&philo->tbl->mtx_dead);
		return (1);
	}
	else
	return (0);
}
