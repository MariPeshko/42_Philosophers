/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:29:27 by mpeshko           #+#    #+#             */
/*   Updated: 2024/12/08 21:58:25 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * Routine is neverending loop if every philosopher is alive.
 * If someone is dead, then bool dead is true, and this even break the circle.
 * 
 * Even philosophers wait slightly to prevent contention.
*/
void	*routine(void *arg)
{
	int		i;
	t_philo	*philo;
	unsigned long	timestamp;

	philo = (t_philo *)arg;
	i = 0;
	timestamp = 7777;
	int *result = malloc(sizeof(int));
	*result = philo->philo_id;
	if (philo->philo_id % 2 == 0)
		ft_usleep(5);
	while (1)
	{
		if (philo->philo_id % 2 == 0)
		{
			pthread_mutex_lock(philo->left_f);
			if (!dead_or_full(philo->tbl))
			{
				pthread_mutex_unlock(philo->left_f);
				return ((void *)result);
			}
			timestamp = ft_timestamp(philo->tbl);
			ft_msg(philo, timestamp, FORK);
			pthread_mutex_lock(philo->right_f);
			if (!dead_or_full(philo->tbl))
			{
				pthread_mutex_unlock(philo->left_f);
				pthread_mutex_unlock(philo->right_f);
				return ((void *)result);
			}
		}
		else
		{
			pthread_mutex_lock(philo->right_f);
			if (!dead_or_full(philo->tbl))
			{
				pthread_mutex_unlock(philo->right_f);
				return ((void *)result);
			}
			timestamp = ft_timestamp(philo->tbl);
			ft_msg(philo, timestamp, FORK);
			pthread_mutex_lock(philo->left_f);
			if (!dead_or_full(philo->tbl))
			{
				pthread_mutex_unlock(philo->left_f);
				pthread_mutex_unlock(philo->right_f);
				return ((void *)result);
			}
		}
		timestamp = ft_timestamp(philo->tbl);
		if (!dead_or_full(philo->tbl))
		{
			pthread_mutex_unlock(philo->left_f);
			pthread_mutex_unlock(philo->right_f);
			return ((void *)result);
		}
		ft_msg(philo, timestamp, FORK);
		if (!dead_or_full(philo->tbl))
		{
			pthread_mutex_unlock(philo->left_f);
			pthread_mutex_unlock(philo->right_f);
			return ((void *)result);
		}
		
		timestamp = ft_timestamp(philo->tbl);
        ft_msg(philo, timestamp, EATING);
		philo->time_last_meal = ft_time_last_meal(philo->tbl);
		ft_usleep((philo->tbl->time_eat));
		philo->amount_meal++;
		pthread_mutex_unlock(philo->right_f);
		pthread_mutex_unlock(philo->left_f);
		
		if(!ft_sleep(philo))
			return ((void *)result);
		if(!ft_think(philo))
			return ((void *)result);
		i++;
	}
}

int	ft_sleep(t_philo *philo)
{
	unsigned long	timestamp;

	timestamp = 7777;
	if (!dead_or_full(philo->tbl))
		return (0);
	timestamp = ft_timestamp(philo->tbl);
	ft_msg(philo, timestamp, SLEEPING);
	if (!dead_or_full(philo->tbl))
		return (0);
	ft_usleep(philo->tbl->time_sleep);
	if (!dead_or_full(philo->tbl))
		return (0);
	else
		return (1);
}

int	ft_think(t_philo *philo)
{
	unsigned long	timestamp;

	timestamp = 7777;
	timestamp = ft_timestamp(philo->tbl);
	ft_msg(philo, timestamp, THINKING);
	usleep(philo->tbl->time_think);
	if (!dead_or_full(philo->tbl))
		return (0);
	else
		return (1);
}
